add_executable(CPUInfo CPUInfo.cpp)

target_include_directories(CPUInfo PUBLIC ../include)

target_compile_features(CPUInfo PRIVATE cxx_std_11)
