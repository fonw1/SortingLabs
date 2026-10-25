#include "two_phase_merge_sort.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <filesystem>

template <typename T>
void twoPhaseMergeSort(std::vector<T>& arr) {
    if (arr.size() <= 1) return;

    namespace fs = std::filesystem;
    std::string tempDir = "temp_two_phase";
    fs::create_directories(tempDir);

    std::string srcFile = (fs::path(tempDir) / "src.txt").string();
    std::string fileB = (fs::path(tempDir) / "b.txt").string();
    std::string fileC = (fs::path(tempDir) / "c.txt").string();
    std::string nextSrc = (fs::path(tempDir) / "next_src.txt").string();

    {
        std::ofstream out(srcFile);
        for (const auto& val : arr) out << val << "\n";
    }

    std::size_t runSize = 2;
    std::size_t runsCount = 0;

    {
        std::ifstream in(srcFile);
        std::ofstream bOut(fileB);
        std::ofstream cOut(fileC);
        std::vector<T> chunk;
        T val;
        bool toB = true;

        while (in >> val) {
            chunk.push_back(val);
            if (chunk.size() >= runSize) {
                std::sort(chunk.begin(), chunk.end());
                auto& target = toB ? bOut : cOut;
                for (const auto& x : chunk) target << x << "\n";
                chunk.clear();
                toB = !toB;
                ++runsCount;
            }
        }
        if (!chunk.empty()) {
            std::sort(chunk.begin(), chunk.end());
            auto& target = toB ? bOut : cOut;
            for (const auto& x : chunk) target << x << "\n";
            ++runsCount;
        }
    }

    if (runsCount == 0) {
        fs::remove_all(tempDir);
        return;
    }

    std::size_t len = runSize;
    while (runsCount > 1) {
        std::ifstream bIn(fileB);
        std::ifstream cIn(fileC);
        std::ofstream out(nextSrc);

        T bVal, cVal;
        bool hasB = static_cast<bool>(bIn >> bVal);
        bool hasC = static_cast<bool>(cIn >> cVal);

        while (hasB || hasC) {
            std::size_t bWritten = 0, cWritten = 0;
            while (hasB && bWritten < len && hasC && cWritten < len) {
                if (bVal <= cVal) {
                    out << bVal << "\n";
                    hasB = static_cast<bool>(bIn >> bVal);
                    ++bWritten;
                }
                else {
                    out << cVal << "\n";
                    hasC = static_cast<bool>(cIn >> cVal);
                    ++cWritten;
                }
            }
            while (hasB && bWritten < len) {
                out << bVal << "\n";
                hasB = static_cast<bool>(bIn >> bVal);
                ++bWritten;
            }
            while (hasC && cWritten < len) {
                out << cVal << "\n";
                hasC = static_cast<bool>(cIn >> cVal);
                ++cWritten;
            }
        }

        out.close();
        srcFile = nextSrc;
        runsCount = (runsCount + 1) / 2;
        len *= 2;

        if (runsCount > 1) {
            std::ifstream in(srcFile);
            std::ofstream bOut(fileB);
            std::ofstream cOut(fileC);
            T val;
            bool toB = true;
            std::size_t currentLen = len;
            std::size_t written = 0;

            while (in >> val) {
                if (written >= currentLen) {
                    toB = !toB;
                    written = 0;
                }
                (toB ? bOut : cOut) << val << "\n";
                ++written;
            }
        }
    }

    arr.clear();
    {
        std::ifstream finalIn(srcFile);
        T val;
        while (finalIn >> val) {
            arr.push_back(val);
        }
    }


    if (arr.empty() && !srcFile.empty()) {
    }

    std::error_code ec;
    // fs::remove_all(tempDir, ec);
}

template void twoPhaseMergeSort<int>(std::vector<int>&);
template void twoPhaseMergeSort<double>(std::vector<double>&);
template void twoPhaseMergeSort<float>(std::vector<float>&);