#include "Road.h"
#include "City.h"
#include <vector>
#include <iostream>
#include <string>

#define MAXCOST 999999999

int tsp(City* currentCity, City* startingCity, int visitedCount, int currentCost, std::vector<bool>& visited) {

    // If we visited all cities and can return to start
    if (visitedCount == visited.size() && currentCity->hasRoadTo(startingCity)) {
        return currentCost + currentCity->getCostTo(startingCity);
    }

    int minPathCost = MAXCOST;
    for (const Road& road : currentCity->getRoads()) {
        City* nextCity = road.getDestination();

        if (!visited[nextCity->getId()]) {
            visited[nextCity->getId()] = true;
            int pathCost = tsp(nextCity, startingCity, visitedCount + 1, currentCost + road.getCost(), visited);
            if (pathCost < minPathCost) {
                minPathCost = pathCost;
            }
            visited[nextCity->getId()] = false;  // backtrack
        }
    }

    return minPathCost;
}






int main(int argc, char* argv[])
{
    char choice;
    std::cout << "Do you want to use a demo with a limited amout of cities ? (Y/N) : ";
    std::cin >> choice;

    std::vector<City*> cities;
    int startingCity = 0;
    
    if (choice == 'Y')
    {
        char starting;
        std::cout << "Enter the number corresponding to the city you wanna start from : "
            << std::endl
            << "A (0), B (1), C (2), D (3), E (4)"
            << std::endl;

        std::cin >> starting;
        std::cin.ignore();

        while ((starting - '0') > 4)
        {
            std::cout << "Your choice is out of the scope of the options, try again." << std::endl;
            std::cin >> starting;
            std::cin.ignore();
        }

        startingCity = starting - '0';

        // Create cities
        cities.push_back(new City("A", 0));
        cities.push_back(new City("B", 1));
        cities.push_back(new City("C", 2));
        cities.push_back(new City("D", 3));
        cities.push_back(new City("E", 4));

        // Connect cities with roads
        cities[0]->addRoad(cities[1], 2);
        cities[0]->addRoad(cities[2], 2);

        cities[1]->addRoad(cities[0], 2);
        cities[1]->addRoad(cities[2], 3);
        cities[1]->addRoad(cities[3], 3);
        cities[1]->addRoad(cities[4], 1);

        cities[2]->addRoad(cities[0], 2);
        cities[2]->addRoad(cities[1], 3);
        cities[2]->addRoad(cities[3], 1);
        cities[2]->addRoad(cities[4], 3);

        cities[3]->addRoad(cities[1], 3);
        cities[3]->addRoad(cities[2], 1);
        cities[3]->addRoad(cities[4], 3);

        cities[4]->addRoad(cities[1], 3);
        cities[4]->addRoad(cities[2], 1);
        cities[4]->addRoad(cities[3], 3);
    }

    if (choice == 'N')
    {
        std::string cityName;
        std::string road;
        int id = -1;
        while (cityName != "quit")
        {
            std::cout << "Enter the name of the cities, if you're done adding cities, type quit." << std::endl;
            std::cin >> cityName;
            if (cityName != "quit")
            {
                id++;
                cities.push_back(new City(cityName, id));
                std::cout << "city " << cityName << " ID : " << id << " created (Write the ID down, you'll need it on next step" << std::endl;
            }
        }

        std::cout << "You will now add road connections, to do so, type one by one origin city ID, destination city ID and cost. If you're done, type quit."
            << std::endl
            << "Example : 0 then 1 then 3"
            << std::endl << "Be aware that this section of the code doesn't handle user errors."
            << std::endl;

        int roadOrigin;
        int roadArrival;
        int cost;
     
        while (road != "quit")
            {
                std::cout << "Origin ID (quit to stop adding roads) : ";
                std::cin >> road;

                if (!(road == "quit"))
                {
                    roadOrigin = stoi(road);
                    std::cout << "Destination ID : ";
                    std::cin >> road;
            
                    roadArrival = stoi(road);
                    std::cout << "Cost : ";
                    std::cin >> road;

                    cost = stoi(road);
                    cities[roadOrigin]->addRoad(cities[roadArrival], cost);
                    std::cout << "Road created, next one. \n" << std::endl;
                }
            }

        std::cout << "Finally, enter the starting point (City ID)" << std::endl;
        
        std::cin >> cityName;
        startingCity = stoi(cityName);
    }

    std::vector<bool> travelled(cities.size(), false);
    travelled[startingCity] = true;


    int minCost = MAXCOST;
    std::cout << "starting city is : " << cities[startingCity]->getName() << std::endl;
    int minimum = tsp(cities[startingCity], cities[startingCity], 1, 0, travelled);


    std::cout << "Minimum cost of traveling through all cities : " << minimum << std::endl;
    std::cout << "If this number is equal to 999999999 it means either you have less than 3 cities \nor you forgot to add a connection back and forth to a city." << std::endl;

    return 0;
}