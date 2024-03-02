#include "timer.h"
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>


#define MAX_N 1e3
#define MIN_N 1


#define TIME_LIMIT_CPP 1


// As we already know, a natural greedy strategy for the change problem does not work correctly for any set of
// denominations. For example, if the available denominations are 1, 3, and 4, the greedy algorithm will change
// 6 cents using three coins (4 + 1 + 1) while it can be changed using just two coins (3 + 3). Your goal now is
// to apply dynamic programming for solving the Money Change Problem for denominations 1, 3, and 4.
// Problem Description
// Input Format. Integer money.
// Output Format. The minimum number of coins with denominations 1, 3, 4 that changes money.
// Constraints. 1 ≤ money ≤ 10 3 .
// Sample 1.
// Input:
// 2
// Output:
// 2
// 2 = 1 + 1.
// Sample 2.
// Input:
// 34
// Output:
// 9
// 34 = 3 + 3 + 4 + 4 + 4 + 4 + 4 + 4 + 4.


using namespace std;

struct MoneyChangeResult {
    int result;
    vector<int> change;

    MoneyChangeResult() {
        result = 0;
        change = {};
    }

    MoneyChangeResult(const int &r, const vector<int> &c) {
        this->result = r;
        this->change = c;
    }

};

ostream &operator<<(ostream &os, const vector<int> &data) {
  size_t idx = 0;
  for (const int &n : data) {
    os << n << (idx < data.size() - 1 ? ":" : "");
    idx++;
  }
  return os;    
}

MoneyChangeResult MoneyChangeMemo(const int &n, const vector<int> &coins, map<int, MoneyChangeResult> &memo) {
    if (n <= 0) {
        return MoneyChangeResult(n, {});
    }
    if (memo.count(n)) {
        return memo[n];
    }

    MoneyChangeResult result;

    for (auto coin : coins) {
        int new_n = n - coin;
        auto rest = MoneyChangeMemo(new_n, coins, memo);
        if (rest.result == 0 ) {
            rest.change.push_back(coin);
            if (result.change.empty() || rest.change.size() < result.change.size()) {
                result.change = rest.change;
            }
        }
    }
    memo[n] = result;
    return memo[n];
}

MoneyChangeResult MoneyChangeTab(const int &n, const vector<int> &coins) {
    if (n <= 0) {
        return MoneyChangeResult(n, {});
    }
    vector<MoneyChangeResult> tab(n + 1, MoneyChangeResult(-1, {}));
    tab[0] = MoneyChangeResult(0, {});

    for (int i = 0; i <= n; i++) {
        if (tab[i].result >= 0 ) {
            for (auto coin : coins) {
                if ((i + coin) <= n) {
                    MoneyChangeResult prev_result = tab[i];
                    prev_result.change.push_back(coin);
                    if (tab[i + coin].change.empty() || prev_result.change.size() < tab[i + coin].change.size()) {
                        tab[i + coin].result = 0;
                        tab[i + coin].change = prev_result.change;
                    }
                }              
            }

        }
    }
    return tab[n];
}

int main() {
    int number;
    vector<int> sequence;
    map<int, MoneyChangeResult> cash;
    
    number = 0;
    sequence = {1, 3, 4};
    cash.clear();
    cout << "MoneyChangeMemo: " << MoneyChangeMemo(number, sequence, cash).change.size();
    cout << ", expected: " << 0 << std::endl;

    number = 6;
    sequence = {1, 3, 4};
    cash.clear();
    cout << "MoneyChangeMemo: " << MoneyChangeMemo(number, sequence, cash).change.size();
    cout << ", expected: " << vector<int>({3, 3}).size() << std::endl;


    number = 2;
    sequence = {1, 3, 4};
    cash.clear();
    cout << "MoneyChangeMemo: " << MoneyChangeMemo(number, sequence, cash).change.size();
    cout << ", expected: " << vector<int>({1, 1}).size() << std::endl;

    number = 34;
    sequence = {1, 3, 4};
    cash.clear();
    cout << "MoneyChangeMemo: " << MoneyChangeMemo(number, sequence, cash).change.size();
    cout << ", expected: " << vector<int>({3, 3, 4, 4, 4, 4, 4, 4, 4}).size() << std::endl;


    number = 999;
    sequence = {1};
    cash.clear();
    cout << "MoneyChangeMemo: " << MoneyChangeMemo(number, sequence, cash).change.size();
    cout << ", expected: " << 999 << std::endl;


    number = 0;
    sequence = {1, 3, 4};
    cout << "MoneyChangeMemo: " << MoneyChangeTab(number, sequence).change.size();
    cout << ", expected: " << 0 << std::endl;

    number = 6;
    sequence = {1, 3, 4};
    cout << "MoneyChangeMemo: " << MoneyChangeTab(number, sequence).change;
    cout << ", expected: " << vector<int>({3, 3}) << std::endl;


    number = 34;
    sequence = {1, 3, 4};
    cout << "MoneyChangeMemo: " << MoneyChangeTab(number, sequence).change.size();
    cout << ", expected: " << 9 << std::endl;


    number = 1000;
    sequence = {1};
    cout << "MoneyChangeMemo: " << MoneyChangeTab(number, sequence).change.size();
    cout << ", expected: " << 1000 << std::endl;
}