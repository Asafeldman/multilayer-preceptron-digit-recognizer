cmake_minimum_required(VERSION 3.24)
project(digit_recoginition_net)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(digit_recoginition_net
        Activation.h
        Dense.h
        main.cpp
        Matrix.cpp
        Matrix.h
        MlpNetwork.h Activation.cpp Dense.cpp MlpNetwork.cpp)
