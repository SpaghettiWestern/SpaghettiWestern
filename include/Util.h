#ifndef UTIL_H
#define UTIL_H

#include <utility>
#include <iostream>
#include <cmath>
#include <random>

typedef std::pair<int, int> Coordinate;
typedef std::pair<double, double> ScreenCoordinate;

class Util{
private:
	static double epsilon();
	static std::default_random_engine generator;

public:
	static ScreenCoordinate coordToScreen(Coordinate loc);
	static Coordinate screenToCoord(ScreenCoordinate scr);
	static void printErrCoordinate(const Coordinate loc);
	static void printErrScreenCoordinate(const ScreenCoordinate scr);
	static bool almostEquals_ScreenCoordinate(const ScreenCoordinate& s1, const ScreenCoordinate& s2);

	static std::default_random_engine& getRandomEngine();
};


#endif
