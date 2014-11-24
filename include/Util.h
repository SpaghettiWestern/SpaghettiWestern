#ifndef UTIL_H
#define UTIL_H

#include <utility>
#include <iostream>


typedef std::pair<int, int> Coordinate;
typedef std::pair<float, float> ScreenCoordinate;


class Util{
private:

public:
	static ScreenCoordinate coordToScreen(Coordinate loc);
	static Coordinate screenToCoord(ScreenCoordinate scr);
	static void printErrCoordinate(const Coordinate loc);
	static void printErrScreenCoordinate(const ScreenCoordinate scr);


};



#endif
