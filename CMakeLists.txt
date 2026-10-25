cmake_minimum_required(VERSION 3.14)
project(SortingLabs CXX)

set(CMAKE_CXX_STANDARD 17)

# Автоматическая загрузка GoogleTest через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Подключаем все файлы библиотек из src/ и include/
file(GLOB SORTING_SOURCES "src/*.cpp")
file(GLOB SORTING_HEADERS "include/*.h")

add_library(sorting_lib ${SORTING_SOURCES} ${SORTING_HEADERS})
target_include_directories(sorting_lib PUBLIC include)

# Передаем управление в папку тестов
add_subdirectory(tests)