#include "timer.h"
#include <random>
#define MAX_SIZE 100000
#define TIME_LIMIT_CPP 1

int main() {
    Timer t;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 2 * MAX_SIZE);
    while(true) {
        t.start();
        auto number = dist(rng);
        t.stop();
        std::cout << "Elapsed time " << t << std::endl;        
    }
}