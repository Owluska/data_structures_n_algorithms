#include "timer.h"
#include <set>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>

// Problem Introduction
// You are responsible for collecting signatures from all tenants of a certain build-
// ing. For each tenant, you know a period of time when he or she is at home.
// You would like to collect all signatures by visiting the building as few times as
// possible.
// The mathematical model for this problem is the following. You are given a set
// of segments on a line and your goal is to mark as few points on a line as possible
// so that each segment contains at least one marked point.
// Problem Description
// Task. Given a set of 𝑛 segments {[𝑎 0 , 𝑏 0 ], [𝑎 1 , 𝑏 1 ], . . . , [𝑎 𝑛−1 , 𝑏 𝑛−1 ]} with integer coordinates on a line, find
// the minimum number 𝑚 of points such that each segment contains at least one point. That is, find a
// set of integers 𝑋 of the minimum size such that for any segment [𝑎 𝑖 , 𝑏 𝑖 ] there is a point 𝑥 ∈ 𝑋 such
// that 𝑎 𝑖 ≤ 𝑥 ≤ 𝑏 𝑖 .
// Input Format. The first line of the input contains the number 𝑛 of segments. Each of the following 𝑛 lines
// contains two integers 𝑎 𝑖 and 𝑏 𝑖 (separated by a space) defining the coordinates of endpoints of the 𝑖-th
// segment.
// Constraints. 1 ≤ 𝑛 ≤ 100; 0 ≤ 𝑎 𝑖 ≤ 𝑏 𝑖 ≤ 10 9 for all 0 ≤ 𝑖 < 𝑛.
// Output Format. Output the minimum number 𝑚 of points on the first line and the integer coordinates
// of 𝑚 points (separated by spaces) on the second line. You can output the points in any order. If there
// are many such sets of points, you can output any set. (It is not difficult to see that there always exist
// a set of points of the minimum size such that all the coordinates of the points are integers.)
// Sample 1.
// Input:
// 3
// 13
// 25
// 36
// Output:
// 1
// 3
// In this sample, we have three segments: [1, 3], [2, 5], [3, 6] (of length 2, 3, 3 respectively). All of them
// contain the point with coordinate 3: 1 ≤ 3 ≤ 3, 2 ≤ 3 ≤ 5, 3 ≤ 3 ≤ 6.
// 8Sample 2.
// Input:
// 4
// 47
// 13
// 25
// 56
// Output:
// 2
// 36
// The second and the third segments contain the point with coordinate 3 while the first and the fourth
// segments contain the point with coordinate 6. All the four segments cannot be covered by a single
// point, since the segments [1, 3] and [5, 6] are disjoint.

#define MAX_N 100
#define MIN_N 1

#define MAX_AB 1e9
#define MIN_AB 0


#define TIME_LIMIT_CPP 1

// 1. for each segments pair 
// 2. choose any from intersections
// 3. choose max(from two start points) and min from (two end points)
typedef std::pair<int, int> Segment_t;
std::vector<int> GetMinimumPointsSequence(std::vector<Segment_t> &segments) {
    std::vector<int> points;
    if (segments.size()) {
        std::sort(
                segments.begin(), 
                segments.end(), 
                [](const Segment_t &a, const Segment_t &b) {
                    return std::get<1>(a) < std::get<1>(b);
                }
            );
        int last_point = std::get<1>(segments[0]);
        bool not_intersects = false;
        for (auto segment : segments) {
            not_intersects = (std::get<0>(segment) > last_point);
            if (not_intersects) {
                points.push_back(last_point);
                last_point = std::get<1>(segment);
            }
        }
        if (std::find(points.begin(), points.end(), last_point) == points.end()) {
            points.push_back(last_point);
        }
    }
    return points;
}



std::ostream& operator<< (std::ostream& os, const std::vector<int>& vector) {
    size_t idx = 0;
    for (const int &n : vector) {
        os << n << (idx < vector.size() - 1 ? ":" : "");
        idx++;
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, const Segment_t &segment) {
    os << "[" << std::get<0>(segment) << " " << std::get<1>(segment) << "]";
    return os;
}


int main () {
    int test_n;
    std::vector<int> result, expected;
    std::vector<Segment_t> segments;

    test_n = 1;
    segments = {
        {0, 1},
        {2, 3},
        {4, 5},
    };   
    result = GetMinimumPointsSequence(segments);
    expected = {1, 3, 5};
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    segments = {
        {0, 1},
        {1, 2},
        {2, 3},
    };   
    result = GetMinimumPointsSequence(segments);
    expected = {1, 3};
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    segments = {
        {0, 5},
        {1, 4},
        {2, 3},
    };   
    result = GetMinimumPointsSequence(segments);
    expected = {3};
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    segments = {
        {1, 3},
        {2, 5},
        {3, 6},
    };   
    result = GetMinimumPointsSequence(segments);
    expected = {3};
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
        throw std::logic_error(err_msg.str());
    }

    test_n += 1;
    segments = {
        {4, 7},
        {1, 3},
        {2, 5},
        {5, 6}
    };   
    result = GetMinimumPointsSequence(segments);
    expected = {3, 6};
    if (result != expected) {
        std::stringstream err_msg;
        err_msg << "FAILED TEST #: " << test_n << ", expected: "  << expected << ", got: " << result;
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
        segments.clear();
        for (int idx = 0; idx < n; idx++) {
            int a = dist_ab(rng);
            int b = dist_ab(rng);
            segments.push_back(
                Segment_t(std::min(a, b), std::max(a, b))
            );
        }
        result = GetMinimumPointsSequence(segments);
        t.stop();
        std::cout << "Elapsed time " << std::fixed << std::setprecision(9) << t 
        << ", input [" << n << "], output " << result << std::endl;
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
    }
}