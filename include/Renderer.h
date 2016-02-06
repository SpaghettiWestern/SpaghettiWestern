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
	void render(const GameBoard& gameboard);
	void render(const GameBoardStructure& board);
	void render(const BoardStatic& piece);
	void render(const BoardActor& actor);
	void render(const Effect& effect);

	void drawQuadrangle(const ScreenCoordinate botLeft, const ScreenCoordinate botRight,
			  	  	  	const ScreenCoordinate topLeft, const ScreenCoordinate topRight,
			  	  	  	const std::tuple<float, float, float> color);

	void drawQuadrangle_textured(const ScreenCoordinate botLeft, const ScreenCoordinate botRight,
				  	  	const ScreenCoordinate topLeft, const ScreenCoordinate topRight,
				  	  	SDL_Texture* texture);

	void drawQuadrangle_gltextured(const ScreenCoordinate botLeft, const ScreenCoordinate botRight,
								  const ScreenCoordinate topLeft, const ScreenCoordinate topRight,
								  const GLuint& texture);

};

#endif
