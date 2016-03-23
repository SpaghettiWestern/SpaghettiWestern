#ifndef UTIL_H
#define UTIL_H

#include <utility>
#include <iostream>
#include <cmath>
#include <random>

#include "Coordinate.h"


class Util{
private:
	static double epsilon();
	static std::default_random_engine generator;

public:
	static Coordinate2D<double> coordToScreen(Coordinate3D<int> loc);
	static Coordinate3D<int> screenToCoord(Coordinate2D<double> scr);
	static void printErrCoordinate(const Coordinate3D<int> loc);
	static void printErrScreenCoordinate(const Coordinate2D<double> scr);
	static bool almostEquals_ScreenCoordinate(const Coordinate2D<double>& s1, const Coordinate2D<double>& s2);

	static std::default_random_engine& getRandomEngine();
};


#endif
