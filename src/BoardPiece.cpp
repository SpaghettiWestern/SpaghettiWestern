#include "BoardPiece.h"

BoardPiece::BoardPiece(){
	location = Coordinate(-1,-1);
	resetScreenLocation();
}

BoardPiece::BoardPiece(Coordinate loc){
	location = loc;
	resetScreenLocation();
}

void BoardPiece::resetScreenLocation(){
	screen_location = Util::coordToScreen(location);
}

Coordinate BoardPiece::getLocation(){
	return location;
}

void BoardPiece::setLocation(Coordinate new_location){
	location = new_location;
	resetScreenLocation();
}

ScreenCoordinate BoardPiece::getScreenLocation(){
	return screen_location;
}
