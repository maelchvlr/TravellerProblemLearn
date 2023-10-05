#include "Road.h"
#include "City.h"

Road::Road(City* destination, int cost) : destination(destination), cost(cost) {}

City* Road::getDestination() const {
    return destination;
}

int Road::getCost() const {
    return cost;
}