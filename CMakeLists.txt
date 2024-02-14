cmake_minimum_required(VERSION 3.14)

project(TidalHarmonicAnalysis LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

file(GLOB _HEADERS_PUBLIC
    "include/*.h"
    "include/*/*.h"
)

file(GLOB _SOURCES
    "src/*.h"
    "src/*.cpp"
    "src/*/*.h"
    "src/*/*.cpp"
)

add_library(${PROJECT_NAME} SHARED
  ${_HEADERS_PUBLIC}
  ${_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(${PROJECT_NAME} PRIVATE TidalHarmonicAnalysis)

target_include_directories(${PROJECT_NAME}
     PUBLIC
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#         #$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include> # FIXME this is for *_export.h
         $<INSTALL_INTERFACE:include>
#     PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}/src
 )
