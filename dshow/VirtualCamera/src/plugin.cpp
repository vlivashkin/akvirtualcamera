/* akvirtualcamera, virtual camera for Mac and Windows.
 * Copyright (C) 2020  Gonzalo Exequiel Pedone
 *
 * akvirtualcamera is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * akvirtualcamera is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with akvirtualcamera. If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: http://webcamoid.github.io/
 */

#include "plugin.h"
#include "plugininterface.h"
#include "classfactory.h"
#include "PlatformUtils/src/utils.h"
#include "VCamUtils/src/utils.h"

inline AkVCam::PluginInterface *pluginInterface()
{
    static AkVCam::PluginInterface pluginInterface;

    return &pluginInterface;
}

// Filter entry point
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    UNUSED(lpvReserved)
    AkLogFunction();
    auto logLevel =
            AkVCam::regReadInt("loglevel", AKVCAM_LOGLEVEL_DEFAULT);
    AkVCam::Logger::setLogLevel(logLevel);

    if (AkVCam::Logger::logLevel() > AKVCAM_LOGLEVEL_DEFAULT) {
        // Turn on lights
        freopen("CONOUT$", "a", stdout);
        freopen("CONOUT$", "a", stderr);
        setbuf(stdout, nullptr);
    }

    auto temp = AkVCam::tempPath();
    auto logFile =
            AkVCam::regReadString("logfile",
                                  std::string(temp.begin(), temp.end())
                                  + "\\" DSHOW_PLUGIN_NAME ".log");
    AkVCam::Logger::setLogFile(logFile);

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            AkLogInfo() << "Reason Attach" << std::endl;
            AkLogInfo() << "Module file name: "
                        << AkVCam::moduleFileName(hinstDLL)
                        << std::endl;
            DisableThreadLibraryCalls(hinstDLL);
            pluginInterface()->pluginHinstance() = hinstDLL;

            break;

        case DLL_PROCESS_DETACH:
            AkLogInfo() << "Reason Detach" << std::endl;

            break;

        default:
            AkLogInfo() << "Reason Unknown: " << fdwReason << std::endl;

            break;
    }

    return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
    AkLogFunction();
    AkLogInfo() << "CLSID: " << AkVCam::stringFromClsid(rclsid) << std::endl;
    AkLogInfo() << "IID: " << AkVCam::stringFromClsid(rclsid) << std::endl;

    if (!ppv)
        return E_INVALIDARG;

    *ppv = nullptr;

    if (!IsEqualIID(riid, IID_IUnknown)
        && !IsEqualIID(riid, IID_IClassFactory)
        && AkVCam::cameraFromId(riid) < 0)
            return CLASS_E_CLASSNOTAVAILABLE;

    auto classFactory = new AkVCam::ClassFactory(rclsid);
    classFactory->AddRef();
    *ppv = classFactory;

    return S_OK;
}

STDAPI DllCanUnloadNow()
{
    AkLogFunction();

    return AkVCam::ClassFactory::locked()? S_FALSE: S_OK;
}

STDAPI DllRegisterServer()
{
    AkLogFunction();
    DllUnregisterServer();

    bool ok = true;

    for (DWORD i = 0; i < AkVCam::camerasCount(); i++) {
        auto description = AkVCam::cameraDescription(i);
        auto path = AkVCam::cameraPath(i);
        auto clsid = AkVCam::createClsidFromStr(path);

        AkLogInfo() << "Creating Camera" << std::endl;
        AkLogInfo() << "\tDescription: "
                    << std::string(description.begin(),
                                   description.end())
                    << std::endl;
        AkLogInfo() << "\tPath: "
                    << std::string(path.begin(), path.end())
                    << std::endl;
        AkLogInfo() << "\tCLSID: " << AkVCam::stringFromIid(clsid) << std::endl;

        ok &= pluginInterface()->createDevice(path, description);
    }

    return ok? S_OK: E_UNEXPECTED;
}

STDAPI DllUnregisterServer()
{
    AkLogFunction();
    auto cameras =
            AkVCam::listRegisteredCameras(pluginInterface()->pluginHinstance());

    for (auto camera: cameras) {
        AkLogInfo() << "Deleting "
                    << AkVCam::stringFromClsid(camera)
                    << std::endl;
        pluginInterface()->destroyDevice(camera);
    }

    return S_OK;
}
