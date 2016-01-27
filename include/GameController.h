#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
//#include <SDL2/SDL_ttf.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <memory>

#include "Util.h"
#include "GameModel.h"
#include "GameBoardStructure.h"

class GameController{
private:
	GameModel& model;
	ScreenCoordinate inputToScreen(int x, int y);
	std::shared_ptr<BoardActor> selected;

	bool handleClick(SDL_Event& click);
	bool handleRClick(ScreenCoordinate loc);
	bool handleLClick(ScreenCoordinate loc);

public:
	GameController(GameModel& model);
	bool handleInput(SDL_Event& event);

};

#endif
