/*
 * Coordinate.h
 *
 *  Created on: Feb 21, 2016
 *      Author: Nate
 */

#ifndef INCLUDE_COORDINATE_H_
#define INCLUDE_COORDINATE_H_


template <class T> class Coordinate2D
{
public:
	T x, y;

	Coordinate2D()
		: x(0), y(0) {}
	Coordinate2D(T u, T v)
		: x(u), y(v) {}
	Coordinate2D(const Coordinate2D &other)
		: x(other.x), y(other.y){}
};


template <class T> class Coordinate3D
{
public:
	T x, y, z;

	Coordinate3D()
		: x(0), y(0), z(0) {}
	Coordinate3D(T u, T v, T w)
		: x(u), y(v), z(w) {}
	Coordinate3D(const Coordinate3D<T> &other)
		: x(other.x), y(other.y), z(other.z) {}
	Coordinate3D(const Coordinate2D<T> &other, T w)
		: x(other.x), y(other.y), z(w) {}
};


#endif /* INCLUDE_COORDINATE_H_ */
