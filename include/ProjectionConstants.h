/*
 * ProjectionConstants.h
 *
 *  Created on: Feb 25, 2016
 *      Author: Nate
 */

#ifndef INCLUDE_PROJECTIONCONSTANTS_H_
#define INCLUDE_PROJECTIONCONSTANTS_H_

#include <math.h>
#include <cmath>

#define PI 3.14159265358979323846
#define SQRT2 1.41421356

const double DIMETRIC_ANGLE = 77.0; // degrees
const double SPRITE_UNIT_WIDTH = .10;
const double SPRITE_UNIT_HEIGHT = .10;
const double PERSPECTIVE_DEPTH = SPRITE_UNIT_HEIGHT / (1 + SQRT2*tan(DIMETRIC_ANGLE * 2 * PI / 360));
const double PERSPECTIVE_HEIGHT = SPRITE_UNIT_HEIGHT - PERSPECTIVE_DEPTH;

#endif /* INCLUDE_PROJECTIONCONSTANTS_H_ */
