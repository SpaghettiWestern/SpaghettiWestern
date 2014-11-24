#ifndef RENDERER_H
#define RENDERER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "GL/gl.h"

#include <iostream>

#include "Util.h"

#include "GameModel.h"
#include "GameBoard.h"
#include "GameBoardStructure.h"
#include "BoardStatic.h"
#include "BoardActor.h"


class Renderer{
private:
	GameModel& model;

public:

	Renderer(GameModel& model);
	void render();
	void render(GameModel& model);
	void render(GameBoard& gameboard);
	void render(GameBoardStructure& board);
	void render(BoardStatic& piece);
	void render(BoardActor& actor);


	void drawQuadrangle(const ScreenCoordinate botLeft, const ScreenCoordinate botRight,
			  	  	  	const ScreenCoordinate topLeft, const ScreenCoordinate topRight,
			  	  	  	const std::tuple<float, float, float> color);

};

#endif
