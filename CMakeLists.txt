cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cache_proj VERSION 1.0)

file(GLOB_RECURSE PCA_SRC_FILES pca_cache/src/*.cpp)
add_executable(pca_cache_proj pca_cache/main.cpp ${PCA_SRC_FILES})
target_include_directories(pca_cache_proj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pca_cache/include)
target_link_libraries(pca_cache_proj gtest gmock pthread)

file(GLOB_RECURSE LFU_SRC_FILES lfu_cache/src/*.cpp)
add_executable(lfu_cache_proj lfu_cache/main.cpp ${LFU_SRC_FILES})
target_include_directories(lfu_cache_proj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lfu_cache/include)
target_link_libraries(lfu_cache_proj gtest gmock pthread)
