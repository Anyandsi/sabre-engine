cmake_minimum_required(VERSION 3.16)
project(sabre_engine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build GLFW from the submodule, but skip its extras
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_executable(sabre_engine
    src/main.cpp
    src/Renderer.cpp
    src/Mesh.cpp
    external/glad/src/glad.c
    src/utils/FileReader.cpp
)

target_include_directories(sabre_engine PRIVATE external/glad/include)

target_link_libraries(sabre_engine PRIVATE glm::glm)

find_package(OpenGL REQUIRED)

target_link_libraries(sabre_engine PRIVATE
    glfw
    OpenGL::GL
)

target_compile_definitions(sabre_engine
    PRIVATE SHADER_DIR="${CMAKE_SOURCE_DIR}/src/shaders"
)

target_include_directories(sabre_engine PRIVATE
    ${CMAKE_SOURCE_DIR}/external/stb
)

file(COPY
    ${CMAKE_SOURCE_DIR}/src/textures
    DESTINATION ${CMAKE_BINARY_DIR}
)
