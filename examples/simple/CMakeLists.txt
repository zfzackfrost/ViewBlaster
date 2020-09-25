add_executable(simple main.cpp)
target_link_libraries(simple PRIVATE ViewBlaster)
target_compile_features(simple PRIVATE cxx_std_17)
