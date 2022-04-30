#include "utility.h"

/* Adapted from: https://stackoverflow.com/questions/8157340/unbiased-random-number-generator */
int Utility::GetRandom(int min, int max) {
    std::uniform_int_distribution<int> gen(min, max);
    return gen(rng);
}
