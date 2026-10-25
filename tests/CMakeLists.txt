# Создаем исполняемый файл для юнит-тестов
add_executable(unit_tests test_all_sortings.cpp)

# Подключаем нашу библиотеку сортировок и фреймворк Google Test
target_link_libraries(unit_tests PRIVATE sorting_lib gtest_main)

# Интеграция с тест-раннером Visual Studio
include(GoogleTest)
gtest_discover_tests(unit_tests)