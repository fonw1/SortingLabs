# SortingLabs — Алгоритмы сортировки на C++

Проект содержит реализацию 12 алгоритмов сортировки, покрытых юнит-тестами на **Google Test** с использованием сборщика **CMake**.

---

## 📌 Реализованные алгоритмы

### Внутренние сортировки
1. **Пузырьковая** (Bubble Sort)
2. **Оптимизированная пузырьковая** (Optimized Bubble Sort)
3. **Шейкерная / перемешиванием** (Shaker / Cocktail Sort)
4. **Глупая / обменом** (Exchange / Stupid Sort)
5. **Выбором** (Selection Sort)
6. **Простая вставками** (Insertion Sort)
7. **Бинарная вставками** (Binary Insertion Sort)
8. **Шелла** (Shell Sort)
9. **Быстрая** (Quick Sort)
10. **Подсчетом** (Counting Sort)
11. **Пирамидальная** (Heap Sort)

### Внешние сортировки
12. **Двухфазное, однофазное и естественное слияние** (Merge Sorts)

---


## 📁 Структура проекта

* `include/` — заголовочные файлы (`.h`)
* `src/` — реализация алгоритмов (`.cpp`)
* `tests/` — тесты Google Test (`test_all_sortings.cpp`)
* `CMakeLists.txt` — конфигурация CMake

---

## 🛠 Сборка и запуск тестов

```bash
cmake -B build -S .
cmake --build build
./build/tests/unit_tests
