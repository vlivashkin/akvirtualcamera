cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(PROJECT "VirtualCamera")
project(${PROJECT})
message("      -- build ${PROJECT}")

set(SOURCES
        src/basefilter.cpp
        src/basefilter.h
        src/classfactory.cpp
        src/classfactory.h
        src/cunknown.cpp
        src/cunknown.h
        src/enummediatypes.cpp
        src/enummediatypes.h
        src/enumpins.cpp
        src/enumpins.h
        src/filtermiscflags.cpp
        src/filtermiscflags.h
        src/latency.cpp
        src/latency.h
        src/mediafilter.cpp
        src/mediafilter.h
        src/mediasample.cpp
        src/mediasample.h
        src/mediasample2.cpp
        src/mediasample2.h
        src/memallocator.cpp
        src/memallocator.h
        src/persist.cpp
        src/persist.h
        src/persistpropertybag.cpp
        src/persistpropertybag.h
        src/pin.cpp
        src/pin.h
        src/plugin.cpp
        src/plugin.h
        src/plugininterface.cpp
        src/plugininterface.h
        src/propertyset.cpp
        src/propertyset.h
        src/pushsource.cpp
        src/pushsource.h
        src/qualitycontrol.cpp
        src/qualitycontrol.h
        src/referenceclock.cpp
        src/referenceclock.h
        src/specifypropertypages.cpp
        src/specifypropertypages.h
        src/streamconfig.cpp
        src/streamconfig.h
        src/videocontrol.cpp
        src/videocontrol.h
        src/videoprocamp.cpp
        src/videoprocamp.h
        )

add_library(${PROJECT} STATIC ${SOURCES})
target_include_directories(${PROJECT} PRIVATE
        ${PROJECT_SOURCE_DIR}/..
        ${PROJECT_SOURCE_DIR}/../..
        )
target_link_libraries(${PROJECT}
        VCamIPC
        PlatformUtils
        VCamUtils
)
set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)
