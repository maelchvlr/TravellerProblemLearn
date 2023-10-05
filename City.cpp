#include "City.h"
#include <iostream>

City::City(const std::string& name, int id) : name(name), ID(id) {}

void City::addRoad(City* destination, int cost) {
    roads.push_back(Road(destination, cost));
}

const std::string& City::getName() const {
    return name;
}

const std::vector<Road>& City::getRoads() const {
    return roads;
}

bool City::hasRoadTo(City* city) const
{
    std::cout << "Current city: " << name << " - Checking for road to: " << city->getName() << std::endl;
    for (Road r : roads)
    {
        std::cout << "Evaluating road to: " << r.getDestination()->getName() << std::endl;
        if (r.getDestination() == city)
        {
            std::cout << "Found road to: " << city->getName() << std::endl;
            return true;
        }
    }
    std::cout << "Did not find road to: " << city->getName() << std::endl;
    return false;
}

int City::getCostTo(const City* destination) const {
    for (const Road& road : roads) {
        if (road.getDestination() == destination) {
            return road.getCost();
        }
    }
    return -1;
}
