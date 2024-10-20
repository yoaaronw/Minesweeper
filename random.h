/*copyright: professor fox */

/*
 * how to use this:
 * int x = Random::Int(0,50);
 * x will be a random number 0-50
 */

#pragma once
#include <random>
class Random {
    static std::mt19937 random;
public:
    static int Int(int min, int max);
};