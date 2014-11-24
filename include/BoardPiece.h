#ifndef BOARDPIECE_H
#define BOARDPIECE_H

#include "Util.h"

class GameBoard;

class BoardPiece{
private:

protected:
	Coordinate location;
	ScreenCoordinate screen_location;

	void resetScreenLocation();

public:
	BoardPiece();
	BoardPiece(Coordinate loc);

	Coordinate getLocation();
	void setLocation(Coordinate new_location);

	ScreenCoordinate getScreenLocation();

};

#endif
