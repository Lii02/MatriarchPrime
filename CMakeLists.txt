cmake_minimum_required(VERSION 4.0)
project(LiGameStarter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_compile_definitions(UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_DEBUG DEBUG)
else()
    add_compile_definitions(_RELEASE RELEASE)
endif()

add_subdirectory(LiDependencies)

file(GLOB_RECURSE SRCS src/*.cpp src/*.c)
file(GLOB_RECURSE HDRS src/*.h)

add_executable(LiGameStarter)
target_sources(LiGameStarter PUBLIC ${SRCS} ${HDRS})

if(WIN32)
    add_custom_command(TARGET LiGameStarter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/LiDependencies/Bin/SDL3.dll
        $<TARGET_FILE_DIR:LiGameStarter>)

    add_custom_command(TARGET LiGameStarter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/LiDependencies/Bin/OpenAL32.dll
        $<TARGET_FILE_DIR:LiGameStarter>)

    target_link_libraries(LiGameStarter opengl32)
    target_link_options(LiGameStarter PRIVATE "$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>" "$<$<CONFIG:Debug>:/SUBSYSTEM:CONSOLE>")
endif()

target_precompile_headers(LiGameStarter PUBLIC src/pch.h)
target_link_libraries(LiGameStarter LiDependencies SDL3 OpenAL32)
target_include_directories(LiGameStarter PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(LiGameStarter PUBLIC ${PROJECT_SOURCE_DIR}/LiDependencies/Include)
target_link_directories(LiGameStarter PUBLIC ${PROJECT_SOURCE_DIR}/LiDependencies/Lib)
set_property(TARGET LiGameStarter PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")