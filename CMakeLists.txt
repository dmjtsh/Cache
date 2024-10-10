cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cache_proj VERSION 1.0)

# PCA CACHE
add_executable(pca_cache_proj pca_cache/main.cpp pca_cache/src/test_interface.cpp)
target_include_directories(pca_cache_proj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pca_cache/include)

add_executable(pca_tests pca_cache/tests.cpp pca_cache/src/test_interface.cpp)
target_link_libraries(pca_tests gtest gmock pthread)
target_include_directories(pca_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pca_cache/include)
add_test(NAME PCA_TESTS COMMAND pca_tests)

target_compile_features(pca_cache_proj PRIVATE cxx_std_20)
target_compile_features(pca_tests PRIVATE cxx_std_20)

#LFU CACHE
add_executable(lfu_cache_proj lfu_cache/main.cpp lfu_cache/src/test_interface.cpp)
target_include_directories(lfu_cache_proj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lfu_cache/include)

add_executable(lfu_tests lfu_cache/tests.cpp lfu_cache/src/test_interface.cpp)
target_link_libraries(lfu_tests gtest gmock pthread)
target_include_directories(lfu_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lfu_cache/include)
add_test(NAME LFU_TESTS COMMAND lfu_tests)

target_compile_features(lfu_cache_proj PRIVATE cxx_std_20)
target_compile_features(lfu_tests PRIVATE cxx_std_20)
