#include "timer.h"
#include <set>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>


#define MAX_N 1e6
#define MIN_N 1


#define MAX_A 1e5
#define MIN_A 1

#define TIME_LIMIT_CPP 1


// https://www.enjoright_partalgorithms.com/blog/merge-sort-algorithm

int Merge(std::vector<int> &sequence, const int &left, const int &middle, const int &right) {
  // include middle index in left part
  int left_amount = middle - left + 1;
  int right_amount = right - middle;
  int inversions = 0;
//   std::vector<int> left_part(left_amount);
//   std::vector<int> right_part(right_amount);
  std::vector<int> left_part, right_part;
  for (int i = 0; i < left_amount; i ++) {
    left_part.push_back(sequence[left + i]);
  }

  for (int i = 0; i < right_amount; i ++) {
    right_part.push_back(sequence[middle + 1 + i]);
  }

  int i = 0;
  int j = 0;
  int k = left;
  // 0..i.. left_amount  0..j..right_amount
  //   /                   /
  //  v                   v
  //left...........k.............right 
  while (i < left_amount && j < right_amount) {
    if (left_part[i] <= right_part[j]) {
      sequence[k] = left_part[i];
      i++;
    } else {
      sequence[k] = right_part[j];
      int i_ = i;
      inversions += left_amount - i;
      j++;
    }
    k++;
  }
  // boundary condition 1
  while (i < left_amount) {
    sequence[k] = left_part[i];
    i++;
    k++;
  }
  // boundary condition 2
  while (j < right_amount) {
    sequence[k] = right_part[j];
    j++;
    k++;
  }
  return inversions;
}

int NumberOfInversions(std::vector<int> &sequence, const int &front, const int &back) {
  int result = 0;
  if (back < 2) {
    return result;
  }
  // end is index
  int window_size;
  // starting from the recursion base case and increasing twice at every step
  for (window_size = 1; window_size <= back; window_size = 2 * window_size) {
    for (int left = front; left <= back; left = left + 2 * window_size) {
      // traversing all array with window step, which: 2, 4, 8 ..
      int mid = std::min(left + window_size - 1, back); 
      int right = std::min(left + 2 * window_size - 1, back);
      // sorting procedure
      result += Merge(sequence, left, mid, right);
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

int main() {
    int test_number, result_inversions, expected_inversions;
    std::vector<int> result, expected;

    test_number += 1;
    result = {1, 3, 10};
    expected = {1, 3, 10};
    expected_inversions = 0;
    result_inversions = NumberOfInversions(result, 0, result.size() - 1);
    if (result != expected || result_inversions != expected_inversions) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected_inversions << ", got: " 
        << result_inversions << ", res vector " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected_inversions << ", got: " 
        << result_inversions << std::endl;
    }

    test_number += 1;
    result = {5, 2, 6, 3};
    expected = {2, 3, 5, 6};
    expected_inversions = 3;
    result_inversions = NumberOfInversions(result, 0, result.size() - 1);
    if (result != expected || result_inversions != expected_inversions) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected_inversions << ", got: " 
        << result_inversions << ", res vector " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected_inversions << ", got: " 
        << result_inversions << std::endl;
    }    

    test_number += 1;
    result = {10, 3, 1};
    expected = {1, 3, 10};
    expected_inversions = 3;
    result_inversions = NumberOfInversions(result, 0, result.size() - 1);
    if (result != expected || result_inversions != expected_inversions) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected_inversions << ", got: " 
        << result_inversions << ", res vector " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected_inversions << ", got: " 
        << result_inversions << std::endl;
    }

    test_number += 1;
    result = {2, 3, 9, 2, 9};
    expected = {2, 2, 3, 9, 9};
    expected_inversions = 2;
    result_inversions = NumberOfInversions(result, 0, result.size() - 1);
    if (result != expected || result_inversions != expected_inversions) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected_inversions << ", got: " 
        << result_inversions << ", res vector " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected_inversions << ", got: " 
        << result_inversions << std::endl;
    }    


    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(MIN_N, MAX_N);
    std::uniform_int_distribution<std::mt19937::result_type> dist_a(MIN_A, MAX_A);
    while(true) {
      test_number++;
      result.clear();
      // std::set<int> input_data;
      int n = dist_n(rng);
      // std::generate_n(std::back_inserter(result), n, GenerateRandomUniqueA);
      for (int i = 1; i <= n; i++) {
        result.push_back(i);
      }
      auto rng = std::default_random_engine {};
      std::shuffle(std::begin(result), std::end(result), rng);
      t.start();
      result_inversions = NumberOfInversions(result, 0, result.size() - 1);
      t.stop();
      std::cout << "Elapsed time " << std::fixed << std::setprecision(9) << t << ", input size " << result.size() << std::endl;
      if (t.secs() > TIME_LIMIT_CPP) {
          break;
      }
  }
}