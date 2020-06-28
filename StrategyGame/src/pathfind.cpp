#include "pch.h"
#include "pathfind.h"
#include <set>

PathFinder::PathFinder(Map& imap) : map(imap)
{
//	dMap = new std::array<std::array<int, Map::Size>, Map::Size>();
	dRange = new std::array<std::array<int, Map::Size>, Map::Size>();
}

void PathFinder::DoUnitMaxDistanceTravel(const Unit& who, int val)
{
	ResetMap();
	calcFlood(who.GetX(),who.GetY(),who.GetSpeed());
}

void PathFinder::DoUnitMaxDistanceAttack(const Unit& who, int val, bool aerial)
{

}

int PathFinder::GetRange(int x, int y)
{
	return (*dRange)[y][x];
}

void PathFinder::ResetMap()
{
	for (int y = 0; y < Map::Size; y++) {
		for (int x = 0; x < Map::Size; x++) {
			//These are just other ways to access it...
			//dMap->at(j).at(i) = -1;
			//dMap->at(j)[i] = -1;
			//(*dMap)[y][x] = -1;
			(*dRange)[y][x] = -1;
		}
	}
}

std::vector<SDL_Point> PathFinder::GetPathTo(int x, int y)
{
	return std::vector<SDL_Point>();
}

bool PathFinder::rangeOpen(int x, int y, int& speed)
{
	speed = 255;
	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= Map::Size) return false;
	if (y >= Map::Size) return false;
	speed = map.Get(x, y).GetSpeed();
	if (speed < 99) {
		int bp = 0;
	}
	//if (((*dMap)[x][y]) != 0) return false;
	if (((*dRange)[y][x]) == -1) return true;
	return false;

}

void PathFinder::calcFlood(int x, int y, int maxSpeed)
{
	typedef std::tuple<int, int, int> xyRange;
	std::set<xyRange> found;
	found.insert(xyRange(x, y, 1));
	int speed = 0;
	while (found.size() > 0)
	{
		std::set<xyRange> mainSet;
		int sx, sy, d;
		for (xyRange xyz : found) {
			std::tie(sx, sy, d) = xyz;
			//Set this spot.
			(*dRange)[sy][sx] = d;
			if (rangeOpen(sx, sy - 1, speed)) mainSet.insert(xyRange(sx, sy - 1, d + speed));
			if (rangeOpen(sx, sy + 1, speed)) mainSet.insert(xyRange(sx, sy + 1, d + speed));
			if (rangeOpen(sx + 1, sy, speed)) mainSet.insert(xyRange(sx + 1, sy, d + speed));
			if (rangeOpen(sx - 1, sy, speed)) mainSet.insert(xyRange(sx - 1, sy, d + speed));
		}
		found.clear();
		for (xyRange xy : mainSet) {
			if (found.find(xy) == found.end()) {
				std::tie(sx, sy, d) = xy;
				//Check our max speed now
				if (d <= maxSpeed) {
					found.insert(xy);
				}
			}
			
		}
		mainSet.clear();
	}
}

bool PathFinder::PathGood(int x, int y, int d)
{
	return false;
}

PathFinder::~PathFinder()
{
	delete dRange;
}