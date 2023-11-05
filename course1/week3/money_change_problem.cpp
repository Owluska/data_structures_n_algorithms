#include "timer.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>

// Task. The goal in this problem is to find the minimum number of coins needed to change the input value
// (an integer) into coins with denominations 1, 5, and 10.
// Input Format. The input consists of a single integer 𝑚.
// Constraints. 1 ≤ 𝑚 ≤ 10^3 .
// Output Format. Output the minimum number of coins with denominations 1, 5, 10 that changes 𝑚.
// Sample 1.
// Input:
// 2
// Output:
// 2
// 2 = 1 + 1.
// Sample 2.
// Input:
// 28
// Output:
// 6
// 28 = 10 + 10 + 5 + 1 + 1 + 1.

#define MAX_N 10e+3
#define MIN_N 1
#define TIME_LIMIT_CPP 1

#define COIN_ONE 1
#define COIN_FIVE 5
#define COIN_TEN 10


int MinimumCoinsNumberForChange(const int &m) {
    // inputs starts from one
    int result = 0;
    int remainder = m;
    while (remainder != 0) {
        result += 1;
        if (remainder - COIN_TEN >= 0 && m != COIN_TEN) {
            remainder -= COIN_TEN;
        } else if (remainder - COIN_FIVE >= 0 && m != COIN_FIVE) {
            remainder -= COIN_FIVE;
        } else  { //(remainder - COIN_ONE >= 0)
            remainder -= COIN_ONE;
        }
    }
    return result;
}

int main () {
    for (int m = 1; m < COIN_FIVE; m++) {
        int expected = m;
        auto result = MinimumCoinsNumberForChange(m);
        if (result != expected) {
            std::stringstream err_msg;
            err_msg << "FAILED TEST n: " << m << ", expected: "  << expected << ", got: " << result;
            throw std::logic_error(err_msg.str());
        }
    }

    int m = COIN_FIVE;
    int expected = 5;
    auto result = MinimumCoinsNumberForChange(m);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST n: " << m << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    m = COIN_TEN;
    expected = 2;
    result = MinimumCoinsNumberForChange(m);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST n: " << m << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    m = 2;
    expected = 2;
    result = MinimumCoinsNumberForChange(m);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST n: " << m << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    m = 28;
    expected = 6;
    result = MinimumCoinsNumberForChange(m);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST n: " << m << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(MIN_N, MAX_N);
    while(true) {
        t.start();
        m = dist(rng);
        auto result = MinimumCoinsNumberForChange(m);
        t.stop();
        std::cout << "Elapsed time " << std::fixed << std::setprecision(9) << t << ", input [" << m << "], output " << result << std::endl;
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
    }
}