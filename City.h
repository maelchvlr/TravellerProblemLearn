#pragma once

#include <string>
#include <vector>
#include "Road.h"  // Include Road because we need its complete type

class City {
public:
    City();
    City(const std::string& name, int id);
    void addRoad(City* destination, int cost);
    const std::string& getName() const;
    const std::vector<Road>& getRoads() const;
    bool hasRoadTo(City* city) const;
    int getCostTo(const City* destination) const;
    int getId() { return ID; }

private:
    std::string name;
    std::vector<Road> roads;
    int ID;
};