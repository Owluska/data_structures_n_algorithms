#include "timer.h"
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>

// https://www.youtube.com/watch?v=oBt53YbR9Kk&t=1565s&ab_channel=freeCodeCamp.org


std::ostream& operator<< (std::ostream &os, const std::vector<int> &data) {
  size_t idx = 0;
  for (const int &n : data) {
    os << n << (idx < data.size() - 1 ? ":" : "");
    idx++;
  }
  return os;
}

uint64_t fib(const int &n) {
  std::vector<uint64_t> table(n + 1, 0);
  table[1] = 1;
  for (int i = 0; i <= n; i++) {
    table[i + 1] += table[i];
    if ((i + 2) <= n) {
      table[i + 2] += table[i];
    }
  }
  return table[n];
}

uint64_t GridTraveler(const int &rows, const int &cols) {
  std::vector<std::vector<uint64_t>> table(rows + 1, std::vector<uint64_t>(cols + 1, 0));

  table[1][1] = 1;
  for (int i = 0; i <= rows; i++) {
    for (int j = 0; j <= cols; j++) {
      if((i + 1) <= rows) {
        table[i + 1][j] += table[i][j];
      }
      if((j + 1) <= cols) {
        table[i][j + 1] += table[i][j];
      }
    }
  }
  return table[rows][cols];
}

bool CanSun(const int &target, const std::vector<int> &sequence) {
  std::vector<bool> table(target + 1, false);
  // cause you always could generate zero number
  table[0] = true;
  for (int i = 0; i <= target; i++) {
    if (table[i] == true) {
      for (auto n : sequence) {
        if ((i + n) <= target) {
          table[i + n] = true;
        }
      }
    }
  }

  return table[target];
}

struct HowSumResult {
  bool canSum = false;
  std::vector<int> howSum;
   
  HowSumResult() {
    ;
  }

  HowSumResult(const bool &res, const std::vector<int> &seq) {
    this->canSum = res;
    this->howSum = seq;
  }
};


std::ostream& operator<< (std::ostream &os,  HowSumResult &data) {
  os << std::boolalpha << "can sum " << data.canSum << ", how sum " << data.howSum;
  return os;
}

HowSumResult HowSum(const int &target, const std::vector<int> &sequence) {
  std::vector<HowSumResult> table(target + 1, HowSumResult());
  table[0] = HowSumResult(true, {});

  for (int i = 0; i <= target; i++) {
    // std::cout << "i " << i << std::endl;
    // for (auto t : table) {
    //   std::cout << t << std::endl;
    // }

    if (table[i].canSum == true) {
      for (auto n : sequence) {
        if ((i + n) <= target) {
          table[i + n] = table[i];
          table[i + n].howSum.push_back(n);
          // std::cout << "i " << i << " n " << n << " t " << table[i + n] << std::endl;
        }
      }
    }
  }
  return table[target];
}

HowSumResult BestSum(const int &target, const std::vector<int> &sequence) {
  std::vector<HowSumResult> table(target + 1, HowSumResult());
  table[0] = HowSumResult(true, {});

  for (int i = 0; i <= target; i++) {
    // std::cout << "i " << i << std::endl;
    // for (auto t : table) {
    //   std::cout << t << std::endl;
    // }

    if (table[i].canSum == true) {
      for (auto n : sequence) {
        if ((i + n) <= target) {
          auto previous_sequence = table[i + n].howSum;
          auto new_sequence = table[i].howSum;
          new_sequence.push_back(n);
          if (!table[i + n].canSum || previous_sequence.size() > new_sequence.size()) {
            table[i + n] = table[i];
            table[i + n].howSum = new_sequence;
          }
          // std::cout << "i " << i << " n " << n << " t " << table[i + n] << std::endl;
        }
      }
    }
  }
  return table[target];
}

std::ostream& operator<< (std::ostream &os,  const std::vector<bool> &data) {
  os << std::boolalpha << "{";
  for (auto flag : data) {
    os << flag <<", ";

  }
  os << "}";
  return os;
}

bool CanConstruct(const std::string &target, const std::vector<std::string> &bank) {
  std::vector<bool> tab(target.length() + 1, false);
  tab[0] = true;

  for (int i = 0; i < tab.size(); i++) {
    // std::cout << i << " - " << tab << std::endl;
    if (tab[i] == true) {
      for (auto word : bank) {
        std::string target_suf = target.substr(i, word.length());
        // std::cout << target_suf << ":" << word << std::endl;
        if (target_suf == word && (i + word.length()) <= target.length()) {
          tab[i + word.length()] = true;
        }
      }
    }
  }
  return tab[target.length()];
}


std::ostream& operator<< (std::ostream &os, const std::vector<std::string> &data) {
  os << "[";
  for (int i = 0; i < data.size(); i++) {
    os << data[i] << (i < data.size() - 1 ? " " : "");
  }
  os << "]";
  return os;
}



int CountConstruct(const std::string &target, const std::vector<std::string> &bank) {
  std::vector<int> tab(target.length() + 1, 0);
  tab[0] = 1;

  for (int i = 0; i < tab.size(); i++) {
    for (auto word : bank) {
      std::string target_suf = target.substr(i, word.length());
      // std::cout << target_suf << ":" << word << std::endl;
      if (target_suf == word && (i + word.length()) <= target.length()) {
        tab[i + word.length()] += tab[i];
      }
    }
  }
  return tab[target.length()];
}



struct CombinationType{
  std::vector<std::string> combination;

  CombinationType() {
    this->combination = {};
  }

  CombinationType(const std::vector<std::string> &new_combination) {
    for (auto str : new_combination) {
      this->combination.push_back(str);
    }
  }
};

typedef std::vector<std::vector<std::string>> AllConstruct_t;

std::ostream& operator<< (std::ostream &os, const AllConstruct_t &data) {
  os << "[";
  for (int i = 0; i < data.size(); i++) {
    os << data[i];
  }
  os << "]";
  return os;
}

AllConstruct_t AllConstruct(const std::string &target, const std::vector<std::string> &bank) {
  std::vector<AllConstruct_t> tab(
    target.length() + 1);
  tab[0] = {{}};

  for (int i = 0; i < tab.size(); i++) {
    AllConstruct_t current_combinations = tab[i];
    // std::cout << "AT I: " << i << "[" << std::endl;
    // int p = 0;
    // for (auto item : tab) {
    //   std::cout << p << ":" << item ;
    //   p ++;
    // }
    // std::cout << "]" << std::endl;
    for (auto word : bank) {
      std::string target_suf = target.substr(i, word.length());
      // std::cout << i << ":" << target_suf << ":" << word << std::endl;
      if (target_suf == word && (i + word.length()) <= target.length()) {
        for (auto combination : current_combinations) {
          combination.push_back(word);
          tab[i + word.length()].push_back(combination);
          // std::cout << i + word.length() << ":" << tab[i + word.length()] << std::endl;
        }
      }
    }
  }
  return tab[target.length()];
}


int main () {
  //fib
  std::cout << "fib " << fib(6) <<  ", expected " << 8 << std::endl;
  std::cout << "fib " << fib(7) <<  ", expected " << 13 << std::endl;
  std::cout << "fib " << fib(8) <<  ", expected " << 21 << std::endl;
  // std::cout << "fib " << fib(50) <<  ", expected " << 12586269025 << std::endl;

  std::cout << "GridTraveler " << GridTraveler(1, 1) <<  ", expected " << 1 << std::endl;
  std::cout << "GridTraveler " << GridTraveler(2, 3) <<  ", expected " << 3 << std::endl;
  std::cout << "GridTraveler " << GridTraveler(3, 2) <<  ", expected " << 3 << std::endl;
  std::cout << "GridTraveler " << GridTraveler(3, 3) <<  ", expected " << 6 << std::endl;
  std::cout << "GridTraveler " << GridTraveler(18, 18) <<  ", expected " << 2333606220 << std::endl;

  std::cout << std::boolalpha << "CanSun " << CanSun(7, {2, 3}) <<  ", expected " << true << std::endl;
  std::cout << std::boolalpha << "CanSun " << CanSun(7, {5, 3, 4, 7}) <<  ", expected " << true << std::endl;
  std::cout << std::boolalpha << "CanSun " << CanSun(7, {2, 4}) <<  ", expected " << false << std::endl;
  std::cout << std::boolalpha << "CanSun " << CanSun(8, {2, 3, 5}) <<  ", expected " << true << std::endl;
  std::cout << std::boolalpha << "CanSun " << CanSun(300, {7, 14}) <<  ", expected " << false << std::endl;

  std::cout << "HowSum " << HowSum(7, {2, 3}).howSum <<  ", expected " << std::vector<int>({3, 2, 2}) << std::endl;
  std::cout << "HowSum " << HowSum(7, {5, 3, 4, 7}).howSum <<  ", expected " << std::vector<int>({4, 3}) << std::endl;
  std::cout << "HowSum " << HowSum(7, {2, 4}).howSum <<  ", expected " << std::vector<int>() << std::endl;
  std::cout << "HowSum " << HowSum(8, {2, 3, 5}).howSum <<  ", expected " << std::vector<int>({2, 2, 2, 2}) << std::endl;
  std::cout << "HowSum " << HowSum(300, {7, 14}).howSum <<  ", expected " << std::vector<int>() << std::endl;

  std::cout << "BestSum " << BestSum(7, {2, 3}).howSum <<  ", expected " << std::vector<int>({7}) << std::endl;
  std::cout << "BestSum " << BestSum(8, {2, 3, 5}).howSum <<  ", expected " << std::vector<int>({3, 5}) << std::endl;
  std::cout << "BestSum " << BestSum(8, {1, 4, 5}).howSum <<  ", expected " << std::vector<int>({4, 4}) << std::endl;
  std::cout << "BestSum " << BestSum(100, {1, 2, 5, 25}).howSum <<  ", expected " << std::vector<int>({25, 25, 25, 25}) << std::endl;

  std::cout << std::boolalpha << "CanConstruct " << CanConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}) <<  ", expected " << true << std::endl;
  std::cout << std::boolalpha << "CanConstruct " << CanConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "boar"}) <<  ", expected " << false << std::endl;
  std::cout << std::boolalpha << "CanConstruct " << CanConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) <<  ", expected " << true << std::endl;
  std::cout << std::boolalpha << "CanConstruct " << CanConstruct("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", 
  {"e", "ee", "eeee", "eeeee", "eeeeee"}) <<  ", expected " << false << std::endl;


  std::cout << "CountConstruct ";
  std::cout << CountConstruct( "purple", {"purp", "p", "ur", "le", "purpl"});
  std::cout << " expected " << 2 << std::endl;

  std::cout << "CountConstruct ";
  std::cout << CountConstruct("abcdef",  {"ab", "abc", "cd", "def", "abcd"});
  std::cout << " expected " << 1 << std::endl;

  std::cout << "CountConstruct ";
  std::cout << CountConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "boar"});
  std::cout << " expected " << 0 << std::endl;
  
  std::cout << "CountConstruct " << std::boolalpha;
  std::cout << CountConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"});
  std::cout << " expected " << 4 << std::endl;
  
  std::cout << "CountConstruct ";
  std::cout << CountConstruct(
      "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", 
      {"e", "ee", "eeee", "eeeee", "eeeeee"});
  std::cout << " expected " << 0 << std::endl;


  
  AllConstruct_t expected = {
      {"ab", "cd", "ef"}, 
      {"ab", "c", "def"}, 
      {"abc", "def"}, 
      {"abcd", "ef"}
  };
  std::cout << "AllConstruct ";
  std::cout << AllConstruct("abcdef",  {"ab", "abc", "cd", "def", "abcd", "ef", "c"});
  std::cout << " expected ";
  std::cout << expected << std::endl;

  std::cout << "AllConstruct ";
  std::cout << AllConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "boar"});
  std::cout << " expected " <<  AllConstruct_t({}) << std::endl;
  
  
  expected = {
      {"purp", "le"}, 
      {"p", "ur", "p", "le"}
  }; 
  std::cout << "AllConstruct " << std::boolalpha;
  std::cout << AllConstruct("purple", {"purp", "p", "ur", "le", "purpl"});
  std::cout << " expected ";
  std::cout << expected << std::endl;
  
  // std::cout << "AllConstruct ";
  // std::cout << AllConstruct(
  //     "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", 
  //     {"e", "ee", "eeee", "eeeee", "eeeeee"});
  // std::cout << " expected " << AllConstruct_t({}) << std::endl;

}