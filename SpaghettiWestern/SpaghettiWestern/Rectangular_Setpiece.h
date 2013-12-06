#ifndef RECTANGULAR_SETPIECE_H
#define RECTANGULAR_SETPIECE_H

#include "Setpiece.h"

class Rectuangular_Setpiece: Setpiece{
	public:
		Rectuangular_Setpiece();
		Rectuangular_Setpiece(double s_height, double s_width, double s_length);

		virtual void render(int x_pos, int y_pos, int z_pos, 
			double x_rot, double y_rot, double z_rot);

		void setHeight(double new_height);
		void setWidth(double new_width);
		void setLength(double new_length);

		

	private:
		double height;
		double width;
		double length;

		~Rectuangular_Setpiece();
		

}
#endif