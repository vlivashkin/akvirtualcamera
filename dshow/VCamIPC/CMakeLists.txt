cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(PROJECT "VCamIPC")
project(${PROJECT})
message("      -- build ${PROJECT}")

set(SOURCES
        src/ipcbridge.cpp
        )

add_library(${PROJECT} STATIC ${SOURCES})
target_compile_definitions(${PROJECT} PRIVATE
        DSHOW_PLUGIN_ARCH="${TARGET_ARCH}"
        DSHOW_PLUGIN_ARCH_L=L"${TARGET_ARCH}"
)
target_include_directories(${PROJECT} PRIVATE
        ${PROJECT_SOURCE_DIR}/..
        ${PROJECT_SOURCE_DIR}/../..
        )
target_link_libraries(${PROJECT}
        PlatformUtils
        VCamUtils
        )
set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)
