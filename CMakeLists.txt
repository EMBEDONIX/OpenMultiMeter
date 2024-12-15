cmake_minimum_required(VERSION 3.20)
project(OpenMultiMeter)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenMultiMeter main.cpp
        src/embedonix/omm/drivers/ads8699.cpp
        include/embedonix/omm/drivers/datafield_interface.hpp
        include/embedonix/omm/drivers/ads8699.hpp
        include/embedonix/omm/drivers/device_register.hpp
)

target_include_directories(OpenMultiMeter PUBLIC include)
target_link_libraries(OpenMultiMeter PUBLIC pigpio)