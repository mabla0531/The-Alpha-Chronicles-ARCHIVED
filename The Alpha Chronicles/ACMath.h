#pragma once
#include <cmath>

/*
 * Contains specialized functions for various calculations
 * (primarily trigonometry) done throughout the game 
 */

struct FloatPoint {
	float x;
	float y;
};

FloatPoint getLengthRatio(float x, float y, float x1, float y1);