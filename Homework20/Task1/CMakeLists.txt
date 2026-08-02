cmake_minimum_required(VERSION 3.10)
project(MedicalSimulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# заголовочные файлы (.h)
include_directories(include)

# Собираем исполняемый файл из исходников в папке src
add_executable(MedicalSimulator src/main.cpp)
