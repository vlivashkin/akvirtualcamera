cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(PROJECT "Manager")
project(${PROJECT})
message("    -- build ${PROJECT}")

set(SOURCES
        src/main.cpp
        )

add_executable(${PROJECT}
        ${SOURCES})
target_include_directories(${PROJECT} PRIVATE
        ${PROJECT_SOURCE_DIR}/..
        ${PROJECT_SOURCE_DIR}/../dshow
        )
target_link_libraries(${PROJECT}
        VCamUtils
)
set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)
