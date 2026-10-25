#include "quick_sort.h"
#include <utility>

template <typename T>
static void quickSortImpl(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quickSortImpl(arr, low, pi - 1);
        quickSortImpl(arr, pi + 1, high);
    }
}

template <typename T>
void quickSort(std::vector<T>& arr) {
    if (!arr.empty()) {
        quickSortImpl(arr, 0, static_cast<int>(arr.size()) - 1);
    }
}

template void quickSort<int>(std::vector<int>&);
template void quickSort<double>(std::vector<double>&);