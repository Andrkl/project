#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

int totalSum = 0;

void calculateSum(const std::vector<int>& arr, int start, int end) {
    int localSum = 0;
    for (int i = start; i < end; ++i) {
        localSum += arr[i];
    }

    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    totalSum += localSum;
}

int main() {
    int N = 100; 
    int M = 5; 

    std::vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 100; 
    }

    std::vector<std::thread> threads;
    int chunkSize = N / M;

    for (int i = 0; i < M; ++i) {
        int start = i * chunkSize;
        int end = (i == M - 1) ? N : start + chunkSize;
        threads.emplace_back(calculateSum, std::ref(arr), start, end);
    }

    for (std::thread& t : threads) {
        t.join();
    }

    std::cout << "Общая сумма элементов массива: " << totalSum << std::endl;

    return 0;
}