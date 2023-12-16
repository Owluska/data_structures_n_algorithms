#include "timer.h"
#include <string>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>

// Problem Introduction
// As the last question of a successful interview, your boss gives you a few pieces of paper
// with numbers on it and asks you to compose a largest number from these numbers. The
// resulting number is going to be your salary, so you are very much interested in maximizing
// this number. How can you do this?
// In the lectures, we considered the following algorithm for composing the largest number out of the given
// single-digit numbers.
// LargestNumber(Digits):
// answer ← empty string
// while Digits is not empty:
// maxDigit ← −∞
// for digit in Digits:
// if digit ≥ maxDigit:
// maxDigit ← digit
// append maxDigit to answer
// remove maxDigit from Digits
// return answer
// Unfortunately, this algorithm works only in case the input consists of single-digit numbers. For example, for
// an input consisting of two integers 23 and 3 (23 is not a single-digit number!) it returns 233, while the largest
// number is in fact 323. In other words, using the largest number from the input as the first number is not a
// safe move.
// Your goal in this problem is to tweak the above algorithm so that it works not only for single-digit
// numbers, but for arbitrary positive integers.
// Problem Description
// Task. Compose the largest number out of a set of integers.
// Input Format. The first line of the input contains an integer 𝑛. The second line contains integers
// 𝑎 1 , 𝑎 2 , . . . , 𝑎 𝑛 .
// Constraints. 1 ≤ 𝑛 ≤ 100; 1 ≤ 𝑎 𝑖 ≤ 10 3 for all 1 ≤ 𝑖 ≤ 𝑛.
// Output Format. Output the largest number that can be composed out of 𝑎 1 , 𝑎 2 , . . . , 𝑎 𝑛 .
// Sample 1.
// Input:
// 2
// 21 2
// Output:
// 221
// Note that in this case the above algorithm also returns an incorrect answer 212.
// 11Sample 2.
// Input:
// 5
// 94619
// Output:
// 99641
// In this case, the input consists of single-digit numbers only, so the algorithm above computes the right
// answer.
// Sample 3.
// Input:
// 3
// 23 39 92
// Output:
// 923923
// As a coincidence, for this input the above algorithm produces the right result, though the input does
// not have any single-digit numbers.

#define MAX_N 100
#define MIN_N 1

#define MAX_A 1000
#define MIN_A 1


#define TIME_LIMIT_CPP 1

bool IsMore(const int &n1, const int &n2) {
    std::string n1_ = std::to_string(n1) +  std::to_string(n2);
    std::string n2_ = std::to_string(n2) + std::to_string(n1);
    return n1_ > n2_;
}

std::string GetLargestNumber(std::vector<int> &numbers) {
    std::string result;
    while(numbers.size()) {
        std::vector<int>::iterator max_number_pos = numbers.end();
        int max_number = 1;
        for (auto it = numbers.begin(); it != numbers.end(); it++) {
            int number = *it;
            if (IsMore(number, max_number)) {
                max_number = number;
                max_number_pos = it;
            }
            std::string common_digit;
        }
        if (result.empty()) {
            result = std::to_string(max_number);
        } else {
            result += std::to_string(max_number);
        }
        // std::cout << str_number << std::endl;
        // std::cout << numbers.size() << std::endl;
        if (max_number_pos != numbers.end()) {
            numbers.erase(max_number_pos);
        } else {
            break;
        }
    }

    return result;
}

std::ostream& operator<< (std::ostream &os, const std::vector<int> &data) {
    size_t idx = 0;
    for (const int &n : data) {
        os << n << (idx < data.size() - 1 ? ":" : "");
        idx++;
    }
    return os;
}

int main () {
    int test_n = 0;
    std::vector<int> input;
    std::string expected, result;

    test_n += 1;
    input = {
        21,
        2
    };
    expected = "221";
    result = GetLargestNumber(input);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    input = {
        9,
        4,
        6,
        1,
        9
    };
    expected = "99641";
    result = GetLargestNumber(input);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }
    test_n += 1;
    input = {
        23,
        39,
        92
    };
    expected = "923923";
    result = GetLargestNumber(input);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }  

    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(MIN_N, MAX_N);
    std::uniform_int_distribution<std::mt19937::result_type> dist_a(MIN_A, MAX_A);
    while(true) {
        t.start();
        int n = dist_n(rng);
        input.clear();
        for (int i = 0; i < n; i++) {
            int a = dist_a(rng);
            input.push_back(a);
        }
        auto input_cp = input;
        auto result = GetLargestNumber(input);
        t.stop();
        std::cout << "Elapsed time " << std::fixed << std::setprecision(9) << t;
        if (n < 20) {
            std::cout << ", input [" << input_cp << "], output " << result << std::endl;
        } else {
            std::cout << std::endl;
        }
       
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
    }
}