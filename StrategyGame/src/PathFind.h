#pragma once

#include "pch.h"
#include "mapTile.h"
#include "map.h"
#include <vector>
#include "unit.h"



class PathFinder {
private:
    std::array<std::array<int, Map::Size>, Map::Size>* dMap = nullptr;
    std::array<std::array<int, Map::Size>, Map::Size>* dRange = nullptr;
    std::vector<SDL_Point> path;
    void resetMap();
    void calcFlood(int x, int y, int maxSpeed);
    bool rangeOpen(int x, int y, int &speed);
    Map& map;
public:
    PathFinder(Map& map);
    void DoUnitMaxDistanceTravel(const Unit& who, int val);
    void DoUnitMaxDistanceAttack(const Unit& who, int val, bool aerial);
    /// <summary>
    /// Returns the distance from calculated path.
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <returns>Returns the distance from calculated path.</returns>
    int GetRange(int x, int y);
    bool PathGood(int x, int y, int d);
    ~PathFinder();
};

