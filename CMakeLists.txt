cmake_minimum_required(VERSION 3.20)
project(OpenMultiMeter)

set(CMAKE_CXX_STANDARD 20)

# Pull fmtlib from github
# Reason: GCC < 13 does not provide std::format
include(FetchContent)
FetchContent_Declare(
        fmtlib
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.0.2 # Replace with the latest version
)
FetchContent_MakeAvailable(fmtlib)

add_executable(OpenMultiMeter main.cpp
        src/embedonix/omm/drivers/ads8699.cpp
        include/embedonix/omm/drivers/datafield_interface.hpp
        include/embedonix/omm/drivers/ads8699.hpp
        include/embedonix/omm/drivers/device_register.hpp
)

target_include_directories(OpenMultiMeter PUBLIC include)
target_link_libraries(OpenMultiMeter PUBLIC pigpio fmt::fmt)