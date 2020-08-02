cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(PROJECT "Assistant")
project(${PROJECT})
message("      -- build ${PROJECT}")

set(SOURCES
        src/main.cpp
        src/service.h
        src/service.cpp
        )

add_executable(${PROJECT} ${SOURCES})
target_include_directories(${PROJECT} PRIVATE
        ${PROJECT_SOURCE_DIR}/..
        ${PROJECT_SOURCE_DIR}/../..
        )
target_link_libraries(${PROJECT}
        PlatformUtils
        VCamUtils
        )
set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)
