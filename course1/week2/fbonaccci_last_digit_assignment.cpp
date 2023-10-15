#include "timer.h"
#include <random>
#define MAX_SIZE 2 * 10e7
#define TIME_LIMIT_CPP 1


int FibonacciLastDigitNaive(int n) {
    if (n <= 1) {
        return n;
    }
    int previous = 0;
    int current = 1;
    // number of iterations: n - 2, i strict lesss than n -1 .. 
    for (int i = 0; i < n - 1; i++) {
        int previous_copy = previous;
        previous = current;
        current = previous_copy + current;
    }
    return current % 10;
}

int main() {
    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, MAX_SIZE);
    while(true) {
        t.start();
        int number = dist(rng);
        int original_number = number;
        std::cout << FibonacciLastDigitNaive(number) << std::endl;
        t.stop();
        std::cout << "Elapsed time " << std::fixed << t << ", n: " << original_number << std::endl;
    }
}