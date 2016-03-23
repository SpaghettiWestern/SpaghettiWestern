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


Coordinate2D<int> GameView::getRearColumn(int width, int length) const
{
	Coordinate2D<int> rearColumn;

	switch(viewAngleOrientation.getOrientation())
	{
	case 0:
		rearColumn.set(0,0);
		break;
	case 1:
		rearColumn.set(0, 1);
		break;
	case 2:
		rearColumn.set(1, 1);
		break;
	case 3:
		rearColumn.set(1, 0);
		break;
	default:
		// Serious error!
		break;
	};

	rearColumn.x *= width - 1;
	rearColumn.y *= length - 1;

	return rearColumn;
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
	lookAtCoordinate.x += amount;
	lookAtCoordinate.y -= amount;
}


void GameView::scrollLeft(double amount)
{
	lookAtCoordinate.x -= amount;
	lookAtCoordinate.y += amount;
}


void GameView::scrollUp(double amount)
{
	lookAtCoordinate.x -= amount;
	lookAtCoordinate.y -= amount;
}


void GameView::scrollDown(double amount)
{
	lookAtCoordinate.x += amount;
	lookAtCoordinate.y += amount;
}


void GameView::resetScroll()
{
	lookAtCoordinate.x = 0;
	lookAtCoordinate.y = 0;
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


void GameView::resetZoom()
{
	zoom = 1.;
}


void GameView::rotateViewAngleClockwise()
{
	viewAngleOrientation.rotateClockwise();
}


void GameView::rotateViewAngleCounterClockwise()
{
	viewAngleOrientation.rotateCounterClockwise();
}


void GameView::resetViewAngle()
{
	viewAngleOrientation.reset();
}
