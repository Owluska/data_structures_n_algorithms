#include "timer.h"
#include <set>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>

// You have 𝑛 ads to place on a popular Internet page. For each ad, you know how
// much is the advertiser willing to pay for one click on this ad. You have set up 𝑛
// slots on your page and estimated the expected number of clicks per day for each
// slot. Now, your goal is to distribute the ads among the slots to maximize the
// total revenue.
// Problem Description
// Task. Given two sequences 𝑎 1 , 𝑎 2 , . . . , 𝑎 𝑛 (𝑎 𝑖 is the profit per click of the 𝑖-th ad) and 𝑏 1 , 𝑏 2 , . . . , 𝑏 𝑛 (𝑏 𝑖 is
// the average number of clicks per day of the 𝑖-th slot), we need to partition them into 𝑛 pairs (𝑎 𝑖 , 𝑏 𝑗 )
// such that the sum of their products is maximized.
// Input Format. The first line contains an integer 𝑛, the second one contains a sequence of integers
// 𝑎 1 , 𝑎 2 , . . . , 𝑎 𝑛 , the third one contains a sequence of integers 𝑏 1 , 𝑏 2 , . . . , 𝑏 𝑛 .
// Constraints. 1 ≤ 𝑛 ≤ 10 3 ; −10 5 ≤ 𝑎 𝑖 , 𝑏 𝑖 ≤ 10 5 for all 1 ≤ 𝑖 ≤ 𝑛.
// Output Format. Output the maximum value of
// 𝑛
// ∑︀
// 𝑎_𝑖 𝑐_𝑖 , where 𝑐_1 , 𝑐_2 , . . . , 𝑐_𝑛 is a permutation of
// 𝑖=1
// 𝑏_1 , 𝑏_2 , . . . , 𝑏_𝑛 .

#define MAX_N 1000
#define MIN_N 1

#define MAX_AB 100000
#define MIN_AB -100000


#define TIME_LIMIT_CPP 1


int MaximumRevenue(std::vector<int> &revenues, std::vector<int> &slots_clicks) {
    int result = 0;
    // for N x N (1000 x 1000 in worst case)
    // for rev in revenues:
    //  for slot in slots:
    //      if slot == max_slot and rev == _max_rev:
    //          res.append(slot * rev)
    //          del revenues[rev]
    //          del slots[slot]


    // if slots and revenues sorted
    //  2 * N * log(N) - [2 * 10 * 10]
    // o(N) ~ 1000
    std::sort(revenues.begin(), revenues.end(), std::greater<int>());
    std::sort(slots_clicks.begin(), slots_clicks.end(), std::greater<int>());
    for (int i = 0; i < revenues.size(); i++) {
        // std::cout << slots_clicks[i] << ":" << revenues[i] << std::endl;
        result += slots_clicks[i] * revenues[i];
    }
    return result;
}


std::ostream& operator<< (std::ostream& os, const std::vector<int>& vector) {
    size_t idx = 0;
    for (const int &n : vector) {
        os << n << (idx < vector.size() - 1 ? ":" : "");
        idx++;
    }
    return os;
}
int main () {
    int test_n, result, expected;
    std::vector<int> slots, revs;

    test_n = 1;
    revs = {
        0, 3, 2, 1
    };
    slots = {
        0, 3, 2, 1
    };    
    result = MaximumRevenue(revs, slots);
    expected = 14;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << +result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    revs = {
        -3, -2, -1
    };
    slots = {
        -3, -2, -1
    };    
    result = MaximumRevenue(revs, slots);
    expected = 14;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << +result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    revs = {
        -3, -2, -1
    };
    slots = {
        3, 2, 1
    };    
    result = MaximumRevenue(revs, slots);
    expected = -10;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << +result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    revs = {
        -3, 2, -1
    };
    slots = {
        3, 2, 1
    };    
    result = MaximumRevenue(revs, slots);
    expected = 1;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << +result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    revs = {
        23
    };
    slots = {
        39
    };    
    result = MaximumRevenue(revs, slots);
    expected = 897;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << +result;
        throw std::logic_error(err_msg.str());
    }

    
    test_n += 1;
    revs = {
        1, 3, -5
    };
    slots = {
        -2, 4, 1
    };    
    result = MaximumRevenue(revs, slots);
    expected = 23;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << +result;
        throw std::logic_error(err_msg.str());
    }    


    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(MIN_N, MAX_N);
    std::uniform_int_distribution<std::mt19937::result_type> dist_ab(MIN_AB, MAX_AB);
    int last_stop, n = 0;
    while(true) {
        t.start();
        int n = dist_n(rng);
        revs.clear();
        slots.clear();
        for (int idx = 0; idx < n; idx++) {
            revs.push_back(dist_ab(rng));
            slots.push_back(dist_ab(rng));
        }
        result = MaximumRevenue(revs, slots);
        t.stop();
        std::cout << "Elapsed time " << std::fixed << std::setprecision(9) << t 
        << ", input [" << n << "], output " << result << std::endl;
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
    }
}