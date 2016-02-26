#include "GameView.h"


GameView::GameView()
	: zoom(1)
{
}


double GameView::getZoom() const
{
	return zoom;
}


Coordinate3D<double> GameView::getLookAtCoordinate() const
{
	return lookAtCoordinate;
}


Coordinate2D<int> GameView::getRearColumn() const
{
	switch(viewAngleOrientation.getOrientation())
	{
	case 0:
		return Coordinate2D<int>(0, 0);
	case 1:
		return Coordinate2D<int>(0, 1);
	case 2:
		return Coordinate2D<int>(1, 1);
	case 3:
		return Coordinate2D<int>(1, 0);
	default:
		// Serious error!
		break;
	};
	return Coordinate2D<int>();
}


Coordinate2D<int> GameView::getDiagonalTraversalVector() const
{
	switch(viewAngleOrientation.getOrientation())
	{
	case 0:
		return Coordinate2D<int>(-1, 1);
	case 1:
		return Coordinate2D<int>(-1, -1);
	case 2:
		return Coordinate2D<int>(1, -1);
	case 3:
		return Coordinate2D<int>(1, 1);
	default:
		// Serious error!
		break;
	};
	return Coordinate2D<int>();
}


void GameView::scrollRight(double amount)
{
	lookAtCoordinate.x -= amount;
	lookAtCoordinate.y += amount;
}


void GameView::scrollLeft(double amount)
{
	lookAtCoordinate.x += amount;
	lookAtCoordinate.y -= amount;
}


void GameView::scrollUp(double amount)
{
	lookAtCoordinate.x += amount;
	lookAtCoordinate.y += amount;
}


void GameView::scrollDown(double amount)
{
	lookAtCoordinate.x -= amount;
	lookAtCoordinate.y -= amount;
}


void GameView::zoomIn(double amount)
{
	if (zoom + amount < ZOOM_MAX)
		zoom += amount;
}


void GameView::zoomOut(double amount)
{
	if (zoom - amount > ZOOM_MIN)
		zoom -= amount;
}
