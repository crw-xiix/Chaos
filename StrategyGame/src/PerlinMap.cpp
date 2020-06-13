#pragma once
#include "pch.h"
#include "PerlinMap.h"
#include <random>
#include "Display.h"

PerlinMap::PerlinMap(int x, int y, unsigned long seed)
{
	width = x;
	height = y;
	this->seed = seed;
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
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{
			float fNoise = 0.0f;
			float fScaleAcc = 0.0f;
			float fScale = 1.0f;

			for (int o = 0; o < octaves; o++)
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

/*
				float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
				float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

*/

				fScaleAcc += fScale;
				fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
				fScale = fScale / fbias;
			}

			// Scale it
			evalues[y * width + x] = fNoise / fScaleAcc;
		}

}



//static
void PerlinMap::TestDraw()
{
	int w = 512;
	int h = 512;
	PerlinMap map = PerlinMap(w, h,100);
	map.Randomize();
	map.MakePerlin();
	SDL_Renderer* ren = Display::GetRenderer();
	//now to draw it.........   ugh
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int val = map.evalues[y * w + x] * 255;
			if (val > 255) val = 255;
			if (val < 0) val = 0;
			SDL_SetRenderDrawColor(ren, val, val, val, 255);
			SDL_RenderDrawPoint(ren, x, y);
		}
	}
}

void PerlinMap::Randomize()
{
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            svalues[y * width + x] = dis(gen);
        }
    }
}

