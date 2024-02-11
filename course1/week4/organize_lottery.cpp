#include "timer.h"
#include <set>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>
#include <map>


#define MAX_SP 50000
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
// Task. You are given a set of points on a line and a set of s on a line. The goal is to compute, for
// each point, the number of s that contain this point.
// Input Format. The first line contains two non-negative integers 𝑠 and 𝑝 defining the number of s
// and the number of points on a line, respectively. The next 𝑠 lines contain two integers 𝑎 𝑖 , 𝑏 𝑖 defining
// the 𝑖-th  [𝑎 𝑖 , 𝑏 𝑖 ]. The next line contains 𝑝 integers defining points 𝑥 1 , 𝑥 2 , . . . , 𝑥 𝑝 .
// Constraints. 1 ≤ 𝑠, 𝑝 ≤ 50000; −10 8 ≤ 𝑎 𝑖 ≤ 𝑏 𝑖 ≤ 10 8 for all 0 ≤ 𝑖 < 𝑠; −10 8 ≤ 𝑥 𝑗 ≤ 10 8 for all 0 ≤ 𝑗 < 𝑝.
// Output Format. Output 𝑝 non-negative integers 𝑘 0 , 𝑘 1 , . . . , 𝑘 𝑝−1 where 𝑘 𝑖 is the number of s which
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
// Here, we have two s and three points. The first point lies only in the first  while the
// remaining two points are outside of all the given s.
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

enum Types {
    start = 0,
    end = 1,
    point = 2
};

struct PointType {
    int data = 0;
    int type = Types::start;

    PointType() {
        this->data = 0;
        this->type = Types::start;
    }

    PointType(const int &new_data, const int &new_type) {
      this->data = new_data;
      this->type = new_type;
    }
};

std::ostream& operator<< (std::ostream &os, const PointType &point) {
  std::map<int, std::string> types = {
    {0, "start"},  {1, "end"},  {2, "point"},
  };
  os << "[" << point.data << ", " << types[point.type] << "]";
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

std::vector<PointType> PreprocessData(
    const std::vector<int> &points, const std::vector<std::vector<int>> &segmetns) {
	std::vector<PointType> result;
  for (const int &p : points) {
		result.push_back(PointType(p, Types::point));
	}
  for ( auto segment : segmetns) {
		// garantied by taks conditions
		// that points are sorted in the 
		result.push_back(PointType(segment[0], Types::start));
		result.push_back(PointType(segment[1], Types::end));
	}
	return result;
}

std::vector<int> GetNumbersOfContainings(
    const std::vector<int> &points, const std::vector<std::vector<int>> &s) {
  std::vector<int> result;
	auto data = PreprocessData(points, s);
	// 0(N *log(N))
	std::sort(
		data.begin(), data.end(), 
		[](const PointType &p1, const PointType &p2) { return p1.data < p2.data; });
	int starts = 0;
	int ends = 0;
	std::map<int, int> points_segments;
	// O(N + 2*M), n_ points, M - segments
  for (int i = 0; i < data.size(); i++) {
		auto point = data[i];
		if (point.type == Types::start) {
			starts += 1;
		}
			if (point.type == Types::end) {
			ends += 1;
		}
		int s = starts - ends;
		if (point.type == Types::point) {
			points_segments[point.data] = s;
		}
  }
	for (auto p : points) {
		result.push_back(points_segments.at(p));
	}
  return result;
}



void TestGetNumberOfContainings(
   const std::vector<int> &points, const std::vector<std::vector<int>> &s, const std::vector<int> &expected, const int &case_number) {
  auto result = GetNumbersOfContainings(points, s);
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
  std::vector<std::vector<int>> case_segmetns;

  case_number += 1;
  TestGetNumberOfContainings(case_points, case_segmetns, expected, case_number);

  case_number += 1;
  case_points = {
    1, 6, 11
  };
  case_segmetns = {
    {0,  5},
    {7, 10},
  };
  expected = {
    1, 0, 0
  };
  TestGetNumberOfContainings(case_points, case_segmetns, expected, case_number);

  case_number += 1;
  case_points = {
    -100, 100, 0
  };
  case_segmetns = {
    {-10, 10},
  };
  expected = {
    0, 0, 1
  };
  TestGetNumberOfContainings(case_points, case_segmetns, expected, case_number);


  case_number += 1;
  case_points = {
    1, 6
  };
  case_segmetns = {
    { 0,  5},
    {-3,  2},
    { 7, 10},


  };
  expected = {
    2, 0
  };
  TestGetNumberOfContainings(case_points, case_segmetns, expected, case_number);
   

    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_sp(MIN_SP, MAX_SP);
    std::uniform_int_distribution<std::mt19937::result_type> dist_ab(MIN_AB, MAX_AB);
    while(true) {
      case_points.clear();
      case_segmetns.clear();
      int points_number = dist_sp(rng);
      for (int i = 1; i <= points_number; i++) {
        case_points.push_back(dist_ab(rng));
      }
      int s_number = dist_sp(rng);
      for (int i = 1; i <= s_number; i++) {
        int a = dist_ab(rng);
        int b = dist_ab(rng);
        case_segmetns.push_back({a, b});
      }
      std::cout << ", input size " << s_number << ":" << points_number << std::endl;
      t.start();
      auto result = GetNumbersOfContainings(case_points, case_segmetns);
      t.stop();
      std::cout << "Elapsed time " << t;
      std::cout << std::fixed << std::setprecision(9);
      std::cout << ", input size " << s_number * points_number;
      std::cout << std::endl;
      if (t.secs() > TIME_LIMIT_CPP) {
          break;
      }
  }
}