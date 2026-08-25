cmake_minimum_required(VERSION 3.14)
project(search_engine LANGUAGES CXX)

# Принудительно отключаем проверку SSL и любые сетевые блокировки Windows для Google Test
set(CMAKE_TLS_VERIFY OFF CACHE BOOL "" FORCE)
set(FETCHCONTENT_QUIET OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Автоматическое скачивание Google Test 
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com
)
set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# 2. Исходные файлы поискового движка АйТиБокс
set(ENGINE_SOURCES
    src/ConverterJSON.cpp
    src/InvertedIndex.cpp
    src/SearchServer.cpp
)

# 3. Создаем основное приложение
add_executable(search_engine main.cpp ${ENGINE_SOURCES})
target_include_directories(search_engine PRIVATE include)

# 4. Создаем тесты
add_executable(search_engine_tests tests/tests.cpp ${ENGINE_SOURCES})
target_include_directories(search_engine_tests PRIVATE include)
target_link_libraries(search_engine_tests PRIVATE gtest_main)

add_test(NAME CoreTests COMMAND search_engine_tests)
