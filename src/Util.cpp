#include "Util.h"

ScreenCoordinate Util::coordToScreen(Coordinate loc){
	return ScreenCoordinate(loc.first/20.0, loc.second/20.0);
}

Coordinate Util::screenToCoord(ScreenCoordinate scr){
	return Coordinate((int)(scr.first*20), (int)(scr.second*20));
}

void Util::printErrCoordinate(const Coordinate loc){
	std::cerr << "(" << loc.first << "," <<loc.second << ")";
}
void Util::printErrScreenCoordinate(const ScreenCoordinate scr){
	std::cerr << "(" << scr.first << "," <<scr.second << ")";
}
