#ifndef SETPIECE_H
#define SETPIECE_H

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

virtual class Setpiece{
	public:
		virtual void render() = 0;
}
#endif