cmake_minimum_required(VERSION 3.0...3.21) # The version of CMake

project(RayLibGame CXX) # Project name and the language (C++)

message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

# Sets up include paths for VS Code to prevent red squiggly lines
set(JSON_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/.vscode/c_cpp_properties.json")
set(JSON_CONTENT "
{
    \"configurations\": [
        {
            \"name\": \"Win32\",
            \"includePath\": [
                \"\${workspaceFolder}/**\"
            ]
        }
    ],
    \"version\": 4
}
")
file(WRITE ${JSON_OUTPUT} ${JSON_CONTENT})

set(CMAKE_CXX_STANDARD 20) # Sets the C++ standard (11, 14 or 17)

set(RAYLIB_INCLUDE_DIR "dependencies/raylib/include")
set(RAYLIB_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/raylib/lib")

set(RAYLIB_IMGUI_INCLUDE_DIR "dependencies/rlImGui")

set(IMGUI_INCLUDE_DIR "dependencies/imgui")
set(IMGUI_SRC
    "dependencies/rlImGui/rlImGui.cpp"
    "dependencies/imgui/imgui.cpp"
    "dependencies/imgui/imgui_demo.cpp"
    "dependencies/imgui/imgui_draw.cpp"
    "dependencies/imgui/imgui_tables.cpp"
    "dependencies/imgui/imgui_widgets.cpp"
    "dependencies/imgui/imgui_impl_opengl3.cpp"
)

include_directories((${RAYLIB_INCLUDE_DIR} ${IMGUI_INCLUDE_DIR} ${RAYLIB_IMGUI_INCLUDE_DIR})) # Include directories

add_executable(${PROJECT_NAME}
    src/Main.cpp
    src/Utils/Utils.cpp
    src/UI/ImGUI/imgui_manager.cpp
    ${IMGUI_SRC}  # Include ImGui sources
)

target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB_DIR}/raylib.lib ${IMGUI_LIB_DIR})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32 gdi32 winmm)
endif()



# message(FATAL_ERROR "Current Source Directory: ${CMAKE_CURRENT_SOURCE_DIR}")

# Get the root source directory
