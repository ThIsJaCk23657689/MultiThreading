#include <omp.h>
#include <iostream>
#include <chrono>

void Test(int n) {
    int x = 0;
    for (int i = 0; i < 100000; i++) {
        for (int j = 0; j < 100; j++)
            x++;
    }
    std::cout << n << ", ";
}

int main(int argc, char** argv) {

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 10; i++)  {
        Test(i);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> delta = end - start;
    std::cout << "cost time: " << delta.count() << " seconds." << std::endl;

    std::cout << "====================" << std::endl << std::endl;

    start = std::chrono::steady_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        Test(i);
    }
    end = std::chrono::steady_clock::now();
    delta = end - start;
    std::cout << "cost time: " << delta.count() << " seconds." << std::endl;

    return 0;
}
