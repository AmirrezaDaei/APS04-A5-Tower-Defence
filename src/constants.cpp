#include "constants.hpp"

int generateRandom(int from, int to) {
    random_device rd;
    mt19937 gen(rd()); 
    uniform_int_distribution<> dist(from, to);
    return dist(gen);
}