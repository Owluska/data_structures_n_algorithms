#include "timer.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>
#include <map>

// Task. The goal of this code problem is to implement an algorithm for the fractional knapsack problem.
// Input Format. The first line of the input contains the number 𝑛 of items and the capacity 𝑊 of a knapsack.
// The next 𝑛 lines define the values and weights of the items. The 𝑖-th line contains integers 𝑣 𝑖 and 𝑤 𝑖 —the
// value and the weight of 𝑖-th item, respectively.
// Constraints. 1 ≤ 𝑛 ≤ 10 3 , 0 ≤ 𝑊 ≤ 2 · 10 6 ; 0 ≤ 𝑣 𝑖 ≤ 2 · 10 6 , 0 < 𝑤 𝑖 ≤ 2 · 10 6 for all 1 ≤ 𝑖 ≤ 𝑛. All the
// numbers are integers.
// Output Format. Output the maximal value of fractions of items that fit into the knapsack. The absolute
// value of the difference between the answer of your program and the optimal value should be at most
// 10 −3 . To ensure this, output your answer with at least four digits after the decimal point (otherwise
// your answer, while being computed correctly, can turn out to be wrong because of rounding issues).
// Sample 1.
// Input:
// 3 50
// 60 20
// 100 50
// 120 30
// Output:
// 180.0000
// To achieve the value 180, we take the first item and the third item into the bag.
// Sample 2.
// Input:
// 1 10
// 500 30
// Output:
// 166.6667
// Here, we just take one third of the only available item.

#define MAX_N 10e+3
#define MIN_N 1

#define MAX_W 2 * 10e+6
#define MIN_W 0


#define TIME_LIMIT_CPP 1

typedef std::tuple<float, float>  Loot_t;

float round_to_three_pts(const float &n) {
    float result = n;
    return std::round(result * 1000)/ 1000;
}

float FindMaximumLootFowWeight(const std::vector<Loot_t> &new_loots, const int &capacity) {
    // O(N^2)
    float result = 0;
    if (new_loots.empty()) {
        return result;
    }
    auto loots = new_loots;
    int left_capacity = capacity;
    int items_amount = 0;
    int  best_loot_idx = 0;
    while (left_capacity > 0 && loots.size()) {
        float max_cost = -MAXFLOAT;
        float max_weight = 0;
        for (int idx = 0; idx < loots.size(); idx++) {
            // invariant
            auto weighted_cost = (std::get<0>(loots[idx]) * capacity) / std::get<1>(loots[idx]);
            if  (max_cost < weighted_cost) {
                max_cost = weighted_cost;
                max_weight = std::get<1>(loots[idx]);
                best_loot_idx = idx;
            }
        }
        left_capacity -= max_weight;
        result += left_capacity >= 0 ? max_cost * max_weight / capacity : max_cost;
        loots.erase(loots.begin() + best_loot_idx);        
    }
    return round_to_three_pts(result);
}




int main () {
    int n = 1;
    int capacity = 50;
    std::vector<Loot_t> loot = {
        {60, 20},
        {100, 50},
        {120, 30},
    };
    float expected = round_to_three_pts(180.000);
    auto result = FindMaximumLootFowWeight(loot, capacity);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }


    n += 1;
    capacity = 10;
    loot = {
        {500, 30},
    };
    expected = round_to_three_pts(166.667);
    result = FindMaximumLootFowWeight(loot, capacity);
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(MIN_N, MAX_N);
    std::uniform_int_distribution<std::mt19937::result_type> dist_w(MIN_W, MAX_W);
    while(true) {
        t.start();
        auto amount = static_cast<float>(dist_n(rng));
        auto capacity = static_cast<float>(dist_w(rng));
        std::vector<Loot_t> loot;
        for (float i = 0; i < amount; i++) {
            float cost = 1.0;
            float weight = 1.0;
            Loot_t loot_item(cost, weight);
            loot.push_back(loot_item);
        }
        float expected = amount >= capacity ? capacity : amount;
        expected = round_to_three_pts(expected);
        try {
            result = FindMaximumLootFowWeight(loot, capacity);
        } catch (...) {
            std::stringstream err_msg;
            err_msg << "FAILED TEST amount, capacity: " << amount << ", " << capacity << ", expected: "  << expected << ", got: " << result;
            throw std::logic_error(err_msg.str());            
        }
        t.stop();
        if (result != expected) {
            std::stringstream err_msg;
            err_msg << "FAILED TEST amount, capacity: " << amount << ", " << capacity << ", expected: "  << expected << ", got: " << result;
            throw std::logic_error(err_msg.str());
        }
        std::cout << "Elapsed time " << std::fixed << std::setprecision(9) << t << ", input [" << amount << ", " << capacity << "], output " << result << std::endl;
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
    }
}