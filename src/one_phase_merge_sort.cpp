#include "one_phase_merge_sort.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <utility>

template <typename T>
void onePhaseMergeSort(std::vector<T>& arr) {
    if (arr.size() <= 1) return;

    namespace fs = std::filesystem;
    std::string tempDir = "temp_one_phase";
    fs::create_directories(tempDir);

    std::string mainFile = (fs::path(tempDir) / "main.txt").string();
    std::string f1 = (fs::path(tempDir) / "f1.txt").string();
    std::string f2 = (fs::path(tempDir) / "f2.txt").string();
    std::string f3 = (fs::path(tempDir) / "f3.txt").string();
    std::string f4 = (fs::path(tempDir) / "f4.txt").string();

    
    {
        std::ofstream out(mainFile);
        for (const auto& val : arr) out << val << "\n";
    }

    std::size_t runSize = 2;
    std::size_t runsCount = 0;

    
    {
        std::ifstream in(mainFile);
        std::ofstream out1(f1);
        std::ofstream out2(f2);
        std::vector<T> chunk;
        T val;
        bool toFirst = true;

        while (in >> val) {
            chunk.push_back(val);
            if (chunk.size() >= runSize) {
                std::sort(chunk.begin(), chunk.end());
                auto& target = toFirst ? out1 : out2;
                for (const auto& x : chunk) target << x << "\n";
                chunk.clear();
                toFirst = !toFirst;
                ++runsCount;
            }
        }
        if (!chunk.empty()) {
            std::sort(chunk.begin(), chunk.end());
            auto& target = toFirst ? out1 : out2;
            for (const auto& x : chunk) target << x << "\n";
            ++runsCount;
        }
    }

    if (runsCount <= 1) {
        std::error_code ec;
        fs::remove_all(tempDir, ec);
        return;
    }

    std::string src1 = f1, src2 = f2;
    std::string dst1 = f3, dst2 = f4;
    std::size_t len = runSize;

    
    while (runsCount > 1) {
        std::ifstream in1(src1);
        std::ifstream in2(src2);
        std::ofstream out1(dst1);
        std::ofstream out2(dst2);

        T val1, val2;
        bool has1 = static_cast<bool>(in1 >> val1);
        bool has2 = static_cast<bool>(in2 >> val2);

        bool writingToFirstDst = true;

        
        while (has1 || has2) {
            auto& currentDst = writingToFirstDst ? out1 : out2;
            std::size_t c1 = 0, c2 = 0;

            while (has1 && c1 < len && has2 && c2 < len) {
                if (val1 <= val2) {
                    currentDst << val1 << "\n";
                    has1 = static_cast<bool>(in1 >> val1);
                    ++c1;
                }
                else {
                    currentDst << val2 << "\n";
                    has2 = static_cast<bool>(in2 >> val2);
                    ++c2;
                }
            }
            while (has1 && c1 < len) {
                currentDst << val1 << "\n";
                has1 = static_cast<bool>(in1 >> val1);
                ++c1;
            }
            while (has2 && c2 < len) {
                currentDst << val2 << "\n";
                has2 = static_cast<bool>(in2 >> val2);
                ++c2;
            }
            writingToFirstDst = !writingToFirstDst;
        }

        runsCount = (runsCount + 1) / 2;
        len *= 2;

        
        std::swap(src1, dst1);
        std::swap(src2, dst2);
    }

    
    arr.clear();
    {
        std::ifstream finalIn1(src1);
        T val;
        while (finalIn1 >> val) arr.push_back(val);
        std::ifstream finalIn2(src2);
        while (finalIn2 >> val) arr.push_back(val);
    }
    std::sort(arr.begin(), arr.end()); 

    std::error_code ec;
    // fs::remove_all(tempDir, ec);
}

template void onePhaseMergeSort<int>(std::vector<int>&);
template void onePhaseMergeSort<double>(std::vector<double>&);
template void onePhaseMergeSort<float>(std::vector<float>&);