#include <vector>
#include <random>
#include <set>
#include <algorithm>
#include "timer.h"

#define MAX_SIZE 100000
#define TIME_LIMIT_CPP 1

u_int64_t GetMaxPairWiseFast1(const std::vector<u_int64_t> &sequence) {
    // calculate max pairwaise product
    // garanteed that sequence starts from 1
    // 2 * O(N)
    u_int64_t result = 0;
    u_int64_t max_number = 0;
    u_int64_t index1 = 0;
    for (u_int64_t i = 0; i < sequence.size(); i++) {
        if (sequence[i] > max_number) {
            index1 = i;
            max_number = sequence[i];
        }
    }
    // std::cout << index1 << std::endl;
    u_int64_t index2 = 0;
    max_number = 0;
    for (u_int64_t i = 0; i < sequence.size(); i++) {
        if (i == index1 || sequence[i] == sequence[index1]) {
            continue;
        }
        if (sequence[i] > max_number) {
            index2 = i;
            max_number = sequence[i];
        }
    }
    // here result has to be int64 and data in seq too, because cimputing is perfoming from left to the right
    // std::cout << index2 << std::endl;
    if (index1 == index2) {
        return 0;
    }
    result = sequence[index1] * sequence[index2];
    return result;
}

u_int64_t GetMaxPairWiseFast2(const std::vector<u_int64_t> &sequence) {
    // calculate max pairwaise product
    // garanteed that sequence starts from 1
    u_int64_t result = 0;
    std::set<u_int64_t> uniques;
    // N * O(log(size()))
    for (u_int64_t i = 0; i < sequence.size(); i++) {
        // Logarithmic in the size of the container, O(log(size())).
        uniques.insert(sequence[i]);
    }
    // for (auto n : uniques) {
    //     std::cout << n << std::endl;
    // }
    // std::cout << *next(uniques.rbegin(), 1) << std::endl;
    // std::cout << *uniques.rbegin() << std::endl;
    if (uniques.size() > 1) {
        result = (*next(uniques.rbegin(), 1)) * (*uniques.rbegin());
    }
    return result;
}

u_int64_t GetMaxPairWiseFast3(const std::vector<u_int64_t> &sequence) {
    // calculate max pairwaise product
    // garanteed that sequence starts from 1
    // 2 * O(N)
    u_int64_t result = 0;
    u_int64_t max_number = 0;
    u_int64_t last_max_number = 0;
    u_int64_t index1 = 0;
    for (u_int64_t i = 0; i < sequence.size(); i++) {
        if (sequence[i] > max_number) {
            index1 = i;
            last_max_number = max_number;
            max_number = sequence[i];
        }
    }
    for (u_int64_t i = index1 + 1; i < sequence.size(); i++) {
        if (sequence[i] == sequence[index1]) {
            continue;
        }
        if (sequence[i] > last_max_number) {
            last_max_number = sequence[i];
        }
    }
    // here result has to be int64 and data in seq too, because cimputing is perfoming from left to the right
    if (last_max_number == max_number) {
        return 0;
    }
    result = last_max_number * max_number;
    return result;
}

u_int64_t GetMaxPairWiseEtalon(std::vector<u_int64_t> &sequence) {
    // calculate max pairwaise product
    // garanteed that sequence starts from 1
    // O(N·log(N)) 
    std::sort(sequence.begin(), sequence.end());
    u_int64_t max_number = *sequence.rbegin();
    u_int64_t last_max_number = 0;
    // N
    for (auto it = next(sequence.rbegin(), 1); it != sequence.rend(); it++) {
        auto n = *it;
        if (n != max_number) {
            last_max_number = n;
            break;
        }
    }
    // O (n^2 * log(N))

    auto result = last_max_number * max_number;
    return result;
}

u_int64_t GetMaxPairWiseNaive(const std::vector<u_int64_t> &sequence) {
    u_int64_t result = 0;
    for (u_int64_t i = 0; i < sequence.size(); i++) {
        for (u_int64_t j = i + 1; j < sequence.size(); j++) {
            u_int64_t n1 = sequence[i];
            u_int64_t n2 = sequence[j];
            if (n1 == n2) {
                continue;
            }
            u_int64_t pair = n1 * n2;
            result = std::max(result, pair);
        }
    }
    return result; 
}

int main () {
    Timer timer;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 2 * MAX_SIZE);
    while(true) {
        timer.start();
        std::vector<u_int64_t> sequence(0);
        uint16_t sequence_size = dist(rng);
        for (u_int64_t i = 1; i <= sequence_size; i++) {
            uint16_t n = dist(rng);
            sequence.push_back(n);
        }        
        auto result1 = GetMaxPairWiseFast3(sequence);
        auto result2 = GetMaxPairWiseEtalon(sequence);
        timer.stop();
        std::cout << "Elapsed " << timer << ", sequence size: " << sequence.size() << std::endl;
        if (result1 != result2) {
            for (auto n : sequence) {
                std::cout << n << " ";
            }
            std::cout << std::endl;
            std::cout << "FAILED, 1: " << result1 << ", 2: " << result2 << std::endl;
            break;
        } else if (timer.secs() > TIME_LIMIT_CPP) {
            std::cout << "TIME LIMIT EXCEEDED, sequence size: " << sequence.size()<< std::endl;
            break;
        } else {
            std::cout << "OK" << std::endl;
        }
    }

    return 0;
}