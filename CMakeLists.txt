cmake_minimum_required(VERSION 3.0)
project(Stenography LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

add_executable(encrypt encrypt.cpp)
add_executable(decrypt decrypt.cpp)

