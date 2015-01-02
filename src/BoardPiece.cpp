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

const Coordinate& BoardPiece::getLocation() const{
	return location;
}

void BoardPiece::setLocation(Coordinate new_location){
	if(new_location != location){
		location = new_location;
		if(Util::screenToCoord(screen_location) != location){
			resetScreenLocation();
		}
	}
}

const ScreenCoordinate& BoardPiece::getScreenLocation() const{
	return screen_location;
}
