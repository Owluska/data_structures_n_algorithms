#include "timer.h"
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>


#define MAX_N 1e6
#define MIN_N 1


#define TIME_LIMIT_CPP 1


// Primitive Calculator
// Problem Introduction
// You are given a primitive calculator that can perform the following three operations with
// the current number 𝑥: multiply 𝑥 by 2, multiply 𝑥 by 3, or add 1 to 𝑥. Your goal is given a
// positive integer 𝑛, find the minimum number of operations needed to obtain the number 𝑛
// starting from the number 1.
// Problem Description
// Task. Given an integer 𝑛, compute the minimum number of operations needed to obtain the number 𝑛
// starting from the number 1.
// Input Format. The input consists of a single integer 1 ≤ 𝑛 ≤ 10 6 .
// Output Format. In the first line, output the minimum number 𝑘 of operations needed to get 𝑛 from 1.
// In the second line output a sequence of intermediate numbers. That is, the second line should contain
// positive integers 𝑎 0 , 𝑎 2 , . . . , 𝑎 𝑘−1 such that 𝑎 0 = 1, 𝑎 𝑘−1 = 𝑛 and for all 0 ≤ 𝑖 < 𝑘 − 1, 𝑎 𝑖+1 is equal to
// either 𝑎 𝑖 + 1, 2𝑎 𝑖 , or 3𝑎 𝑖 . If there are many such sequences, output any one of them.
// Sample 1.
// Input:
// 1
// Output:
// 0
// 1
// Sample 2.
// Input:
// 5
// Output:
// 3
// 1245
// Here, we first multiply 1 by 2 two times and then add 1. Another possibility is to first multiply by 3
// and then add 1 two times. Hence “1 3 4 5” is also a valid output in this case.
// Sample 3.
// Input:
// 96234
// Output:
// 14
// 1 3 9 10 11 22 66 198 594 1782 5346 16038 16039 32078 96234
// Again, another valid output in this case is “1 3 9 10 11 33 99 297 891 2673 8019 16038 16039 48117
// 96234”.
// 3Starter Files
// Going from 1 to 𝑛 is the same as going from 𝑛 to 1, each time either dividing the current number by 2 or 3
// or subtracting 1 from it. Since we would like to go from 𝑛 to 1 as fast as possible it is natural to repeatedly
// reduce 𝑛 as much as possible. That is, at each step we replace 𝑛 by min{𝑛/3, 𝑛/2, 𝑛 − 1} (the terms 𝑛/3
// and 𝑛/2 are used only when 𝑛 is divisible by 3 and 2, respectively). We do this until we reach 1. This gives
// rise to the following algorithm and it is implemented in the starter files:
// GreedyCalculator(𝑛):
// 𝑛𝑢𝑚𝑂𝑝𝑒𝑟𝑎𝑡𝑖𝑜𝑛𝑠 ← 0
// while 𝑛 > 1:
// 𝑛𝑢𝑚𝑂𝑝𝑒𝑟𝑎𝑡𝑖𝑜𝑛𝑠 ← 𝑛𝑢𝑚𝑂𝑝𝑒𝑟𝑎𝑡𝑖𝑜𝑛𝑠 + 1
// if 𝑛 mod 3 = 0:
// 𝑛 ← 𝑛/3
// else if 𝑛 mod 2 = 0:
// 𝑛 ← 𝑛/2
// else:
// 𝑛 ← 𝑛 − 1
// return 𝑛𝑢𝑚𝑂𝑝𝑒𝑟𝑎𝑡𝑖𝑜𝑛𝑠
// This seemingly correct algorithm is in fact incorrect. You may want to submit one of the starter files to
// ensure this. Hence in this case moving from 𝑛 to min{𝑛/3, 𝑛/2, 𝑛 − 1} is not safe.


using namespace std;
const int OPERATIONS_AMOUNT = 3;
enum Operations_t {
  plus_1 = 0,
  mult_2 = 1,
  mult_3 = 2,
};

struct CalculatorResult_t {
  int rest = 1;
  vector<vector<int>> operations_sequences;
  
  CalculatorResult_t() {
    this->rest = 1;
    this->operations_sequences = {};
  }

  CalculatorResult_t(const int &rest_new, const vector<vector<int>> &seq_new) {
    this->rest = rest_new;
    this->operations_sequences = seq_new;
  }  
};

ostream& operator<<(ostream &os, const vector<int> &operations) {
  for (int i = 0; i < operations.size(); i++) {
    int op = operations[i];
    // string str_operation = "[";
    string str_operation = "";
    switch (op)
    {
      case Operations_t::plus_1:
        str_operation += "+ 1";
        break;
      
      case Operations_t::mult_2:
        str_operation += "x 2";
        break;

      case Operations_t::mult_3:
        str_operation += "x 3";
        break;
      
      default:
        break;
    }
    // str_operation += "]";
    os << str_operation << (i < operations.size() - 1 ? ", " : "");
  }
  return os;
}


ostream& operator<<(ostream &os, const vector<vector<int>> &operations) {
  for (int i = 0; i < operations.size(); i++) {
    os << "{" << operations[i] << "}" << (i < operations.size() - 1 ? ", " : "");
  }
  return os;
}


CalculatorResult_t MemoCalculator(const int &target, map<int, CalculatorResult_t> &cash) {
  if (target == 1) {
    return CalculatorResult_t(target, {{}});
  }
  if (cash.count(target)) {
    return cash[target];
  }

  CalculatorResult_t result;
  for (int i = 0; i < OPERATIONS_AMOUNT; i++) {
    int operation_result = 0;
    // vector<Operations_t> current_operations;
    switch (i)
    {
      case Operations_t::plus_1:
        operation_result = target - 1;
        break;
      
      case Operations_t::mult_2:
        if (target % 2 != 0) { continue; }
        operation_result = target / 2;
        break;

      case Operations_t::mult_3:
        if (target % 3 != 0) { continue; }
        operation_result = target / 3;
        break;
      
      default:
        break;
    }
    auto current_result = MemoCalculator(operation_result, cash);
    if (result.rest == 1) {
      for (auto &operations  : current_result.operations_sequences) {
        operations.push_back(i);
        result.operations_sequences.push_back(operations);
      }
    }
  }
  cash[target] = result;
  return cash[target];
}

CalculatorResult_t TabCalculator(const int &target) {
  if (target <= 1) {
    return CalculatorResult_t(target, {{}});
  }
  vector<CalculatorResult_t> tab(target + 1, CalculatorResult_t());
  tab[0] = CalculatorResult_t(0, {});
  tab[1] = CalculatorResult_t(1, {{}});

  for (int i = 0; i < tab.size(); i++ ) {
    for (int j = 0; j < OPERATIONS_AMOUNT; j++) {
      int operation_result = 0;
      auto current_sequences = tab[i].operations_sequences;
      switch (j)
      {
        case Operations_t::plus_1:
          operation_result = i + 1;
          break;
        
        case Operations_t::mult_2:
          operation_result = i * 2;
          break;

        case Operations_t::mult_3:
          operation_result = i * 3;
          break;
        
        default:
          break;
      }
      if (operation_result < tab.size()) {
        for (auto &operations_sequence : current_sequences) {
          operations_sequence.push_back(j);
          tab[operation_result].operations_sequences.push_back(operations_sequence);
        }
      } 
    }
  }
  return tab.back();
}


vector<int> TabCalculator2(const int &target) {
  if (target == 1) {
    return {1};
  }
  vector<vector<int>> tab(target + 1, vector<int>(0));
  // tab[1] = {1};

  for (int i = 0; i < tab.size(); i++ ) {
    for (int j = 0; j < OPERATIONS_AMOUNT; j++) {
      int operation_result = 0;
      auto current_sequences = tab[i];
      switch (j)
      {
        case Operations_t::plus_1:
          operation_result = i + 1;
          break;
        
        case Operations_t::mult_2:
          operation_result = i * 2;
          break;

        case Operations_t::mult_3:
          operation_result = i * 3;
          break;
        
        default:
          break;
      }
      if (operation_result < tab.size() & operation_result != 0) {
        current_sequences.push_back(operation_result);
        if (tab[operation_result].size() > current_sequences.size() || tab[operation_result].empty()) {
          tab[operation_result] = current_sequences;
        }
      } 
    }
  }
  return tab.back();
}

int GetBestSequence(const int &target, const int &mode) {
  map<int, CalculatorResult_t> cash;
  auto result = mode == 0 ? MemoCalculator(target, cash) : TabCalculator(target);
  cout << "All sequences: " <<  result.operations_sequences << ", min amount: ";
  int min_amount = target;
  for (auto operations : result.operations_sequences) {
    if (operations.size() < min_amount) {
      min_amount = operations.size();
    }
  }
  return min_amount;
}


int main() {
  int recursive_solution = 0;
  int iterative_solution = 1;
  cout << GetBestSequence(3, recursive_solution) << endl;
  cout << GetBestSequence(1, recursive_solution) << endl;
  cout << GetBestSequence(5, recursive_solution) << endl;
  // cout << GetBestSequence(96234) << endl; - crashes (stack? 96234 * 3 calls in worse)

  cout << GetBestSequence(3, iterative_solution) << endl;
  cout << GetBestSequence(1, iterative_solution) << endl;
  cout << GetBestSequence(5, iterative_solution) << endl;
  cout << "TabCalculator2 " << TabCalculator2(3).size() - 1 << endl;
  cout << "TabCalculator2 " << TabCalculator2(5).size() - 1 << endl;
  cout << "TabCalculator2 " << TabCalculator2(1).size() - 1 << endl;
  cout << "TabCalculator2 " << TabCalculator2(10).size() - 1 << endl;


  auto calc_result = TabCalculator2(96234);
  cout << "TabCalculator2:\n" << "{";
  for (auto n : calc_result) {
    cout << n << " ";
  }
  cout << "}, total: " << calc_result.size() - 1 << endl;
}