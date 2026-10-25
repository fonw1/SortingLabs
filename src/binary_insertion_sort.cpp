#include "binary_insertion_sort.h"

template <typename T>
void binaryInsertionSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int left = 0, right = i - 1;
        int pos = i;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > key) {
                pos = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }

        for (int j = i - 1; j >= pos; --j) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = key;
    }
}

template void binaryInsertionSort<int>(std::vector<int>&);
template void binaryInsertionSort<double>(std::vector<double>&);