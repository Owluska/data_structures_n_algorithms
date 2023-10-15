#include "timer.h"
// to get statistic build than
//$/usr/bin/time -v output/sum_two_numbers
int main () {
    Timer timer;
    timer.start();
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b << std::endl;
    timer.stop();
    std::cout << "Elapsed " << timer << " us" << std::endl;
    // do not forget this!!!
    return 0;
}