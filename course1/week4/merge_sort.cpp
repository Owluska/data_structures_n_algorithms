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

void Merge(std::vector<int> &sequence, const int &left, const int &middle, const int &right) {
  // include middle index in left part
  int left_amount = middle - left + 1;
  int right_amount = right - middle;
  std::vector<int> left_part(left_amount);
  std::vector<int> right_part(right_amount);
  for (int i = 0; i < left_amount; i ++) {
    left_part[i] = sequence[left + i];
  }

  for (int i = 0; i < right_amount; i ++) {
    right_part[i] = sequence[middle + 1 + i];
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
}

void MergeSort(std::vector<int> &sequence, const int &left, const int &right) {
  // right is index, not size!
  if (right <= left) {
    return;
  }
  // othrewise we could get too big number
  int middle = left + (right - left) / 2;
  // divide skipping mid_idleft_part
  MergeSort(sequence, left, middle);
  MergeSort(sequence, middle + 1, right);
  Merge(sequence, left, middle, right);
}

void MergeSortIterative(std::vector<int> &sequence, const int &front, const int &end) {
  // end is index
  int window_size;
  // starting from the recursion base case and increasing twice at every step
  for (window_size = 1; window_size <= end; window_size = 2 * window_size) {
    for (int left = front; left <= end; left = left + 2 * window_size) {
      // traversing all array with window step, which: 2, 4, 8 ..
      int mid = std::min(left + window_size - 1, end); 
      int right = std::min(left + 2 * window_size - 1, end);
      // sorting procedure
      Merge(sequence, left, mid, right);
    }
  }
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
    int test_number;
    std::vector<int> result, expected;

    test_number += 1;
    result = {1 ,3, 10};
    expected = {1, 3, 10};
    MergeSortIterative(result, 0, result.size() - 1);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    result = {10, 3, 1};
    expected = {1, 3, 10};
    MergeSortIterative(result, 0, result.size() - 1);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    result = {10 ,3, 1, 5, 12, 37};
    expected = {1, 3, 5, 10, 12, 37};
    MergeSortIterative(result, 0, result.size() - 1);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    result = {3 , 5, 7, 1, 1};
    expected = {1 ,1, 3, 5, 7};
    MergeSortIterative(result, 0, result.size() - 1);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    result = {1 ,2, 3, 3, 3, 3,  5, 7, 7, 9};
    expected = result; 
    std::sort(expected.begin(), expected.end());
    MergeSortIterative(result, 0, result.size() - 1);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
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
      expected = result; 
      std::sort(expected.begin(), expected.end());
      MergeSortIterative(result, 0, result.size() - 1);
      t.stop();
      std::cout << "Elapsed time " << std::fixed << std::setprecision(9) << t << ", input size " << result.size() << std::endl;
      if (t.secs() > TIME_LIMIT_CPP) {
          break;
      }
      if (result != expected) {
          std::stringstream err_msg;
          err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
          throw std::logic_error(err_msg.str());
      }
  }
}