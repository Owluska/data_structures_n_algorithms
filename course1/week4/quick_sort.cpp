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


// https://www.enjoyalgorithms.com/blog/quick-sort-algorithm


std::ostream& operator<< (std::ostream &os, const std::vector<int> &data) {
  size_t idx = 0;
  for (const int &n : data) {
    os << n << (idx < data.size() - 1 ? ":" : "");
    idx++;
  }
  return os;
}

void SwapElements(std::vector<int> &sequence, const int &idx1, const int &idx2) {
    int tmp = sequence[idx1];
    sequence[idx1] = sequence[idx2];
    sequence[idx2] = tmp;
}

int GenerateRandomA() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(
    MIN_A, MAX_A);
  return dist(rng);
}

int GenerateRandom(const int &min, const int &max) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(
    MIN_A, MAX_A);
  return dist(rng);
}

int GenerateRandomUniqueA(){
  int a = GenerateRandomA();
  const unsigned int p = 11; //any prime number satisfying p ≡ 3 (mod 4)
  unsigned int r = ((unsigned long long) a * a) % p;
  if (a <= p / 2){
    return r;
  } else {
    return p - r;
  }
}

int PartitionAlgo(
    std::vector<int> &sequence, const int &leftPos, const int &rightPos) {
  int pivotIdx = rightPos;
  // first value always should be zero, in 46 or in 51 and 52
  int i = leftPos - 1;

  // check all except of pivotIdx
  for (int j = leftPos; j < rightPos; j++ ) {
    if (sequence[j] < sequence[pivotIdx]) {
      i++;
      //  arr[i + 1] = arr[j], arr[j] = arr[i + 1], 
      // so we always push bigger values to the end
      SwapElements(sequence, i, j);
    }
  }
  // pivot position now is i + 1
  SwapElements(sequence, i + 1, pivotIdx);
  return i + 1;
}


void QuickSort(
      std::vector<int> &sequence, const int &leftPos, const int &rightPos) {
  if (!sequence.empty() && leftPos != rightPos) {
    auto pivotIdx = PartitionAlgo(sequence, leftPos, rightPos);
    QuickSort(
      sequence, leftPos, pivotIdx != leftPos ? pivotIdx - 1 : pivotIdx);
    QuickSort(
      sequence, pivotIdx != rightPos ? pivotIdx + 1 : pivotIdx, rightPos);
  }
  return;
}

int main() {
    int test_number;
    std::vector<int> result, expected;

    test_number += 1;
    result = {1 ,3, 10};
    expected = {1, 3, 10};
    QuickSort(result, 0, result.size() - 1);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_number << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    } else {
        std::cout << "PASSED TEST #: " << test_number << ", expected: "  << expected << ", got: " 
        << result << std::endl;
    }

    test_number += 1;
    result = {10 ,3, 1};
    expected = {1, 3, 10};
    QuickSort(result, 0, result.size() - 1);
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
    QuickSort(result, 0, result.size() - 1);
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
    QuickSort(result, 0, result.size() - 1);
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
    QuickSort(result, 0, result.size() - 1);
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
      QuickSort(result, 0, result.size() - 1);
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