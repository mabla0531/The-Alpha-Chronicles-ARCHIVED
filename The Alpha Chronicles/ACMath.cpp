#include "ACMath.h"

FloatPoint getLengthRatio(float x, float y, float x1, float y1) {
	FloatPoint deltaLocation;
	deltaLocation.x = x - x1;
	deltaLocation.y = y - y1;
	//create a ratio from 0 to 1 based on pythagorean theorem
	FloatPoint ratio;
	ratio.x = deltaLocation.x / std::sqrt(std::pow(deltaLocation.x, 2) + std::pow(deltaLocation.y, 2));
	ratio.y = deltaLocation.y / std::sqrt(std::pow(deltaLocation.x, 2) + std::pow(deltaLocation.y, 2));

	return ratio;
}
