#include <iostream>
#include <vector>

template<typename T>
void quickSort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end);

void runQuickSort()
{
    std::vector<int> arr{5, 6, 7, 3, 1, 9, 2, 4, 8, 0};

    std::cout << "[quick sort]" << std::endl;

    quickSort(arr, 0, 7);

    for (auto& i : arr)
        std::cout << i << " ";
    std::endl;
}

template <typename T>
auto partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) {
    auto pivotVal = *begin;
    auto L = begin + 1;
    auto R = end;

    while (true) {
        /**
         * pivot 기준으로 정렬
         */
        while (*L <= pivotVal && std::distance(L, R) > 0) L++;
        while (*R > pivotVal) R--;

        if (L == R) break;
        else std::iter_swap(L, R); // pivot 위치 이동
    }

    if (pivotVal > *R)
        std::iter_swap(begin, R);

    return R; // 변경된 pivot 위치
}

template<typename T>
void quickSort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) {
    if (std::distance(begin, end) < 1) return;

    auto pivotIter = partition(begin, end);

    quickSort(begin, pivotIter);
    quickSort(pivotIter + 1, end);
}
