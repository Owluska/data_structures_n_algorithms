#include "timer.h"
#include <map>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>

// https://www.youtube.com/watch?v=oBt53YbR9Kk&t=1565s&ab_channel=freeCodeCamp.org
#define TIME_LIMIT_CPP 1

std::ostream& operator<< (std::ostream &os, const std::vector<int> &data) {
  size_t idx = 0;
  for (const int &n : data) {
    os << n << (idx < data.size() - 1 ? ":" : "");
    idx++;
  }
  return os;
}


long int fib(const int &n, std::map<int, long int> &memo) {
    if (memo.count(n)) { return memo[n]; }
    if (n <= 2) {return 1; }
    memo[n] = fib(n - 2, memo) + fib(n -1, memo);
    return memo[n];
}

uint64_t grid_traveler(
    const uint64_t &cols, const uint64_t &rows, 
    std::map<std::vector<uint64_t>, uint64_t> &memo) {
    std::vector<uint64_t> key = {cols, rows};
    if (memo.count(key)) { return memo[key]; }
    if (cols == 0 || rows == 0) {
        return 0;
    }
    if (cols == 1 && rows == 1) {
        return 1;
    }
    // right + down
    memo[key] = grid_traveler(cols - 1, rows, memo) + grid_traveler(cols, rows - 1, memo);
    return memo[key];
}

bool canSum(
        const int &target, const std::vector<int> &sequence, std::map<int, bool> &memo) {
    if (memo.count(target)) { return memo[target]; }
    if (target == 0) { return true; }
    if (target < 0) { return false; }
    for (auto n : sequence) {
        int reminder = target - n;
        if (canSum(reminder, sequence, memo)) {
            memo[target] = true;
            return true;
        }
    }
    memo[target] = false;
    return false;
}


bool howSum(
        const int &target, 
        const std::vector<int> &sequence,
        std::vector<int> &combinations,
        std::map<int, bool> &memo) {
    if (memo.count(target)) { return memo[target]; }
    if (target == 0) { return true; }
    if (target < 0) { return false; }
    for (auto n : sequence) {
        int reminder = target - n;
        if (howSum(reminder, sequence, combinations, memo)) {
            combinations.push_back(n);
            memo[target] = true;
            return true;
        }
    }
    memo[target] = false;
    return false;
}

struct BestSumResult {
    bool result = false;
    std::vector<int> combinations;
    BestSumResult() {
        this->result = false;
        this->combinations.clear();
    }

    BestSumResult(const bool &new_result, const std::vector<int> &new_combinations) {
        this->result = new_result;
        this->combinations = new_combinations;
    }
};

BestSumResult bestSum(
        const int &target, 
        const std::vector<int> &sequence,
        std::map<int, BestSumResult> &memo) {
    if (memo.count(target)) { return memo[target]; }
    if (target == 0) { return BestSumResult(true, {}); }
    if (target < 0) { return BestSumResult(false, {}); }
    auto result = BestSumResult();
    std::vector<int> shortest_combination;
    for (auto n : sequence) {
        int reminder = target - n;
        auto reminder_result = bestSum(reminder, sequence, memo);
        if (reminder_result.result) {
            std::vector<int> current_combination = reminder_result.combinations;
            current_combination.push_back(n);
            result.result = true;
            if (shortest_combination.size() == 0 ||  current_combination.size() < shortest_combination.size()) {
                shortest_combination = current_combination;
            }
        }
    }
    result.combinations = shortest_combination;
    memo[target] = result;
    return result;
}



bool isPrefix(const std::string &string, const std::string &prefix) {
    if (prefix.empty()) { return true; }
    std::string substring(string.begin(), string.begin() + prefix.length());
    return substring == prefix;
}

std::string removePrefix(const std::string &string, const std::string &prefix) {
    return std::string(string.begin() + prefix.length(), string.end());
}

bool CanConstruct(
      const std::string &target, 
      const std::vector<std::string> &bank, 
      std::map<std::string, bool> &memo) {
    if (memo.count(target)) {return memo[target]; }
    if (target.empty()) {return true; }
    for (auto word : bank) {
        if (!isPrefix(target, word)) { continue; }
        std::string new_target = removePrefix(target, word);
        if (CanConstruct(new_target, bank, memo) ) {
            memo[target] = true;
            return memo[target];
        }
    }
    memo[target] = false;
    return memo[target];
}

int CountConstruct(
      const std::string &target, 
      const std::vector<std::string> &bank, 
      std::map<std::string, int> &memo) {
    if (memo.count(target)) {return memo[target]; }
    if (target.empty()) {return 1; }
    int total_count = 0;
    for (auto word : bank) {
        if (!isPrefix(target, word)) { continue; }
        // O(1)
        std::string new_target = removePrefix(target, word);
        int count_for_rest = CountConstruct(new_target, bank, memo);
        total_count += count_for_rest;
    }
    memo[target] = total_count;
    return memo[target];
}

typedef std::vector<std::vector<std::string>> AllConstruct_t;

AllConstruct_t AllConstruct(
      const std::string &target, 
      const std::vector<std::string> &bank, 
      std::map<std::string, AllConstruct_t> &memo) {
    if (memo.count(target)) {return memo[target]; }
    if (target.empty()) {return {{}}; }
    AllConstruct_t all_consturctions;
    for (int i = 0; i < bank.size(); i++) {
        auto word = bank[i];
        if (!isPrefix(target, word)) { continue; }
        // O(1)
        std::string new_target = removePrefix(target, word);
        auto rest_constructions = AllConstruct(new_target, bank, memo);
        for (auto &ways : rest_constructions) {
          ways.insert(ways.begin(), word);
          all_consturctions.push_back(ways);
        }
    }
    memo[target] = all_consturctions;
    return memo[target];
}

std::ostream& operator<< (std::ostream &os, const AllConstruct_t &data) {
  os << "[";
  for (int i = 0; i < data.size(); i++) {
    os << "[";
    for (int j = 0; j < data[i].size(); j++) {
      os << data[i][j] << (j < data[i].size() - 1 ? " " : "");
    }
    os << "]" << (i < data.size() - 1 ? "," : "");
  }
  os << "]";
  return os;
}

int main () {
  // DYNAMIC FIB
  std::map<int, long int> cash;
  std::cout << "fib: " << fib(7, cash) << std::endl;

  cash.clear();
  std::cout << "fib: " << fib(8, cash) << std::endl;

  cash.clear();
  std::cout << "fib: " << fib(50, cash) << std::endl;
  // DYNAMIC MAP TRAVELER
  // 1
  std::map<std::vector<uint64_t>, uint64_t> cash2;
  std::cout << "grid_traveler " << grid_traveler(1, 1, cash2) << ", expected: " << 1 <<  std::endl;

  // 2
  cash2.clear();
  std::cout << "grid_traveler " << grid_traveler(2, 2, cash2) << ", expected: " << 2 <<  std::endl;

  // 3
  cash2.clear();
  std::cout << "grid_traveler " << grid_traveler(3, 2, cash2) << ", expected: " << 3 <<  std::endl;

  // 6
  cash2.clear();
  std::cout << "grid_traveler " << grid_traveler(3, 3, cash2) << ", expected: " << 6 <<  std::endl;

  // 2333606220
  cash2.clear();
  std::cout << "grid_traveler " << grid_traveler(18, 18, cash2) << ", expected: " << 2333606220 <<  std::endl;

  
  // CAN SUM
  // 1
  std::map<int, bool> cash3;
  std::cout << "canSum: " << std::boolalpha << canSum(7, {2, 3}, cash3) << ", expected: " << true << std::endl;


  // CAN SUM
  // 1
  cash3.clear();
  std::cout << "canSum: " << std::boolalpha << canSum(7, {5, 3, 4, 7}, cash3) << ", expected: " << true << std::endl;


  // CAN SUM
  // 0
  cash3.clear();
  std::cout << "canSum: " << std::boolalpha << canSum(7, {2, 4}, cash3) << ", expected: " << false << std::endl;


  // CAN SUM
  // 1
  cash3.clear();
  std::cout << "canSum: " << std::boolalpha << canSum(8, {2, 3, 5}, cash3) << ", expected: " << true << std::endl;


  // CAN SUM
  // 0
  cash3.clear();
  std::cout << "canSum: " << std::boolalpha << canSum(300, {7, 14}, cash3) << ", expected: " << false << std::endl;



  // HOW SUM
  // 3 2 2 
  std::vector<int> result;
  bool can_sum;
  cash3.clear();
  can_sum =  howSum(7, {2, 3}, result, cash3);
  std::cout << "howSum: " << can_sum << " result " << result << std::endl;


  // HOW SUM
  // 3 4
  cash3.clear();
  result.clear();
  can_sum = howSum(7, {5, 3, 4, 7}, result, cash3);
  std::cout << "howSum: " << can_sum << " result " << result << std::endl;

  // HOW SUM
  //[]
  cash3.clear();
  result.clear();
  can_sum = howSum(7, {2, 4}, result, cash3);
  std::cout << "howSum: " << can_sum << " result " << result << std::endl;

  // HOW SUM
  // 2 2 2 2
  cash3.clear();
  result.clear();
  can_sum = howSum(8, {2, 3, 5}, result, cash3);
  std::cout << "howSum: " << can_sum << " result " << result << std::endl;

  // HOW SUM
  // []
  cash3.clear();
  result.clear();
  can_sum = howSum(300, {7, 14}, result, cash3);
  std::cout << howSum << " result " << result << std::endl;

  // BEST SUM
  // 7 
  BestSumResult best_sum;
  std::map<int, BestSumResult> cash4;
  best_sum = bestSum(7, {5, 3, 4, 7}, cash4);
  std::cout << "BEST SUM " << best_sum.combinations  << std::endl;

  // BEST SUM
  // 3 5
  best_sum = BestSumResult();
  cash4.clear();
  best_sum = bestSum(8, {2, 3, 5}, cash4);
  std::cout << "BEST SUM " << best_sum.combinations  << std::endl;


  // BEST SUM
  // 4 4
  best_sum = BestSumResult();
  cash4.clear();
  best_sum = bestSum(8, {1, 4, 5}, cash4);
  std::cout << "BEST SUM " << best_sum.combinations  << std::endl;

  // BEST SUM
  // 25 25 25 
  best_sum = BestSumResult();
  cash4.clear();
  best_sum = bestSum(100, {1, 2, 5, 25}, cash4);
  std::cout << "BEST SUM " << best_sum.combinations  << std::endl;



  // isPrefix
  std::cout << "isPrefix " << isPrefix("abcdeee", "abc") << std::endl;
  std::cout << "isPrefix " << isPrefix("abcdeee", "ee") << std::endl;
  std::cout << "isPrefix " << isPrefix("", "ee") << std::endl;
  std::cout << "isPrefix " << isPrefix("", "") << std::endl;
  std::cout << "isPrefix " << isPrefix("abc", "abcd") << std::endl;
  std::cout << "isPrefix " << isPrefix("abc", "k") << std::endl;
  std::cout << "isPrefix " << isPrefix("abc", "") << std::endl;



  //removePrefix
  std::cout << "removePrefix " << removePrefix("abcdeee", "abc") << std::endl;

  //CanConstruct
  std::map<std::string, bool> cash5;
  std::cout << "CanConstruct " << std::boolalpha;
  std::cout << CanConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}, cash5);
  std::cout << " expected " << true << std::endl;

  cash5.clear();
  std::cout << "CanConstruct " << std::boolalpha;
  std::cout << CanConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "boar"}, cash5);
  std::cout << " expected " << false << std::endl;
  
  cash5.clear();
  std::cout << "CanConstruct " << std::boolalpha;
  std::cout << CanConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, cash5);
  std::cout << " expected " << true << std::endl;
  
  cash5.clear();
  std::cout << "CanConstruct " << std::boolalpha;
  std::cout << CanConstruct(
      "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", 
      {"e", "ee", "eeee", "eeeee", "eeeeee"}, cash5);
  std::cout << " expected " << false << std::endl;


  //CountConstruct
  std::map<std::string, int> cash6;
  std::cout << "CountConstruct ";
  std::cout << CountConstruct(
      "purple", 
      {"purp", "p", "ur", "le", "purpl"}, cash6);
  std::cout << " expected " << 2 << std::endl;

  cash6.clear();
  std::cout << "CountConstruct ";
  std::cout << CountConstruct(
      "abcdef", 
      {"ab", "abc", "cd", "def", "abcd"}, cash6);
  std::cout << " expected " << 1 << std::endl;

  cash6.clear();
  std::cout << "CountConstruct " << std::boolalpha;
  std::cout << CountConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "boar"}, cash6);
  std::cout << " expected " << 0 << std::endl;
  
  cash6.clear();
  std::cout << "CountConstruct " << std::boolalpha;
  std::cout << CountConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, cash6);
  std::cout << " expected " << 4 << std::endl;
  
  cash6.clear();
  std::cout << "CountConstruct " << std::boolalpha;
  std::cout << CountConstruct(
      "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", 
      {"e", "ee", "eeee", "eeeee", "eeeeee"}, cash6);
  std::cout << " expected " << 0 << std::endl;

  //AllConstruct
  std::map<std::string, AllConstruct_t> cash7;
  std::cout << "AllConstruct:\n";
  std::cout << AllConstruct(
      "purple", 
      {"purp", "p", "ur", "le", "purpl"}, cash7);
  AllConstruct_t expected = {{"purp", "le"}, {"p", "ur", "p", "le"}};
  std::cout << "\nexpected:\n" << expected << std::endl;

  cash7.clear();
  std::cout << "AllConstruct:\n";
  std::cout << AllConstruct(
      "abcdef", 
      {"ab", "abc", "cd", "def", "abcd", "ef", "c"}, cash7);
  expected = {{"ab", "cd", "ef"}, {"ab", "c", "def"}, {"abc", "def"}, {"abcd", "ef"}};
  std::cout << "\nexpected:\n" << expected << std::endl;

  cash7.clear();
  std::cout << "AllConstruct:\n";
  std::cout << AllConstruct(
      "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", 
      {"e", "ee", "eeee", "eeeee", "eeeeee"}, cash7);
  expected = {{}};
  std::cout << "\nexpected:\n" << expected << std::endl;
}