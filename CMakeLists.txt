cmake_minimum_required(VERSION 3.2.0)
project(dotghost VERSION 0.2.0 LANGUAGES CXX)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

find_package (Threads REQUIRED)
find_package (X11 REQUIRED)

add_subdirectory(src)