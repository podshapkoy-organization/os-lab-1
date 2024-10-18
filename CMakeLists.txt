cmake_minimum_required(VERSION 3.28)
project(os_lab_1)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS system chrono)

add_executable(os_lab_1 shell/main.cpp
        Monitoring-profiling/ema_search_srt/ema_search_str.cpp
        Monitoring-profiling/main.cpp
        Monitoring-profiling/ema_search_srt/ema_search_str.cpp
)

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(os_lab_1
        Boost::system
        Boost::chrono
)
