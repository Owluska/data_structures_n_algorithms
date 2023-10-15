#include "timer.h"
#include <random>
#include <sstream>

// /usr/bin/time output/lcm_assignment 
#define MAX_SIZE 45
#define MIN_VALUE 1
#define MAX_VALUE 2 * 1000000000
#define TIME_LIMIT_CPP 1

int GCDNaive(const int &a, const int &b) {
    // The greatest common divisor GCD(𝑎, 𝑏) of two non-negative integers 𝑎 and 𝑏
    // (which are not both equal to 0)
    if (a == 0 || b == 0) {
        return 0;
    }
    int n1 = a > b ? a : b;
    int n2 = b < a ? b : a;
    int r = n2 % n1;
    while (r != 0) {
        n2 = n1;
        n1 = r;
        r = n2 % n1;
    }
    return n1;
}

uint64_t LCMNaive(const uint64_t &a, const uint64_t &b) {
// Task. Given two integers 𝑎 and 𝑏, find their least common multiple.
// Input Format. The two integers 𝑎 and 𝑏 are given in the same line separated by space.
// Constraints. 1 ≤ 𝑎, 𝑏 ≤ 2 · 10^9 .
// Output Format. Output the least common multiple of 𝑎 and 𝑏.
    auto gcd = GCDNaive(a, b);
    return a * (b / gcd);
}


int main() {
    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(MIN_VALUE, MAX_VALUE);
    while(true) {
        t.start();
        int a = dist(rng);
        int b = dist(rng);
        auto lcm =  LCMNaive(a, b);
        t.stop();
        std::cout << "LCM: " << lcm << ", a: " << a << ", b " << b <<  ", elapsed time " << std::fixed << t << std::endl;
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
        exit(0);
    }
}