cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
set(PROJECT_NAME softpack)

project(${PROJECT_NAME})

if (EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
  include("${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
endif()

find_package(imgui REQUIRED)
find_package(SFML REQUIRED)
find_package(ImGui-SFML REQUIRED)

set(IMGUI_LIBS imgui::imgui)
set(SFML_LIBS sfml-graphics sfml-system sfml-window)
set(IMGUI-SFML_LIBS ImGui-SFML::ImGui-SFML)
set(CONAN_LIBS ${IMGUI_LIBS} ${SFML_LIBS} ${IMGUI-SFML_LIBS})

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
