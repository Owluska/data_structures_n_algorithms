#include "timer.h"
#include <random>
#include <sstream>
#include <map>
#include <iomanip>


#define MAX_N 10e+18
#define MIN_N 0
#define TIME_LIMIT_CPP 1

uint64_t PisanoPeriod(const uint64_t &m) {
    uint64_t pi_prev = 0;
    uint64_t pi_curr = 1;
    // The length of a Pisano Period for
    // a given m ranges from 3 to m * m
    for (uint64_t i = 0; i <= m * m; i++) {
        // f ~ pi * m 
        // mod(1) = 1 and mod(0) = 0
        uint64_t tmp = (pi_prev + pi_curr) % m;
        // std::cout << pi_prev << ":" << pi_curr << ":" <<  tmp << std::endl;
        pi_prev = pi_curr;
        pi_curr = tmp;
        // Pisano sequence always starts from 01
        if (pi_prev == 0 && pi_curr == 1) {
            // i starts from zero
            return i + 1;
        }

    }
    return 0;
}


uint64_t LastDigitFibonacciNumbersSumm(const uint64_t &n) {
    // https://www.youtube.com/watch?v=pakNmC9pV-Q&ab_channel=FlammableMaths
    // SUM(Fn) = Fn+2 - 1 
    auto n_ = n + 2;
    uint64_t pi = PisanoPeriod(10);
    uint64_t idx = n_ % pi;
    // std::cout << "Pi " << pi << ":" << idx << std::endl;
    if (idx <= 1) {
        return 0;
    }
    uint64_t f_prev = 0;
    uint64_t f_curr = 1;
    // f0 and f1 wer processed previouslu
    for (uint64_t i = 0; i < idx - 1; i++) {
        uint64_t tmp = (f_prev + f_curr);
        f_prev = f_curr;
        f_curr = tmp;
        // std::cout << f_curr << std::endl;
    }
    auto sum = f_curr - 1;
    return f_curr % 10;
}


int main() {
    uint64_t n = 10;

    // f(10) = 55

    std::map<int, int> fibonaccies = {
        {0, 0},
        {1, 1},
        {2, 1},
        {3, 2},
        {4, 3},
        {5, 5},
        {6, 8},
        {7, 13},
        {8, 21},
        {9, 34},
        {10, 55},
        {100, 5},
    };
    for (int i = 0; i < 8; i++) {
        uint64_t expected = fibonaccies[i + 2] % 10;
        auto result = LastDigitFibonacciNumbersSumm(i);
        if (result != expected) {
            std::stringstream err_msg;
            err_msg << "FAILED TEST m: " << i << ", expected: "  << expected << ", got: " << result;
            throw std::logic_error(err_msg.str());
        }
    }
    int i = 98;
    uint64_t expected = fibonaccies[i + 2] % 10;
    auto result = LastDigitFibonacciNumbersSumm(i);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST m: " << i << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(MIN_N, MAX_N);
    while(true) {
        t.start();
        uint64_t n = dist_n(rng);
        auto result = LastDigitFibonacciNumbersSumm(n);
        t.stop();
        std::cout << "Elapsed time " << t << ", input " << n << ", output " << result << std::endl;
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
    }
}