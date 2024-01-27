#include "timer.h"
#include <set>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>

#define MAX_N 1e5
#define MIN_N 1


#define MAX_COORD 1e9
#define MIN_COORD 1e-9

#define TIME_LIMIT_CPP 1
// https://www.geeksforgeeks.org/closest-pair-of-points-using-divide-and-conquer-algorithm/
// https://www.youtube.com/watch?v=6u_hWxbOc7E&ab_channel=iDeer7

// Problem Introduction
// In this problem, your goal is to find the closest pair of points among the given 𝑛
// points. This is a basic primitive in computational geometry having applications in,
// for example, graphics, computer vision, traffic-control systems.
// Problem Description
// Task. Given 𝑛 points on a plane, find the smallest distance between a √︀
// pair of two (different) points. Recall
// that the distance between points (𝑥 1 , 𝑦 1 ) and (𝑥 2 , 𝑦 2 ) is equal to (𝑥 1 − 𝑥 2 ) 2 + (𝑦 1 − 𝑦 2 ) 2 .
// Input Format. The first line contains the number 𝑛 of points. Each of the following 𝑛 lines defines a point
// (𝑥 𝑖 , 𝑦 𝑖 ).
// Constraints. 2 ≤ 𝑛 ≤ 10 5 ; −10 9 ≤ 𝑥 𝑖 , 𝑦 𝑖 ≤ 10 9 are integers.
// Output Format. Output the minimum distance. The absolute value of the difference between the answer
// of your program and the optimal value should be at most 10 −3 . To ensure this, output your answer
// with at least four digits after the decimal point (otherwise your answer, while being computed correctly,
// can turn out to be wrong because of rounding issues).
// Sample 1.
// Input:
// 2
// 00
// 34
// Output:
// 5.0
// There are only two points here. The distance between them is 5.
// Sample 2.
// Input:
// 4
// 77
// 1 100
// 48
// 77
// Output:
// 0.0
// There are two coinciding points among the four given points. Thus, the minimum distance is zero.
struct Point2d_t {
  double x;
  double y;

  Point2d_t() {
    this->x = 0.0;
    this->y = 0.0;
  }

  Point2d_t(const double &x, const double &y) {
    this->x = x;
    this->y = y;
  }

  double eucliaidian_dist(const Point2d_t &other_p) const {
    Point2d_t diff = {
      this->x - other_p.x,
      this->y - other_p.y,
    };
    return std::hypot(diff.x, diff.y);
  }
};


struct PointsPair {
  Point2d_t p1;
  Point2d_t p2;
  double dist;

  PointsPair() {
    this->p1 = Point2d_t();
    this->p2 = Point2d_t();
    dist = 0.0;
  }

  PointsPair(const Point2d_t &input_p1, const Point2d_t &input_p2) {
    this->p1 = input_p1;
    this->p2 = input_p2;
    dist = this->p1.eucliaidian_dist(this->p2);
  }

  bool PointsDifferent() {
    return this->dist != 0;
  }
};

// Point2d_t operator- (const Point2d_t &p1, const Point2d_t &p2) {
//   Point2d_t subs = {
//     p1.x - p2.x,
//     p1.y - p2.y,
//   };
//   return subs;
// }

std::ostream& operator<< (std::ostream &os, const Point2d_t &p) {
  os << "[" << p.x << ", " << p.y<< "]";
  return os;
}

std::ostream& operator<< (std::ostream &os, const std::vector<Point2d_t> &data) {
  size_t idx = 0;
  for (const Point2d_t &n : data) {
    os << n << (idx < data.size() - 1 ? ", " : "");
    idx++;
  }
  return os;
}

std::ostream& operator<< (std::ostream &os, const PointsPair &pair) {
  os << "p1:" << pair.p1 << ", p2:" << pair.p2 << ", dist:" << pair.dist;
  return os;
}

bool operator== (const Point2d_t &p1, const Point2d_t &p2) {
  return p1.eucliaidian_dist(p2) < 0.001;
}

bool operator!= (const PointsPair &pair1, const PointsPair &pair2) {
  // dist between two points not depens on order
  bool direct = !(pair1.p1 == pair2.p1 && pair1.p2 == pair2.p2);
  bool inverse = !(pair1.p1 == pair2.p2 && pair1.p2 == pair2.p1);
  return inverse & direct;
}

PointsPair GetClosestPointsFromPairs(const PointsPair &pair1, PointsPair &pair2) {
  PointsPair result = PointsPair(Point2d_t(MAX_COORD, MAX_COORD), Point2d_t(MIN_COORD, MIN_COORD));
  bool updated = false;
  std::vector<PointsPair> combinations = {
    pair1, 
    pair2, 
    PointsPair(pair1.p1, pair2.p1), 
    PointsPair(pair1.p2, pair2.p1),
    PointsPair(pair1.p1, pair2.p2),
    PointsPair(pair1.p2, pair2.p2)
  };

  for (auto pair : combinations) {
    // if (pair.dist == 0) {
    //   continue;
    // }
    if (pair.dist < result.dist) {
      result = pair;
    }
  }
  return result;
}

PointsPair Partition(
  const std::vector<Point2d_t> &half1, const std::vector<Point2d_t> &half2, 
  const PointsPair &closest_pair1, const PointsPair &closest_pair12, const double &middle_x) {
  PointsPair result = closest_pair1.dist < closest_pair12.dist ? closest_pair1 : closest_pair12;
  std::vector<Point2d_t> strip;
  double min_dist = result.dist;
  
  for (auto pt : half1) {
    if (std::abs(pt.x - middle_x) < min_dist) {
      strip.push_back(pt);
    } 
  }

  for (auto pt : half2) {
    if (std::abs(pt.x - middle_x) < min_dist) {
      strip.push_back(pt);
    } 
  }
  std::sort(
    strip.begin(), strip.end(), [](const Point2d_t &lhs, const Point2d_t &rhs) { return lhs.y < rhs.y; });

  for (int i = 0; i < strip.size(); i++) {
    for (int j = i + 1; j < strip.size(); j++) {
      if (strip[j].y - strip[i].y >= min_dist) {
        break;
      }
      if (strip[j].eucliaidian_dist(strip[i]) < result.dist) {
        result = PointsPair(strip[i], strip[j]);
      } 
    }
  }
  return result;
}


PointsPair GetClosestPointsPiar(std::vector<Point2d_t> &points) {
  PointsPair result;
  if (points.size() <= 3) {
    double min_dist = MAX_COORD;
    for (int i = 0; i < points.size(); i++) {
      // cause dist_ij == dist_ji
      for (int j = i + 1; j < points.size(); j++) {
        PointsPair current = PointsPair(points[i], points[j]);
        if (current.dist < min_dist) {
          result = current;
        }
      }
    }
    return result;
  }
  int last_idx = points.size() - 1;
  std::sort(
    points.begin(), points.end(), [](const Point2d_t &lhs, const Point2d_t &rhs) { return lhs.x < rhs.x; });
  int mid = std::min(points.size() / 2, points.size() - 1);
  double mid_x = points[mid].x;
  std::vector<Point2d_t> half_1(points.begin(), points.begin() + mid);
  std::vector<Point2d_t> half_2(points.begin() + mid, points.end());
  PointsPair frst_pair = GetClosestPointsPiar(half_1);
  PointsPair scnd_pair = GetClosestPointsPiar(half_2);
  result = Partition(half_1, half_2, frst_pair, scnd_pair, mid_x);
  return result;
}

void TestGetClosestPointsPiar(std::vector<Point2d_t> &points, const PointsPair &expected, const int &case_number) {
  auto result = GetClosestPointsPiar(points);
  if (result != expected) {
      std::stringstream err_msg;
      err_msg << "FAILED TEST #:" << case_number;
      err_msg << ", expected pair: "  << expected;
      err_msg << ", got pair: " << result;
      err_msg << std::endl;
      throw std::logic_error(err_msg.str());
  } else {
      std::cout << "PASSED TEST #:" << case_number;
      std::cout << ", expected pair: "  << expected;
      std::cout << ", got pair: " << result;
      std::cout << std::endl;
  }
}
int main() {
    int case_number = 0;
    std::vector<Point2d_t> case_data;
    PointsPair expected;

    case_number += 1;
    TestGetClosestPointsPiar(case_data, expected, case_number);

    case_number += 1;
    case_data = {
      Point2d_t(3.0, 4.0),
    };
    expected = PointsPair();
    TestGetClosestPointsPiar(case_data, expected, case_number);

    case_number += 1;
    case_data = {
      Point2d_t(0.0, 0.0),
      Point2d_t(3.0, 4.0),
    };
    expected = PointsPair(Point2d_t(0.0, 0.0), Point2d_t(3.0, 4.0));
    TestGetClosestPointsPiar(case_data, expected, case_number);

    case_number += 1;
    case_data = {
      Point2d_t(0.0, 0.0),
      Point2d_t(3.0, 4.0),
      Point2d_t(3.0, 4.25),
    };
    expected = PointsPair(Point2d_t(3.0, 4.0), Point2d_t(3.0, 4.25));
    TestGetClosestPointsPiar(case_data, expected, case_number);


    case_number += 1;
    case_data = {
      Point2d_t(7.0, 7.0),
      Point2d_t(1.0, 100.0),
      Point2d_t(4.0, 8.0),
      Point2d_t(7.0, 7.0),
    };
    expected = PointsPair(Point2d_t(7.0, 7.0), Point2d_t(7.0, 7.0));
    TestGetClosestPointsPiar(case_data, expected, case_number);


    case_number += 1;
    case_data = {
      Point2d_t(4.0, 4.0),
      Point2d_t(-2.0, -2.0),
      Point2d_t(-3.0, -4.0),
      Point2d_t(-1.0, 3.0),
      Point2d_t(2.0, 3.0),
      Point2d_t(-4.0, 0.0),
      Point2d_t(1.0, 1.0),
      Point2d_t(-1.0, -1.0),
      Point2d_t(3.0, -1.0),
      Point2d_t(-4.0, 2.0),
      Point2d_t(-2.0, 4.0),
    };
    expected = PointsPair(Point2d_t(-1.0, -1.0), Point2d_t(-2.0, -2.0));
    TestGetClosestPointsPiar(case_data, expected, case_number);


    case_number += 1;
    case_data = {
      Point2d_t(7.0, 7.0),
      Point2d_t(7.0, 7.0),
      Point2d_t(7.0, 7.0),
      Point2d_t(7.0, 7.0),
      Point2d_t(7.0, 7.0),
    };
    expected = PointsPair(Point2d_t(7.0, 7.0), Point2d_t(7.0, 7.0));
    TestGetClosestPointsPiar(case_data, expected, case_number);
   

    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(MIN_N, MAX_N);
    std::uniform_int_distribution<std::mt19937::result_type> dist_coords(MIN_COORD, MAX_COORD);
    while(true) {
      case_data.clear();
      int n = dist_n(rng);
      for (int i = 1; i <= n; i++) {
        double x = (double)dist_coords(rng);
        double y = (double)dist_coords(rng);
        case_data.push_back(Point2d_t(x, y));
      }
      t.start();
      auto result = GetClosestPointsPiar(case_data);
      t.stop();
      std::cout << "Elapsed time " << t;
      std::cout << std::fixed << std::setprecision(9);
      std::cout << ", input size " << case_data.size();
      std::cout << ", result " << result;
      std::cout << std::endl;
      if (t.secs() > TIME_LIMIT_CPP) {
          break;
      }
  }
}