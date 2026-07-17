cmake_minimum_required(VERSION 3.10)
project(ComputerSimulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к заголовкам глобально, чтобы в .cpp писать только имя файла
include_directories(include)

# Передаем управление сборкой внутренней папке src
add_subdirectory(src)
