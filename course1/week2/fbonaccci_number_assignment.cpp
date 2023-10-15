#include "timer.h"
#include <random>
#define MAX_SIZE 45
#define TIME_LIMIT_CPP 1

int FibonacciNaive(int n) {
    // res: -811192543, Elapsed time 15.606517 s, n: 49
    if (n <= 1) {
        return n;
    }
    return FibonacciNaive(n -1) + FibonacciNaive(n - 2);
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
        std::cout << FibonacciNaive(number) << std::endl;
        t.stop();
        std::cout << "Elapsed time " << std::fixed << t << ", n: " << original_number << std::endl;
    }
}