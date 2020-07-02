#include "pch.h"
#include "pathfind.h"
#include <set>
#include <algorithm>
#include <random>





PathFinder::PathFinder(Map& imap) : map(imap)
{
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

PathFinder::xyRange PathFinder::pathGood(int x, int y)
{
	int d = ((*dRange)[y][x]);
	if (d < 0) d = Map::Size*2+1;
	return xyRange{ x,y,d };
}

/// <summary>
/// Get path to starts at x, y, and ends at pathfinder 0.  
/// This shall not be called if a path is not already possible.
/// </summary>
/// <param name="x">target x cell</param>
/// <param name="y">targer y cell</param>
/// <returns></returns>
std::vector<SDL_Point> PathFinder::GetPathTo(int x, int y)
{
	int sx = x;
	int sy = y;
	typedef std::tuple<int, int, int> xyRange;
	std::vector<xyRange> found;

	std::vector<SDL_Point> thePath;
	//This is our starting location.
	
	thePath.push_back(SDL_Point{ x,y });

	//It's zero when we find the target
	while ((*dRange)[y][x] > 1)
	{
		int d = (*dRange)[y][x];

		//std::cout << "Pos" << x << "," << y << " Dist: " << d << "\n";

		found.push_back(pathGood(x, y - 1));
		found.push_back(pathGood(x, y + 1));
		found.push_back(pathGood(x - 1, y));
		found.push_back(pathGood(x + 1, y));

		auto rng = std::default_random_engine{};
		std::shuffle(found.begin(), found.begin()+2,rng);

		std::sort(found.begin(), found.end() , 
			[](xyRange& a, xyRange& b) {
				return std::get<2>(a) < std::get<2>(b);
			}
			);

		//This gives us a little randomness in motion so they don't walk straight lines.
		int d1;
		int idx = 0;
		if (std::get<2>(found[0]) == std::get<2>(found[1])) {
			idx = rand() % 2;
		}

		std::tie(x, y, d1) = found[idx];

		d = d1;
		found.clear();
		thePath.push_back( SDL_Point{ x,y });
		if (thePath.size() > 20) {
			int bp = 0;
		}
	}
	return thePath;
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
			std::tie(sx, sy, d) = xy;
			bool isFound = false;
			//Figure out if that position is already found, we don't want to search 2-20x.
			//double searching makes bad paths.
			for (auto position : found) {
				int isx, isy, isd;
				std::tie(isx, isy, isd) = position;
				if ((sx == isx) && (sy == isy)) {
					isFound = true;
					break;
				}
			} //Back from break above
			if (!isFound) {
				//Check our max speed now
				if (d <= maxSpeed) {
					found.insert(xy);
				}
			}
			else {
				int bp = 0;
			}
		}
		mainSet.clear();
	}
}

PathFinder::~PathFinder()
{
	delete dRange;
}