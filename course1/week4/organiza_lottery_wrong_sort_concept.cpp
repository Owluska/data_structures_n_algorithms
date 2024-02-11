#include "timer.h"
#include <set>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>


#define MAX_SP 5e3
#define MIN_SP 1

#define MAX_AB 1e8
#define MIN_AB -10000000

#define TIME_LIMIT_CPP 1
// Problem Introduction
// You are organizing an online lottery. To participate, a person bets on a single
// integer. You then draw several ranges of consecutive integers at random.
// A participant’s payoff then is proportional to the number of ranges that
// contain the participant’s number minus the number of ranges that does not
// contain it. You need an efficient algorithm for computing the payoffs for all
// participants. A naive way to do this is to simply scan, for all participants, the
// list of all ranges. However, you lottery is very popular: you have thousands
// of participants and thousands of ranges. For this reason, you cannot afford
// a slow naive algorithm.
// Problem Description
// Task. You are given a set of points on a line and a set of segments on a line. The goal is to compute, for
// each point, the number of segments that contain this point.
// Input Format. The first line contains two non-negative integers 𝑠 and 𝑝 defining the number of segments
// and the number of points on a line, respectively. The next 𝑠 lines contain two integers 𝑎 𝑖 , 𝑏 𝑖 defining
// the 𝑖-th segment [𝑎 𝑖 , 𝑏 𝑖 ]. The next line contains 𝑝 integers defining points 𝑥 1 , 𝑥 2 , . . . , 𝑥 𝑝 .
// Constraints. 1 ≤ 𝑠, 𝑝 ≤ 50000; −10 8 ≤ 𝑎 𝑖 ≤ 𝑏 𝑖 ≤ 10 8 for all 0 ≤ 𝑖 < 𝑠; −10 8 ≤ 𝑥 𝑗 ≤ 10 8 for all 0 ≤ 𝑗 < 𝑝.
// Output Format. Output 𝑝 non-negative integers 𝑘 0 , 𝑘 1 , . . . , 𝑘 𝑝−1 where 𝑘 𝑖 is the number of segments which
// contain 𝑥 𝑖 . More formally,
// 𝑘 𝑖 = |{𝑗 : 𝑎 𝑗 ≤ 𝑥 𝑖 ≤ 𝑏 𝑗 }| .
// Sample 1.
// Input:
// 23
// 05
// 7 10
// 1 6 11
// Output:
// 100
// Here, we have two segments and three points. The first point lies only in the first segment while the
// remaining two points are outside of all the given segments.
// Sample 2.
// Input:
// 13
// -10 10
// -100 100 0
// Output:
// 001
// 8Sample 3.
// Input:
// 32
// 05
// -3 2
// 7 10
// 16
// Output:
// 20

struct Segment {
    int start = 0;
    int end = 0;

    Segment() {
        this->start = 0;
        this->end = 0;
    }

    Segment(const int &new_start, const int &new_end) {
      this->start = new_start < new_end ? new_start : new_end;
      this->end = new_end > new_start ? new_end : new_start;
    }
};

std::ostream& operator<< (std::ostream &os, const Segment &segment) {
  os << "[" << segment.start << ", " << segment.end << "]";
  return os;
}


template <typename T>
std::ostream& operator<< (std::ostream &os, const std::vector<T> &data) {
  size_t idx = 0;
  for (auto n : data) {
    os << n << (idx < data.size() - 1 ? ", " : "");
    idx++;
  }
  return os;
}

bool IsPointInSegment(const int &point, const Segment &segment) {
  bool result= false;
  if (point >= segment.start && point <= segment.end) {
    result = true;
  }
  return result;
}

int GetNumberOfContainingSegments(const int &point, const std::vector<Segment> &segments) {
  // end is index
  int result = 0;
  if (segments.size() < 2) {
    for (auto segment : segments) {
      result = IsPointInSegment(point, segment);
    }
    return result;
  }
  int mid = segments.size() / 2;
  std::vector<Segment> left_part(segments.begin(), segments.begin() + mid);
  std::vector<Segment> right_part(segments.begin() + mid, segments.end());
  result = GetNumberOfContainingSegments(point, left_part) + GetNumberOfContainingSegments(point, right_part);
  return result;
}

std::vector<int> GetNumbersOfContainingSegments(
    const std::vector<int> &points, const std::vector<Segment> &segments) {
  std::vector<int> result;
  for (auto p : points) {
    int n = GetNumberOfContainingSegments(p, segments);
    result.push_back(n);
  }
  return result;
}



void TestGetNumberOfContainingSegments(
    const std::vector<int> &points, const std::vector<Segment> &segments, const std::vector<int> &expected, const int &case_number) {
  auto result = GetNumbersOfContainingSegments(points, segments);
  if (result != expected) {
      std::stringstream err_msg;
      err_msg << "FAILED TEST #:" << case_number;
      err_msg << ", expected: "  << expected;
      err_msg << ", got: " << result;
      err_msg << std::endl;
      throw std::logic_error(err_msg.str());
  } else {
      std::cout << "PASSED TEST #:" << case_number;
      std::cout << ", expected: "  << expected;
      std::cout << ", got: " << result;
      std::cout << std::endl;
  }
}

int main() {
  int case_number = 0;
  std::vector<int> case_points, expected;
  std::vector<Segment> case_segments;

  case_number += 1;
  TestGetNumberOfContainingSegments(case_points, case_segments, expected, case_number);

  case_number += 1;
  case_points = {
    1, 6, 11
  };
  case_segments = {
    Segment(0, 5),
    Segment(7, 10),
  };
  expected = {
    1, 0, 0
  };
  TestGetNumberOfContainingSegments(case_points, case_segments, expected, case_number);

  case_number += 1;
  case_points = {
    -100, 100, 0
  };
  case_segments = {
    Segment(-10, 10),
  };
  expected = {
    0, 0, 1
  };
  TestGetNumberOfContainingSegments(case_points, case_segments, expected, case_number);


  case_number += 1;
  case_points = {
    1, 6
  };
  case_segments = {
    Segment( 0, 5),
    Segment(-3, 2),
    Segment( 7, 10),


  };
  expected = {
    2, 0
  };
  TestGetNumberOfContainingSegments(case_points, case_segments, expected, case_number);
   

    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_sp(MIN_SP, MAX_SP);
    std::uniform_int_distribution<std::mt19937::result_type> dist_ab(MIN_AB, MAX_AB);
    while(true) {
      case_points.clear();
      case_segments.clear();
      int points_number = dist_sp(rng);
      for (int i = 1; i <= points_number; i++) {
        case_points.push_back(dist_ab(rng));
      }
      int segments_number = dist_sp(rng);
      for (int i = 1; i <= segments_number; i++) {
        int a = dist_ab(rng);
        int b = dist_ab(rng);
        case_segments.push_back(Segment(a, b));
      }
      std::cout << ", input size " << segments_number << ":" << points_number << std::endl;
      t.start();
      auto result = GetNumbersOfContainingSegments(case_points, case_segments);
      t.stop();
      std::cout << "Elapsed time " << t;
      std::cout << std::fixed << std::setprecision(9);
      std::cout << ", input size " << segments_number * points_number;
      std::cout << std::endl;
      if (t.secs() > TIME_LIMIT_CPP) {
          break;
      }
  }
}