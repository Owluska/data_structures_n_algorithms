#include "timer.h"
#include <set>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>

// Problem Introduction
// You are going to travel to another city that is located 𝑑 miles away from your home city. Your can can travel
// at most 𝑚 miles on a full tank and you start with a full tank. Along your way, there are gas stations at
// distances stop 1 , stop 2 , . . . , stop 𝑛 from your home city. What is the minimum number of refills needed?
// Problem Description
// Input Format. The first line contains an integer 𝑑. The second line contains an integer 𝑚. The third line
// specifies an integer 𝑛. Finally, the last line contains integers stop 1 , stop 2 , . . . , stop 𝑛 .
// Input Format. Assuming that the distance between the cities is 𝑑 miles, a car can travel at most 𝑚 miles
// on a full tank, and there are gas stations at distances stop 1 , stop 2 , . . . , stop 𝑛 along the way, output the
// minimum number of refills needed. Assume that the car starts with a full tank. If it is not possible to
// reach the destination, output −1.
// Constraints. 1 ≤ 𝑑 ≤ 10 5 . 1 ≤ 𝑚 ≤ 400. 1 ≤ 𝑛 ≤ 300. 0 < stop 1 < stop 2 < · · · < stop 𝑛 < 𝑑.

// #define MAX_N 10e+3
// #define MIN_N 1
// #define TIME_LIMIT_CPP 1

// #define COIN_ONE 1
// #define COIN_FIVE 5
// #define COIN_TEN 10

#define MAX_D 100000
#define MIN_D 1

#define MAX_M 400
#define MIN_M 1

#define MAX_N 300
#define MIN_N 1


#define TIME_LIMIT_CPP 1


int MinimumNumberOfRefills(const int &d, const int &m, const std::set<int> &stops) {
    int min_stops = 0;
    int the_road_so_far = 0;
    int last_stop = 0;
    for (auto stop : stops) {

        if (stop - last_stop > m) {
            std::cout << "Next stop is too far: " << stop << std::endl;
            return -1;
        }
        if (the_road_so_far + stop >= m) {
            the_road_so_far = the_road_so_far + stop == m ? the_road_so_far + stop : the_road_so_far + last_stop;
            if (the_road_so_far > d) {
                break;
            }
            min_stops += 1;        
            if (the_road_so_far == d) {
                break;
            }
        }
        last_stop = stop;
    }
    if (d - last_stop > m) {
        std::cout << "Last stop is too far from destiantion: " << std::endl;
        return -1;
    }
    if (min_stops == 0 && last_stop != d && last_stop != 0) {
        min_stops += 1;
    }
    return min_stops;
}

std::ostream& operator<< (std::ostream &os, const std::set<int> &data) {
    size_t idx = 0;
    for (const int &n : data) {
        os << n << (idx < data.size() - 1 ? ":" : "");
        idx++;
    }
    return os;
}

int main () {
    int test_n = 1;
    int d = 950;
    int m = 400;
    std::set<int> stops = {
        200, 375, 550, 750
    };
    auto result = MinimumNumberOfRefills(d, m, stops);
    int expected = 2;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << +result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    d = 10;
    m = 3;
    stops = {
        1, 2, 5, 9
    };
    result = MinimumNumberOfRefills(d, m, stops);
    expected = -1;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << +result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    d = 10;
    m = 6;
    stops = {
        7
    };
    result = MinimumNumberOfRefills(d, m, stops);
    expected = -1;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << +result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    d = 10;
    m = 6;
    stops = {
        1, 3, 5
    };
    result = MinimumNumberOfRefills(d, m, stops);
    expected = 1;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << +result;
        throw std::logic_error(err_msg.str());
    }
    
    // it is garanteed that this case won t happen by the task conditions
    test_n += 1;
    d = 10;
    m = 6;
    stops = {
        11
    };
    result = MinimumNumberOfRefills(d, m, stops);
    expected = -1;
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_d(MIN_D, MAX_D);
    std::uniform_int_distribution<std::mt19937::result_type> dist_m(MIN_M, MAX_M);
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(MIN_N, MAX_N);
    std::uniform_int_distribution<std::mt19937::result_type> coin_toss(0, 1);
    int last_stop, n = 0;
    while(true) {
        t.start();
        d = dist_d(rng);
        m = dist_m(rng);
        stops.clear();
        n = dist_n(rng);
        for (int idx = 0; idx < n; idx ++) {
            auto stop = dist_m(rng);
            stops.insert(stop);
            last_stop = stop;
        }
        if (coin_toss(rng) && d > last_stop + m) {
            d = last_stop + m / 2;
        }
        if (d < last_stop + m) {
            d = last_stop + m;
        }
        auto result = MinimumNumberOfRefills(d, m, stops);
        t.stop();
        std::cout << "Elapsed time " << std::fixed << std::setprecision(9) << t 
        << ", input [" << d << ", " << m << ", " << stops << "], output " << result << std::endl;
        if (result > d / m + 1) {
            break;
        }
        // if (t.secs() > TIME_LIMIT_CPP) {
        //     break;
        // }
    }
}