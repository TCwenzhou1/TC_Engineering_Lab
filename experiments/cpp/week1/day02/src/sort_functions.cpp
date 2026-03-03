#include <iostream>
#include <vector>
#include <utility>  // for std::swap

// 打印数组（每轮输出用）
static void printVec(const std::vector<int>& a, const char* tag, int round) {
    std::cout << tag << " round " << round << ": ";
    for (int x : a) std::cout << x << ' ';
    std::cout << '\n';
}

// 冒泡排序：相邻交换，把最大值“冒”到末尾
void bubbleSort(std::vector<int>& a, bool verbose = true) {
    const int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (verbose) printVec(a, "bubble", i + 1);
        if (!swapped) break; // 已有序可提前结束
    }
}

// 选择排序：每轮从未排序区找最小值，交换到前面
void selectionSort(std::vector<int>& a, bool verbose = true) {
    const int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[minIdx]) minIdx = j;
        }
        if (minIdx != i) std::swap(a[i], a[minIdx]);
        if (verbose) printVec(a, "select", i + 1);
    }
}

/*
对比总结（写在代码里，满足 Day2 要求）：
- 冒泡：通过“相邻交换”把最大值一轮轮推到末尾；交换次数可能很多
- 选择：每轮只做一次“选最小 + 交换”；比较次数固定，交换次数更少
复杂度：
- 两者时间复杂度都是 O(n^2)（双重循环）
- 空间复杂度 O(1)（原地排序）
*/

int main() {
    std::vector<int> data{7, 3, 9, 2, 5, 1, 8};

    std::cout << "Original: ";
    for (int x : data) std::cout << x << ' ';
    std::cout << "\n\n";

    auto a1 = data;
    std::cout << "[Bubble Sort]\n";
    bubbleSort(a1, true);

    std::cout << "\n";

    auto a2 = data;
    std::cout << "[Selection Sort]\n";
    selectionSort(a2, true);

    return 0;
}