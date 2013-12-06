#include "Rectangular_Setpiece.h"



Rectuangular_Setpiece::Rectuangular_Setpiece(){
	height = 1.0;
	length = 1.0;
	width = 1.0;
}

Rectuangular_Setpiece::Rectuangular_Setpiece(double s_height, double s_width, double s_length){
	height = s_height;
	length = s_length;
	width = s_width;
}

void Rectuangular_Setpiece::render(int x_pos, int y_pos, int z_pos, 
									double x_rot, double y_rot, double z_rot){
	glBegin(GL_QUADS);
		glVertex3d(x_pos+1.0*width, y_pos+1.0*length,z_pos+1.0*height);
		glVertex3d(x_pos+1.0*width, y_pos+1.0*length, z_pos);
		glVertex3d(x_pos, y_pos+1.0*length, z_pos);
		glVertex3d(x_pos, y_pos+1.0*length, z_pos+1.0*height);
		glVertex3d(x_pos+1.0*width, y_pos, z_pos+1.0*height);
		glVertex3d(x_pos+1.0*width, y_pos, z_pos);
		glVertex3d(x_pos, y_pos, z_pos);
		glVertex3d(x_pos, y_pos, z_pos+1.0*height);
	glEnd();
}

Rectuangular_Setpiece::~Rectuangular_Setpiece(){

}

void Rectuangular_Setpiece::setHeight(double new_height){
	height = new_height;
}
void Rectuangular_Setpiece::setWidth(double new_width){
	width = new_width;
}
void Rectuangular_Setpiece::setLength(double new_length){
	length = new_length;
}















