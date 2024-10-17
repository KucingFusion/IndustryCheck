cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(IndustryCheck LANGUAGES CXX)

#设置编译参数
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "c:/Qt/6.7.2/mingw_64")           # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR C:/opencv/build/x64/rebuild_for_qt)      # OpenCV_DIR

find_package(OpenCV REQUIRED)                           # OpenCV package
find_package(Qt6 COMPONENTS Widgets REQUIRED)           # Qt COMPONENTS

aux_source_directory(./src srcs)

# 设置头文件目录
include_directories(${Opencv_INCLUDE_DIRS})             # OpenCV sdk
include_directories(${PROJECT_SOURCE_DIR}/include/)     # MV sdk

# 设置库目录
link_directories(${PROJECT_SOURCE_DIR}/lib)

# Specify MSVC UTF-8 encoding   
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME}
    #WIN32 # If you need a terminal for debug, please comment this statement 
    ${srcs} 
) 
target_link_libraries(${PROJECT_NAME} PRIVATE 
                Qt6::Widgets 
                MvCameraControl 
                ${OpenCV_LIBS}) # Qt6 HikiCamer OpenCV Shared Library

message(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_LIBS})