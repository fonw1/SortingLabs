#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>

#include "insertion_sort.h"
#include "selection_sort.h"
#include "exchange_sort.h"
#include "bubble_sort.h"
#include "optimized_bubble_sort.h"
#include "binary_insertion_sort.h"
#include "shaker_sort.h"
#include "shell_sort.h"
#include "quick_sort.h"
#include "two_phase_merge_sort.h"
#include "one_phase_merge_sort.h"
#include "natural_merge_sort.h"

template <typename SortFunc>
void testSortingAlgorithm(SortFunc sortFunction) {
    {
        std::vector<int> arr = {};
        sortFunction(arr);
        EXPECT_TRUE(arr.empty());
    }

    {
        std::vector<int> arr = { 42 };
        sortFunction(arr);
        EXPECT_EQ(arr, (std::vector<int>{ 42 }));
    }

    {
        std::vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8 };
        std::vector<int> expected = arr;
        sortFunction(arr);
        EXPECT_EQ(arr, expected);
    }

    {
        std::vector<int> arr = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        sortFunction(arr);
        EXPECT_EQ(arr, expected);
    }

    {
        std::vector<int> arr = { 5, 5, 5, 5, 5 };
        std::vector<int> expected = { 5, 5, 5, 5, 5 };
        sortFunction(arr);
        EXPECT_EQ(arr, expected);
    }

    {
        std::vector<int> arr = { 15, -3, 0, 42, -100, 8, 8, 23, 4 };
        std::vector<int> expected = arr;
        std::sort(expected.begin(), expected.end());
        sortFunction(arr);
        EXPECT_EQ(arr, expected);
    }
}

// ------------------- —≈Ã»Õ¿– 1 -------------------
TEST(SortingTest, InsertionSort) {
    testSortingAlgorithm([](std::vector<int>& v) { insertionSort(v); });
}

TEST(SortingTest, SelectionSort) {
    testSortingAlgorithm([](std::vector<int>& v) { selectionSort(v); });
}

TEST(SortingTest, ExchangeSort) {
    testSortingAlgorithm([](std::vector<int>& v) { exchangeSort(v); });
}

TEST(SortingTest, BubbleSort) {
    testSortingAlgorithm([](std::vector<int>& v) { bubbleSort(v); });
}

TEST(SortingTest, OptimizedBubbleSort) {
    testSortingAlgorithm([](std::vector<int>& v) { optimizedBubbleSort(v); });
}

// ------------------- —≈Ã»Õ¿– 2 -------------------
TEST(SortingTest, BinaryInsertionSort) {
    testSortingAlgorithm([](std::vector<int>& v) { binaryInsertionSort(v); });
}

TEST(SortingTest, ShakerSort) {
    testSortingAlgorithm([](std::vector<int>& v) { shakerSort(v); });
}

// ------------------- —≈Ã»Õ¿– 3 -------------------
TEST(SortingTest, ShellSort) {
    testSortingAlgorithm([](std::vector<int>& v) { shellSort(v); });
}

TEST(SortingTest, QuickSort) {
    testSortingAlgorithm([](std::vector<int>& v) { quickSort(v); });
}

// ------------------- —≈Ã»Õ¿– 4 (¬ÌÂ¯ÌËÂ ÒÓÚËÓ‚ÍË) -------------------
TEST(SortingTest, TwoPhaseMergeSort) {
    testSortingAlgorithm([](std::vector<int>& v) { twoPhaseMergeSort(v); });
}

TEST(SortingTest, OnePhaseMergeSort) {
    testSortingAlgorithm([](std::vector<int>& v) { onePhaseMergeSort(v); });
}

TEST(SortingTest, NaturalMergeSort) {
    testSortingAlgorithm([](std::vector<int>& v) { naturalMergeSort(v); });
}
