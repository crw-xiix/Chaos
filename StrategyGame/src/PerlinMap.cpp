#pragma once
#include "pch.h"
#include "PerlinMap.h"
#include <random>

PerlinMap::PerlinMap(int x, int y, unsigned long seed)
{
	width = x;
	height = y;
	this->seed = seed;
	evalues = new float[x * y];
	svalues = new float[x * y];
}

PerlinMap::~PerlinMap()
{
    if (svalues) delete[] svalues;
    if (evalues) delete[] evalues;
}

void PerlinMap::Randomize()
{
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < width; y++) {
            svalues[y * width + x] = dis(gen);
        }
    }
}

float PerlinMap::getTestValue()
{
    return svalues[9];
}
