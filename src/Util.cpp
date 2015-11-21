#include "Util.h"

std::default_random_engine Util::generator;

double Util::epsilon(){
	return 0.0000000001;
}

ScreenCoordinate Util::coordToScreen(Coordinate loc){
	return ScreenCoordinate(loc.first/20.0, loc.second/20.0);
}

Coordinate Util::screenToCoord(ScreenCoordinate scr){
	return Coordinate((int)(scr.first*20.0+epsilon()), (int)(scr.second*20.0+epsilon()));
}

void Util::printErrCoordinate(const Coordinate loc){
	std::cerr << "(" << loc.first << "," <<loc.second << ")";
}
void Util::printErrScreenCoordinate(const ScreenCoordinate scr){
	std::cerr << std::fixed << "(" << scr.first << "," <<scr.second << ")";
}

bool Util::almostEquals_ScreenCoordinate(const ScreenCoordinate& s1, const ScreenCoordinate& s2){
	return (std::abs(s1.first - s2.first) < epsilon()) && (std::abs(s1.second - s2.second) < epsilon());
}

std::default_random_engine& Util::getRandomEngine(){
	return generator;
}



