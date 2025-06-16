cmake_minimum_required(VERSION 3.17)

project(OpenGLTemplate)

set(CMAKE_CXX_STANDARD 17)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} GLEW::GLEW glfw OpenGL::GL glm::glm)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Shaders:
set(SHADER_DIR ${CMAKE_SOURCE_DIR}/shaders)
set(SHADER_OUTPUT_DIR ${CMAKE_BINARY_DIR}/shaders)

file(GLOB SHADER_FILES ${SHADER_DIR}/*)

file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

add_custom_target(
  copy_shaders ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_DIR} ${SHADER_OUTPUT_DIR}
  DEPENDS ${SHADER_FILES})

add_dependencies(${PROJECT_NAME} copy_shaders)

# Resources:
set(RESC_DIR ${CMAKE_SOURCE_DIR}/res)
set(RESC_OUTPUT_DIR ${CMAKE_BINARY_DIR}/res)

file(GLOB RESC_FILES ${RESC_DIR}/*)

file(MAKE_DIRECTORY ${RESC_OUTPUT_DIR})

add_custom_target(
        copy_resc ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESC_DIR} ${RESC_OUTPUT_DIR}
        DEPENDS ${RESC_FILES})

add_dependencies(${PROJECT_NAME} copy_resc)
