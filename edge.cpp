#include "edge.h"

//To make priority queue sort edges in increasing order with respect to distance
bool edge::operator < (edge b) const {
    return distance > b.distance;
}

// a < b