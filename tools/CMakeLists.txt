# --- tools ---

add_executable(resource_embedder resource_embedder.cpp)
add_executable(deep_copy_bench deep_copy_benchmark.cpp)
find_package(Boost REQUIRED)
target_link_libraries(deep_copy_bench PUBLIC Boost::boost adm)
target_compile_features(deep_copy_bench PRIVATE cxx_std_17)