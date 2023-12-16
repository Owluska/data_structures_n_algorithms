#include "timer.h"
#include <set>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>

// Problem Introduction
// You are organizing a funny competition for children. As a prize fund you have 𝑛
// candies. You would like to use these candies for top 𝑘 places in a competition
// with a natural restriction that a higher place gets a larger number of candies.
// To make as many children happy as possible, you are going to find the largest
// value of 𝑘 for which it is possible.
// Problem Description
// Task. The goal of this problem is to represent a given positive integer 𝑛 as a sum of as many pairwise
// distinct positive integers as possible. That is, to find the maximum 𝑘 such that 𝑛 can be written as
// 𝑎 1 + 𝑎 2 + · · · + 𝑎 𝑘 where 𝑎 1 , . . . , 𝑎 𝑘 are positive integers and 𝑎 𝑖 ̸ = 𝑎 𝑗 for all 1 ≤ 𝑖 < 𝑗 ≤ 𝑘.
// Input Format. The input consists of a single integer 𝑛.
// Constraints. 1 ≤ 𝑛 ≤ 10 9 .
// Output Format. In the first line, output the maximum number 𝑘 such that 𝑛 can be represented as a sum
// of 𝑘 pairwise distinct positive integers. In the second line, output 𝑘 pairwise distinct positive integers
// that sum up to 𝑛 (if there are many such representations, output any of them).
// Sample 1.
// Input:
// 6
// Output:
// 3
// 123
// Sample 2.
// Input:
// 8
// Output:
// 3
// 125
// Sample 3.
// Input:
// 2
// Output:
// 1
// 2

#define MAX_N 1e9
#define MIN_N 1


#define TIME_LIMIT_CPP 1


std::set<int> MaxNumberOfPrizes(const int &n) {
    std::set<int> prizes;
    int current_number = n;
    for (int i = 1; i <= current_number; i++) {
        if (!prizes.count(i)) {
            int next_result = current_number - i;
            if (prizes.count(next_result) || next_result == i) {
                continue;
            }
            prizes.insert(i);
            current_number -= i;
        }
        // std::cout << current_number << ":" << i << std::endl;
    }
    return prizes;
}

std::ostream& operator<< (std::ostream &os, const std::set<int> &data) {
    size_t idx = 0;
    for (const int &n : data) {
        os << n << (idx < data.size() - 1 ? ":" : "");
        idx++;
    }
    return os;
}

int main () {
    int test_n = 0;
    int n = 0;
    std::set<int> expected, result;

    test_n += 1;
    n = 6;
    expected = {
        1, 2, 3
    };
    result = MaxNumberOfPrizes(n);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    n = 8;
    expected = {
        1, 2, 5
    };
    result = MaxNumberOfPrizes(n);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    n = 2;
    expected = {
        2
    };
    result = MaxNumberOfPrizes(n);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    n = 1;
    expected = {
        1
    };
    result = MaxNumberOfPrizes(n);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    n = 10;
    expected = {
        1, 2, 3, 4
    };
    result = MaxNumberOfPrizes(n);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    n = 12;
    expected = {
        1, 2, 3, 6
    };
    result = MaxNumberOfPrizes(n);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }      

    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(MIN_N, MAX_N);
    while(true) {
        t.start();
        n = dist_n(rng);
        auto result = MaxNumberOfPrizes(n);
        t.stop();
        std::cout << "Elapsed time " << std::fixed << std::setprecision(9) << t;
        if (n < 20) {
            std::cout << ", input [" << n << "], output " << result << std::endl;
        } else {
            std::cout << std::endl;
        }
       
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
    }
}