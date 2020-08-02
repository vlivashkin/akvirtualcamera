cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(PROJECT "PlatformUtils")
project(${PROJECT})
message("      -- build ${PROJECT}")

set(DSHOW_PLUGIN_NAME "AkVirtualCamera")
set(DSHOW_PLUGIN_ASSISTANT_NAME "AkVCamAssistant")
set(DSHOW_PLUGIN_ASSISTANT_DESCRIPTION "Webcamoid virtual camera service")
set(DSHOW_PLUGIN_DESCRIPTION "Webcamoid Virtual Camera")
set(DSHOW_PLUGIN_DESCRIPTION_EXT "Central service for communicating between virtual cameras clients and servers")
set(DSHOW_PLUGIN_DEVICE_PREFIX "/akvcam/video")
set(DSHOW_PLUGIN_VENDOR "Webcamoid Project")

add_compile_definitions(DSHOW_PLUGIN_NAME="${DSHOW_PLUGIN_NAME}")
add_compile_definitions(DSHOW_PLUGIN_NAME_L=L"${DSHOW_PLUGIN_NAME}")
add_compile_definitions(DSHOW_PLUGIN_ASSISTANT_NAME="${DSHOW_PLUGIN_ASSISTANT_NAME}")
add_compile_definitions(DSHOW_PLUGIN_ASSISTANT_NAME_L=L"${DSHOW_PLUGIN_ASSISTANT_NAME}")
add_compile_definitions(DSHOW_PLUGIN_ASSISTANT_DESCRIPTION="${DSHOW_PLUGIN_ASSISTANT_DESCRIPTION}")
add_compile_definitions(DSHOW_PLUGIN_ASSISTANT_DESCRIPTION_L=L"${DSHOW_PLUGIN_ASSISTANT_DESCRIPTION}")
add_compile_definitions(DSHOW_PLUGIN_DESCRIPTION="${DSHOW_PLUGIN_DESCRIPTION}")
add_compile_definitions(DSHOW_PLUGIN_DESCRIPTION_L=L"${DSHOW_PLUGIN_DESCRIPTION}")
add_compile_definitions(DSHOW_PLUGIN_DESCRIPTION_EXT="${DSHOW_PLUGIN_DESCRIPTION_EXT}")
add_compile_definitions(DSHOW_PLUGIN_DESCRIPTION_EXT_L=L"${DSHOW_PLUGIN_DESCRIPTION_EXT}")
add_compile_definitions(DSHOW_PLUGIN_DEVICE_PREFIX="${DSHOW_PLUGIN_DEVICE_PREFIX}")
add_compile_definitions(DSHOW_PLUGIN_DEVICE_PREFIX_L=L"${DSHOW_PLUGIN_DEVICE_PREFIX}")
add_compile_definitions(DSHOW_PLUGIN_VENDOR="${DSHOW_PLUGIN_VENDOR}")
add_compile_definitions(DSHOW_PLUGIN_VENDOR_L=L"${DSHOW_PLUGIN_VENDOR}")

set(SOURCES
        src/messagecommons.h
        src/messageserver.cpp
        src/messageserver.h
        src/mutex.cpp
        src/mutex.h
        src/sharedmemory.cpp
        src/sharedmemory.h
        src/utils.cpp
        src/utils.h
        )

add_library(${PROJECT} STATIC ${SOURCES})
target_include_directories(${PROJECT} PRIVATE
        ${PROJECT_SOURCE_DIR}/..
        ${PROJECT_SOURCE_DIR}/../..
)
target_link_libraries(${PROJECT}
        VCamUtils
        )
set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)
