#include "Util.h"

std::default_random_engine Util::generator;

double Util::epsilon(){
	return 0.0000000001;
}

Coordinate2D<double> Util::coordToScreen(Coordinate3D<int> loc){
	return Coordinate2D<double>(loc.x/20.0, loc.y/20.0);
}

Coordinate3D<int> Util::screenToCoord(Coordinate2D<double> scr){
	return Coordinate3D<int>((int)(scr.x*20.0+epsilon()), (int)(scr.y*20.0+epsilon()), 0);
}

void Util::printErrCoordinate(const Coordinate3D<int> loc){
	std::cerr << "(" << loc.x << "," <<loc.y << ")";
}
void Util::printErrScreenCoordinate(const Coordinate2D<double> scr){
	std::cerr << std::fixed << "(" << scr.x << "," <<scr.y << ")";
}

bool Util::almostEquals_ScreenCoordinate(const Coordinate2D<double>& s1, const Coordinate2D<double>& s2){
	return (std::abs(s1.x - s2.x) < epsilon()) && (std::abs(s1.y - s2.y) < epsilon());
}

std::default_random_engine& Util::getRandomEngine(){
	return generator;
}



