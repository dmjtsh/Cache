cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(pca_cache_proj VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(pca_cache_proj main.cpp ${SRC_FILES})

target_include_directories(pca_cache_proj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
