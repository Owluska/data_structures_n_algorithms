#include "timer.h"
#include <random>
#include <sstream>
#define MAX_SIZE 45
#define MIN_VALUE 1
#define MAX_VALUE 2 * 10^9
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


int main() {
    // a = 0, b != 0
    int a = 0;
    int b = 2;
    int exepected = 0;
    std::stringstream warn;
    auto gcd =  GCDNaive(a, b);
    if (gcd != exepected) {
        warn << "GCD calucaltion error, gcd: " << gcd;
        warn << ", a " << a;
        warn << ", b " << b;
        throw std::logic_error(warn.str());
    }
    // a != 0, b = 0
    a = 2;
    b = 0;
    exepected = 0;
    gcd =  GCDNaive(a, b);
    if (gcd != exepected) {
        warn << "GCD calucaltion error, gcd: " << gcd;
        warn << ", a " << a;
        warn << ", b " << b;
        throw std::logic_error(warn.str());
    }
    // a = b
    a = 2;
    b = 2;
    exepected = a;
    gcd =  GCDNaive(a, b);
    if (gcd != exepected) {
        warn << "GCD calucaltion error, gcd: " << gcd;
        warn << ", a " << a;
        warn << ", b " << b;
        throw std::logic_error(warn.str());
    }
    // gcd is 1
    a = 11;
    b = 3;
    exepected = 1;
    gcd =  GCDNaive(a, b);
    if (gcd != exepected) {
        warn << "GCD calucaltion error, gcd: " << gcd;
        warn << ", a " << a;
        warn << ", b " << b;
        throw std::logic_error(warn.str());
    }

    // a = 12, b = 36
    a = 12;
    b = 36;
    exepected = 12;
    gcd =  GCDNaive(a, b);
    if (gcd != exepected) {
        warn << "GCD calucaltion error, gcd: " << gcd;
        warn << ", a " << a;
        warn << ", b " << b;
        throw std::logic_error(warn.str());
    }   
    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(MIN_VALUE, MAX_VALUE);
    while(true) {
        t.start();
        int a = dist(rng);
        int b = dist(rng);
        auto gcd =  GCDNaive(a, b);
        t.stop();
        std::cout << "GCD: " << gcd << ", a: " << a << ", b " << b <<  ", elapsed time " << std::fixed << t << std::endl;
        if (t.secs() > TIME_LIMIT_CPP) {
            break;
        }
    }
}