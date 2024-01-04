#include "timer.h"
#include <string>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>


#define MAX_NK 10000
#define MIN_NK 1

#define MAX_AB 1.0e9
#define MIN_AB 1


// 1
// Binary Search
// Problem Introduction
// In this problem, you will implement the binary search algorithm that allows searching
// very efficiently (even huge) lists, provided that the list is sorted.
// Problem Description
// Task. The goal in this code problem is to implement the binary search algorithm.
// Input Format. The first line of the input contains an integer 𝑛 and a sequence 𝑎 0 < 𝑎 1 < . . . < 𝑎 𝑛−1
// of 𝑛 pairwise distinct positive integers in increasing order. The next line contains an integer 𝑘 and 𝑘
// positive integers 𝑏 0 , 𝑏 1 , . . . , 𝑏 𝑘−1 .
// Constraints. 1 ≤ 𝑛, 𝑘 ≤ 10 4 ; 1 ≤ 𝑎 𝑖 ≤ 10 9 for all 0 ≤ 𝑖 < 𝑛; 1 ≤ 𝑏 𝑗 ≤ 10 9 for all 0 ≤ 𝑗 < 𝑘;
// Output Format. For all 𝑖 from 0 to 𝑘 − 1, output an index 0 ≤ 𝑗 ≤ 𝑛 − 1 such that 𝑎 𝑗 = 𝑏 𝑖 or −1 if there
// is no such index.
// Sample 1.
// Input:
// 5 1 5 8 12 13
// 5 8 1 23 1 11
// Output:
// 2 0 -1 0 -1
// In this sample, we are given an increasing sequence 𝑎 0 = 1, 𝑎 1 = 5, 𝑎 2 = 8, 𝑎 3 = 12, 𝑎 4 = 13 of length
// five and five keys to search: 8, 1, 23, 1, 11. We see that 𝑎 2 = 8 and 𝑎 0 = 1, but the keys 23 and 11 do
// not appear in the sequence 𝑎. For this reason, we output a sequence 2, 0, −1, 0, −1.

std::ostream& operator<< (std::ostream &os, const std::vector<int> &data) {
    size_t idx = 0;
    for (const int &n : data) {
        os << n << (idx < data.size() - 1 ? ":" : "");
        idx++;
    }
    return os;
}

int BinarySearch(const int &target, const std::vector<int> sequence) {
    int result = -1;
    if (sequence.empty()) {
        return result;
    }
    if (sequence.back() < target || sequence.front() > target) {
        return result;
    }
    size_t idx = (sequence.size()  - 1) / 2; // <= sequence center idx
    size_t last_idx = 0;
    // int k = 0;
    while (idx >= 0 && idx < sequence.size()) {
        // k += 1;
        // if (sequence[idx] == target || k > 5) {
        if (sequence[idx] == target) {

            if (sequence[idx] == target) {
              result = idx;  
            }
            break;
        }
        if (sequence[idx] > target) {
            last_idx = idx;
            idx = idx / 2;
            int di = abs(last_idx - idx);
            if (di <= 2 && sequence[idx] < target) {
                if (di && sequence[idx  + 1] == target) { 
                    result = idx + 1;
                }
                break;
            }
        } else {
            //  idx = idx + (size - idx ) / 2
            last_idx = idx;
            idx = (sequence.size() + idx) / 2;
            int di = abs(last_idx - idx);
            if (di <= 2 && sequence[idx] > target) {
                if (di && sequence[idx + 1] == target) { 
                    result = idx - 1;
                }
                break;
            }
        }
        // std::cout << idx << ":" << target << ":" << sequence[idx] << ":" << last_idx << "::" << sequence << std::endl;
    }
    return result;
}

std::vector<int> FindAllTargetNumbers(const std::vector<int> targets, const std::vector<int> sequence) {
    std::vector<int> result;
    for (auto t : targets) {
        result.push_back(BinarySearch(t, sequence));
        // std::cout << result << std::endl;
    }

    return result;
}

int main() {
    int result, expected, test_number, target_number;
    std::vector<int> input_data, targets, expected_idxs, result_idxs;


    test_number += 1;
    input_data = {1 ,2, 3};
    target_number = 6;
    expected = -1;
    result = BinarySearch(target_number, input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    input_data = {};
    target_number = 6;
    expected = -1;
    result = BinarySearch(target_number, input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    input_data = {6, 7, 8};
    target_number = 6;
    expected = 0;
    result = BinarySearch(target_number, input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    input_data = {3, 5, 6};
    target_number = 6;
    expected = 2;
    result = BinarySearch(target_number, input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    input_data = {1, 2, 3, 4, 6, 8};
    target_number = 6;
    expected = 4;
    result = BinarySearch(target_number, input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    input_data = {5, 6, 7, 8, 9, 10};
    target_number = 6;
    expected = 1;
    result = BinarySearch(target_number, input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    input_data = {4, 5, 7, 8, 9, 10};
    target_number = 6;
    expected = -1;
    result = BinarySearch(target_number, input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    input_data = {1, 5, 8, 12, 13};
    targets = {8, 1, 23, 1, 11};
    expected_idxs = {2, 0, -1, 0, -1};

    result_idxs = FindAllTargetNumbers(targets, input_data);

    if (result_idxs != expected_idxs) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << "\nexpected: "  << expected_idxs << ", got: " << result_idxs;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << "\nexpected: "  << expected_idxs << ", got: " 
        << result_idxs << std::endl;
    }


    test_number += 1;
    input_data = {1, 5, 8, 12, 13};
    targets = {1, 5, 8, 12, 13};
    expected_idxs = {0, 1, 2, 3, 4};

    result_idxs = FindAllTargetNumbers(targets, input_data);

    if (result_idxs != expected_idxs) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << "\nexpected: "  << expected_idxs << ", got: " << result_idxs;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << "\nexpected: "  << expected_idxs << ", got: " 
        << result_idxs << std::endl;
    }
}