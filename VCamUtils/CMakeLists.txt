cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(PROJECT "VCamUtils")
project(${PROJECT})
message("  -- build ${PROJECT}")

set(SOURCES
        src/image/color.h
        src/image/videoformat.cpp
        src/image/videoformat.h
        src/image/videoformattypes.h
        src/image/videoframe.cpp
        src/image/videoframe.h
        src/image/videoframetypes.h
        src/logger/logger.cpp
        src/logger/logger.h
        src/fraction.cpp
        src/fraction.h
        src/ipcbridge.h
        src/timer.cpp
        src/timer.h
        src/utils.cpp
        src/utils.h
        )

add_library(${PROJECT} STATIC ${SOURCES})
#set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)
