cmake_minimum_required(VERSION 3.0...3.21) # The version of CMake

project(RayLibGame CXX) # Project name and the language (C++)

set(CMAKE_CXX_STANDARD 11) # Sets the C++ standard (11, 14 or 17)

set(RAYLIB_INCLUDE_DIR "C:/Users/jayxw/Desktop/RayLibGame/raylib/include")
set(RAYLIB_LIB_DIR "C:/Users/jayxw/Desktop/RayLibGame/raylib/lib")

include_directories((${RAYLIB_INCLUDE_DIR})) # Include directories
add_executable(${PROJECT_NAME}  src/main.cpp)

# RELEASE BUILD ONLY
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

# DEV BUILD ONLY
# add_custom_target(GenerateLaunchJson ALL
#     COMMAND ${CMAKE_COMMAND} -E echo "Generating launch.json"
#     COMMAND ${CMAKE_COMMAND} -P "${CMAKE_SOURCE_DIR}/GenerateLaunchJSON.cmake"
#     WORKING_DIRECTORY "${workspaceFolder}"
# )
# add_dependencies(${PROJECT_NAME} GenerateLaunchJson)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32 gdi32 winmm)
endif()

target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB_DIR}/raylib.lib)
