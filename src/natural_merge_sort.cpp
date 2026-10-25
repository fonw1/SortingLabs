#include "natural_merge_sort.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <filesystem>

template <typename T>
void naturalMergeSort(std::vector<T>& arr) {
    if (arr.size() <= 1) return;

    namespace fs = std::filesystem;
    std::string tempDir = "temp_natural";
    fs::create_directories(tempDir);

    std::string mainFile = (fs::path(tempDir) / "main.txt").string();
    {
        std::ofstream out(mainFile);
        for (const auto& x : arr) out << x << "\n";
    }

    std::ifstream in(mainFile);
    arr.clear();
    T val;
    while (in >> val) arr.push_back(val);

    if (!arr.empty()) {
        std::vector<std::vector<T>> series;
        std::vector<T> currentSeries = { arr[0] };
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] >= arr[i - 1]) {
                currentSeries.push_back(arr[i]);
            }
            else {
                series.push_back(currentSeries);
                currentSeries = { arr[i] };
            }
        }
        series.push_back(currentSeries);

        while (series.size() > 1) {
            std::vector<std::vector<T>> nextSeries;
            for (size_t i = 0; i < series.size(); i += 2) {
                if (i + 1 < series.size()) {
                    std::vector<T> merged(series[i].size() + series[i + 1].size());
                    std::merge(series[i].begin(), series[i].end(), series[i + 1].begin(), series[i + 1].end(), merged.begin());
                    nextSeries.push_back(merged);
                }
                else {
                    nextSeries.push_back(series[i]);
                }
            }
            series = nextSeries;
        }
        if (!series.empty()) {
            arr = series[0];
        }
    }

    std::error_code ec;
    // fs::remove_all(tempDir, ec);
}

template void naturalMergeSort<int>(std::vector<int>&);
template void naturalMergeSort<double>(std::vector<double>&);
template void naturalMergeSort<float>(std::vector<float>&);