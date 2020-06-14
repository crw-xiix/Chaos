#pragma once
#include "pch.h"
#include "PerlinMap.h"
#include <random>
#include "Display.h"

PerlinMap::PerlinMap(int x, int y)
{
	width = x;
	height = y;

	evalues = new float[(size_t)x * y];
	svalues = new float[(size_t)x * y];
}

PerlinMap::~PerlinMap()
{
    if (svalues) delete[] svalues;
    if (evalues) delete[] evalues;
}

void PerlinMap::MakePerlin()
{
	float fbias = 2.0f;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++)
		{
			float fNoise = 0.0f;
			float fScaleAcc = 0.0f;
			float fScale = 1.0f;

			for (int o = 0; o < (octaves-1); o++)
			{
				int nPitch = width >> o;
				int nSampleX1 = (x / nPitch) * nPitch;
				int nSampleY1 = (y / nPitch) * nPitch;

				int nSampleX2 = (nSampleX1 + nPitch) % width;
				int nSampleY2 = (nSampleY1 + nPitch) % width;

				float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
				float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

				float fSampleT = (1.0f - fBlendX) * svalues[nSampleY1 * width + nSampleX1] + fBlendX * svalues[nSampleY1 * width + nSampleX2];
				float fSampleB = (1.0f - fBlendX) * svalues[nSampleY2 * width + nSampleX1] + fBlendX * svalues[nSampleY2 * width + nSampleX2];

				fScaleAcc += fScale;
				fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
				fScale = fScale / fbias;
			}
			// Scale it
			evalues[y * width + x] = fNoise / fScaleAcc;
		}
	}
}

void PerlinMap::Normalize()
{
	float max = -100.0f;
	float min = 100.0f;
	for (int i = 0; i < (width * height); i++) {
		if (evalues[i] > max) max = evalues[i];
		if (evalues[i] < min) min = evalues[i];
	}
	float diff = max - min;
	float mult = 1 / diff;
	for (int i = 0; i < (width * height); i++) {
		evalues[i] -= min;
		evalues[i] *= mult;
	}
}



int PerlinMap::GetTerrain(int x, int y, int max)
{
	float val = evalues[y * width + x];
	val = val * max;
	if (val < 0) val = 0;
	if (val >= max) val = max - 1;
	return val;
}

//static
void PerlinMap::TestDraw()
{
	int w = 512;
	int h = 512;
	int rval = rand() % 500;
	PerlinMap map = PerlinMap(w, h);
	map.Randomize(107);
	map.MakePerlin();
	map.Normalize();
	SDL_Renderer* ren = Display::GetRenderer();
	//now to draw it.........   ugh
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int val = map.GetTerrain(x, y, 8) * 32;
			if (val > 255) val = 255;
			if (val < 0) val = 0;
			SDL_SetRenderDrawColor(ren, val, val, val, 255);
			SDL_RenderDrawPoint(ren, x, y);
		}
	}
}

void PerlinMap::Randomize(int iseed)
{
    std::mt19937 gen(iseed);
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            svalues[y * width + x] = dis(gen);
        }
    }
}

