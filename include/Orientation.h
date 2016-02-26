/*
 * Orientation.h
 *
 *  Created on: Feb 21, 2016
 *      Author: Nate
 */

#ifndef INCLUDE_ORIENTATION_H_
#define INCLUDE_ORIENTATION_H_


class Orientation
{
public:
	Orientation()
		: orientation(0) {}
	inline int getOrientation() const { return orientation; }
	inline void rotateClockwise() { orientation = (orientation + 1)%4; }
	inline void rotateCounterClockwise() { orientation = (orientation - 1)%4; }
	inline void rotate(int rotation) { orientation = (orientation + rotation)%4; }

private:
	int orientation;
};


#endif /* INCLUDE_ORIENTATION_H_ */
