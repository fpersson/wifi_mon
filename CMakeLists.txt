cmake_minimum_required(VERSION 3.17)
project(wifi_mon)

set(CMAKE_CXX_STANDARD 17)

add_executable(wifi_mon main.cpp networking/wifistatus.cpp networking/wifistatus.h networking/rtstatus.cpp networking/rtstatus.h networking/structs.h)