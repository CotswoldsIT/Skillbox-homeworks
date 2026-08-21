cmake_minimum_required(VERSION 3.16)

project(MySkillboxApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(MySkillboxApp main.cpp)

target_link_libraries(MySkillboxApp PRIVATE
    Qt6::Widgets
)
