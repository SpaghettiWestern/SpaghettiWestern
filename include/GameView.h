#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "Orientation.h"
#include "Coordinate.h"
#include "ProjectionConstants.h"

class GameView{
private:
	double ZOOM_MAX = 4.;
	double ZOOM_MIN = 0.10;

	Coordinate3D<double> lookAtCoordinate;
	double zoom;
	Orientation viewAngleOrientation;

public:
	GameView();
	double getZoom() const;
	Coordinate3D<double> getLookAtCoordinate() const;

	// methods that change the view
	void scrollRight(double amount);
	void scrollLeft(double amount);
	void scrollUp(double amount);
	void scrollDown(double amount);
	void resetScroll();

	void zoomIn(double amount);
	void zoomOut(double amount);
	void resetZoom();

	void rotateViewAngleClockwise();
	void rotateViewAngleCounterClockwise();
	void resetViewAngle();

	// rendering info
	Coordinate2D<int> getRearColumn() const;
	Coordinate2D<int> getDiagonalTraversalVector() const;
};


#endif
