#include "timer.h"
#include <random>
#include <sstream>

// /usr/bin/time output/... 
#define MIN_VALUE_n 1
#define MAX_VALUE_n 1 * 1000000000000000000
#define MIN_VALUE_m 2
#define MAX_VALUE_m 1 * 1000
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

uint64_t FibonacciModulo(const uint64_t &n, const uint64_t &m){
    uint64_t pi = PisanoPeriod(m);
    uint64_t idx = n % pi;
    // std::cout << "Pi " << pi << ":" << idx << std::endl;
    if (idx <= 1) {
        return idx % m;
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
    return f_curr % m;
}


int main() {
    uint64_t n = 10;

    // f(10) = 55

    uint64_t m = 2;
    uint64_t expected = 1;
    auto result = FibonacciModulo(n, m);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST m: " << m << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    m = 3;
    expected = 1;
    result = FibonacciModulo(n, m);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST m: " << m << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    m = 4;
    expected = 3;
    result = FibonacciModulo(n, m);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST m: " << m << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    m = 5;
    expected = 0;
    result = FibonacciModulo(n, m);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST m: " << m << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    m = 6;
    expected = 1;
    result = FibonacciModulo(n, m);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST m: " << m << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }


    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(MIN_VALUE_n, MAX_VALUE_n);
    std::uniform_int_distribution<std::mt19937::result_type> dist_m(MIN_VALUE_m, MAX_VALUE_m);
    while(true) {
        t.start();
        int n = dist_n(rng);
        int m = dist_m(rng);
        result = FibonacciModulo(n, m);
        t.stop();
        std::cout << "Elapsed time " << std::fixed << t << std::endl;
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
    }
}