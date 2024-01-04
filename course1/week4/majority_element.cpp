#include "timer.h"
#include <string>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>


#define MAX_N 1e5
#define MIN_N 1

#define MAX_A 1.0e9
#define MIN_A 1


// Problem Introduction
// Majority rule is a decision rule that selects the alternative which has a majority,
// that is, more than half the votes.
// Given a sequence of elements 𝑎 1 , 𝑎 2 , . . . , 𝑎 𝑛 , you would like to check whether
// it contains an element that appears more than 𝑛/2 times. A naive way to do
// this is the following.
// MajorityElement(𝑎 1 , 𝑎 2 , . . . , 𝑎 𝑛 ):
// for 𝑖 from 1 to 𝑛:
// currentElement ← 𝑎 𝑖
// count ← 0
// for 𝑗 from 1 to 𝑛:
// if 𝑎 𝑗 = currentElement:
// count ← count + 1
// if count > 𝑛/2:
// return 𝑎 𝑖
// return “no majority element”
// The running time of this algorithm is quadratic. Your goal is to use the divide-and-conquer technique to
// design an 𝑂(𝑛 log 𝑛) algorithm.
// Problem Description
// Task. The goal in this code problem is to check whether an input sequence contains a majority element.
// Input Format. The first line contains an integer 𝑛, the next one contains a sequence of 𝑛 non-negative
// integers 𝑎 0 , 𝑎 1 , . . . , 𝑎 𝑛−1 .
// Constraints. 1 ≤ 𝑛 ≤ 10 5 ; 0 ≤ 𝑎 𝑖 ≤ 10 9 for all 0 ≤ 𝑖 < 𝑛.
// Output Format. Output 1 if the sequence contains an element that appears strictly more than 𝑛/2 times,
// and 0 otherwise.
// Sample 1.
// Input:
// 5
// 23922
// Output:
// 1
// 2 is the majority element.
// Sample 2.
// Input:
// 4
// 1234
// Output:
// 0
// There is no majority element in this sequence.


// https://www.enjoyalgorithms.com/blog/find-the-majority-element-in-an-array

typedef std::vector<int> Data_t;
typedef size_t DataPos_t;

std::ostream& operator<< (std::ostream &os, const Data_t &data) {
  size_t idx = 0;
  for (const int &n : data) {
    os << n << (idx < data.size() - 1 ? ":" : "");
    idx++;
  }
  return os;
}

int CountFrequency(
      const Data_t &sequence, const DataPos_t &leftPos, const DataPos_t &rightPos, const int &element) {
  int count = 0;
  for (DataPos_t i = leftPos; i <= rightPos; i++) {
    if (sequence[i] == element) {
      count += 1;
    }
  }
  return count;
}

int FindMajorityElement(
      const Data_t &sequence, const DataPos_t &leftPos, const DataPos_t &rightPos) {
  if (leftPos == rightPos) {
    // one element in sequence
    return sequence[leftPos];
  }
  DataPos_t midPos = leftPos + (rightPos - leftPos) / 2;
  int leftMajorityElement = FindMajorityElement(sequence, leftPos, midPos);
  int rightMajorityElement = FindMajorityElement(sequence, midPos + 1, rightPos);

  if (leftMajorityElement == rightMajorityElement) {
    return leftMajorityElement;
  }

  int leftCount = CountFrequency(sequence, leftPos, rightPos, leftMajorityElement);
  int rightCount = CountFrequency(sequence, leftPos, rightPos, rightMajorityElement);

  int targetCount = (rightPos - leftPos + 1) / 2;
  if (leftCount > targetCount) {
    return leftMajorityElement;
  } else if (rightCount > targetCount) {
    return rightMajorityElement;
  } else {
    return -1;
  }
}

int MajorityElement(const Data_t &sequence) {
  // the initial values for leftPos and rightPos is 0 and n -1
  return FindMajorityElement(sequence, 0, sequence.size() - 1);
}

int main() {
    int result, expected, test_number;
    std::vector<int> input_data;


    test_number += 1;
    input_data = {1 ,1, 1};
    expected = 1;
    result = MajorityElement(input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    input_data = {2, 1, 2};
    expected = 2;
    result = MajorityElement(input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    input_data = {2 ,3, 3, 3, 2};
    expected = 3;
    result = MajorityElement(input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    input_data = {2, 3, 2, 3, 3};
    expected = 3;
    result = MajorityElement(input_data);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }
}