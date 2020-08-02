cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(PROJECT "akvirtualcamera")
project(${PROJECT})
message("-- build ${PROJECT}")

add_definitions(-DUNICODE -D_UNICODE)

set(COMMONS_APPNAME "AkVirtualCamera")
set(COMMONS_TARGET "akvirtualcamera")

add_compile_definitions(COMMONS_APPNAME="${COMMONS_APPNAME}")
add_compile_definitions(COMMONS_TARGET="${COMMONS_TARGET}")
add_compile_definitions(COMMONS_VER_MAJ="${VER_MAJ}")
add_compile_definitions(COMMONS_VERSION="${VERSION}")
add_compile_definitions(PREFIX="${PREFIX}")

add_subdirectory(VCamUtils)
if (APPLE)
    add_subdirectory(cmio)
elseif(MSVC)
    add_subdirectory(dshow)
endif()
add_subdirectory(Manager)
