cmake_minimum_required(VERSION 3.4...3.18)
project(demo LANGUAGES CXX)

find_package(pybind11 REQUIRED)

pybind11_add_module(demo
    bind/libpd.cpp
    bind/PdBase.cpp
    bind/PdTypes.cpp
    ${CMAKE_SOURCE_DIR}/../libs/libpd.a
    # ../libs/libpd.a
)

include_directories(
    include
    ../pure-data/src
    ../libpd_wrapper
    ../libpd_wrapper/util
)

#link_directories(${CMAKE_SOURCE_DIR}/../libs)