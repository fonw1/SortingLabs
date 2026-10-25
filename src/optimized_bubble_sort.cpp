#include "optimized_bubble_sort.h"
#include <utility>

template <typename T>
void optimizedBubbleSort(std::vector<T>& arr) {
    int n = arr.size();
    bool swapped = true;
    for (int i = 0; i < n - 1 && swapped; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
    }
}

template void optimizedBubbleSort<int>(std::vector<int>&);
template void optimizedBubbleSort<double>(std::vector<double>&);