#ifndef UTIL_H
#define UTIL_H

#include <utility>
#include <iostream>
#include <cmath>


typedef std::pair<int, int> Coordinate;
typedef std::pair<double, double> ScreenCoordinate;


class Util{
private:
	static double epsilon(){return 0.0000000001;}

public:
	static ScreenCoordinate coordToScreen(Coordinate loc);
	static Coordinate screenToCoord(ScreenCoordinate scr);
	static void printErrCoordinate(const Coordinate loc);
	static void printErrScreenCoordinate(const ScreenCoordinate scr);
	static bool almostEquals_ScreenCoordinate(const ScreenCoordinate& s1, const ScreenCoordinate& s2);
};



#endif
