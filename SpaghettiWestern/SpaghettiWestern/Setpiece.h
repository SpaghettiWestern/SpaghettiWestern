#ifndef SETPIECE_H
#define SETPIECE_H

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

virtual class Setpiece{
	public:
		virtual void render(int x_pos, int y_pos, int z_pos, 
			double x_rot, double y_rot, double z_rot) = 0;
}
#endif