cmake_minimum_required(VERSION 3.16)

project(MySkillboxApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# автоматическая обработка сигналов и слотов Qt
set(CMAKE_AUTOMOC ON)

# Поиск установленной версию Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(MySkillboxApp main.cpp)

# Подключение библиотеки Qtкпроекту
target_link_libraries(MySkillboxApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
