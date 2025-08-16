cmake_minimum_required(VERSION 4.0.0)

set(CMAKE_CXX_STANDARD 23)
set(PROJECT_NAME softpack)

project(${PROJECT_NAME})

if (EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
  include("${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
endif()

set(BOOST_LIBS boost::boost)
set(IMGUI_LIBS imgui::imgui)
set(IMGUI-SFML_LIBS ImGui-SFML::ImGui-SFML)
set(SFML_LIBS sfml::sfml)

find_package(Boost REQUIRED COMPONENTS ${BOOST_LIBS})
find_package(imgui REQUIRED COMPONENTS ${IMGUI_LIBS})
find_package(ImGui-SFML REQUIRED COMPONENTS ${IMGUI-SFML_LIBS})
find_package(SFML REQUIRED COMPONENTS ${SFML_LIBS})

set(CONAN_LIBS ${BOOST_LIBS} ${IMGUI_LIBS} ${IMGUI-SFML_LIBS} ${SFML_LIBS})

set(SOURCES "*.cpp")
set(HEADERS "*.hpp")

set(CORE_PROJECT_NAME "core")
set(CORE_PROJECT_PATH "src/core/")

file(GLOB_RECURSE CORE_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "${CORE_PROJECT_PATH}${SOURCES}")
file(GLOB_RECURSE CORE_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "${CORE_PROJECT_PATH}${HEADERS}")

add_executable(${CORE_PROJECT_NAME} ${CORE_SOURCES} ${CORE_HEADERS})

target_link_libraries(${CORE_PROJECT_NAME} ${CONAN_LIBS} ${LIBRARY_PROJECT_NAME})
