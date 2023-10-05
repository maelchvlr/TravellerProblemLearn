#pragma once  // To prevent multiple inclusions

class City;  // Forward declaration

class Road {
public:
    Road(City* destination, int cost);
    City* getDestination() const;
    int getCost() const;

private:
    City* destination;
    int cost;
};