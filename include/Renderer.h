#ifndef RENDERER_H
#define RENDERER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "GL/gl.h"

#include <iostream>

#include "Util.h"

#include "GameView.h"
#include "GameModel.h"
#include "GameBoard.h"
#include "GameBoardStructure.h"
#include "BoardStatic.h"
#include "BoardActor.h"

class Renderer{
private:
	const GameModel &model;
	const GameView &view;

public:

	Renderer(const GameModel &model, const GameView &view);
	void render();
	void render(const BoardStatic& piece);
	void render(const BoardActor& actor);
	void render(const Effect& effect);
	void renderBoardDiagonal(const GameBoardStructure& board, Coordinate startCoord, int dx, int dy);
	void renderBoardCoordinate(const GameBoardStructure& board, Coordinate coord);

	void drawQuadrangle(const ScreenCoordinate botLeft, const ScreenCoordinate botRight,
			  	  	  	const ScreenCoordinate topLeft, const ScreenCoordinate topRight,
			  	  	  	const std::tuple<float, float, float> color);

	void drawQuadrangle(const ScreenCoordinate& topLeft, const ScreenCoordinate& botRight,
			const std::tuple<float, float, float> color);

	void drawQuadrangle_textured(const ScreenCoordinate& topLeft, const ScreenCoordinate& botRight,
								  const ScreenCoordinate& tex_topLeft, const ScreenCoordinate& tex_botRight,
								  const GLuint& texture);

};

#endif
