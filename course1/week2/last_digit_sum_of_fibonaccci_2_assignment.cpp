#include "timer.h"
#include <random>
#include <sstream>
#include <map>


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

void LastTwoFibonacciNumbers(const uint64_t &n, uint64_t &f_m1, uint64_t &f_m2) {
    f_m2 = 0;
    f_m1 = 0;
    if (n == 0) {
        return;
    }
    f_m1 = 1;
    if (n == 1) {
        return;
    }
    uint64_t f = 0;
    for (uint64_t i = 1; i < n; i++) {
        f = (f_m1 + f_m2);
        f_m2 = f_m1;
        f_m1 = f;
    }
    return;
}



uint64_t LastDigitFibonacciNumbersSqyaresSumm(const uint64_t &n) {
    if (n == 0) {
        return 0;
    }
    uint64_t pi = PisanoPeriod(10);
    uint64_t idx = n % pi;
    uint64_t fib, previous_fib;
    LastTwoFibonacciNumbers(idx, fib, previous_fib);
    auto sum = fib * (fib + previous_fib);
    return sum % 10;
}


int main() {

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
    uint64_t n = 0;
    uint64_t expected  = 0;
    for (int n = 0; n < 8; n++) {
        expected = fibonaccies[n];
        uint64_t f, f_pre;
        uint64_t exp1 = fibonaccies[n];
        uint64_t exp2 = fibonaccies[n - 1];
        LastTwoFibonacciNumbers(n, f, f_pre);
        if (f != exp1 || f_pre != exp2) {
            std::stringstream err_msg;
            err_msg << "FAILED TEST n: " << n << ", expected: ["  << exp1 << ", " << exp2  << "], got: [" << f << ", " << f_pre << "]";
            throw std::logic_error(err_msg.str());
        }
    }
    // new variable with the same name will be created in loop
    for (int n = 0; n < 8; n++) {
        if (n == 0) {
            expected = 0;
        } else {
            expected = (fibonaccies[n] * (fibonaccies[n] + fibonaccies[n - 1])) % 10;
        }
        auto result = LastDigitFibonacciNumbersSqyaresSumm(n);
        if (result != expected) {
            std::stringstream err_msg;
            err_msg << "FAILED TEST n: " << n << ", expected: "  << expected << ", got: " << result;
            throw std::logic_error(err_msg.str());
        }
    }
    n = 7;
    expected = 3;
    auto result = LastDigitFibonacciNumbersSqyaresSumm(n);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST n: " << n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    n = 73;
    expected = 1;
    result = LastDigitFibonacciNumbersSqyaresSumm(n);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST n: " << n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    n = 1234567890;
    expected = 0;
    result = LastDigitFibonacciNumbersSqyaresSumm(n);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST n: " << n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(MIN_N, MAX_N);
    while(true) {
        t.start();
        n = dist(rng);
        auto result = LastDigitFibonacciNumbersSqyaresSumm(n);
        t.stop();
        std::cout << "Elapsed time " << t << ", input [" << n << "], output " << result << std::endl;
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
    }
}