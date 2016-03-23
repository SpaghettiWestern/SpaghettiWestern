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
#include "BoardCell.h"


class Renderer{
private:
	const GameModel &model;
	const GameView &view;

public:
	Renderer(const GameModel &model, const GameView &view);

	void render();
	void render(GameModel& model);
	void render(const GameBoard& gameboard);
	void render(const GameBoardStructure& board);
	void render(const BoardCell& cell);
	void render(const BoardStatic& piece);
	void render(const BoardActor& actor);
	void render(const Effect& effect);
	void renderBoardDiagonal(const GameBoardStructure& board, Coordinate3D<int> startCoord, int dx, int dy);
	void renderBoardCoordinate(const GameBoardStructure& board, Coordinate3D<int> coord);

	void drawQuadrangle(const Coordinate2D<double> botLeft, const Coordinate2D<double> botRight,
			  	  	  	const Coordinate2D<double> topLeft, const Coordinate2D<double> topRight,
			  	  	  	const std::tuple<float, float, float> color);

	void drawQuadrangle(const Coordinate2D<double>& topLeft, const Coordinate2D<double>& botRight,
			const std::tuple<float, float, float> color);

	void drawQuadrangle_textured(const Coordinate2D<double>& topLeft, const Coordinate2D<double>& botRight,
								  const Coordinate2D<double>& tex_topLeft, const Coordinate2D<double>& tex_botRight,
								  const GLuint& texture);

};

#endif
