cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(PROJECT "AkVirtualCamera")
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

add_custom_target(${PROJECT}
        DEPENDS Assistant VirtualCamera)
set(PLUGIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/AkVirtualCamera.plugin)
file(MAKE_DIRECTORY ${PLUGIN_DIR}/x64)
file(MAKE_DIRECTORY ${PLUGIN_DIR}/share)
add_custom_command(TARGET ${PROJECT} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Assistant> ${PLUGIN_DIR}/x64/AkVCamAssistant.exe
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:VirtualCamera> ${PLUGIN_DIR}/x64/AkVirtualCamera.dll
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Assistant> ${PLUGIN_DIR}/AkVCamAssistant.exe
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:VirtualCamera> ${PLUGIN_DIR}/AkVirtualCamera.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/TestFrame.bmp ${PLUGIN_DIR}/share)