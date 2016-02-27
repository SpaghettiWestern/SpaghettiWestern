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
#include "GameView.h"
#include "GameBoardStructure.h"

class GameController{
private:
	GameModel &model;
	GameView &view;
	ScreenCoordinate inputToScreen(int x, int y);
	std::shared_ptr<BoardActor> selected;

	const double SCROLL_SPEED_HORIZ = 0.1;
	const double SCROLL_SPEED_VERT = 0.2;
	const double ZOOM_SPEED = 0.1;

	std::map<SDL_Keycode, bool> keyDownMap;

	bool handleClick(SDL_Event& click);
	bool handleRClick(ScreenCoordinate loc);
	bool handleLClick(ScreenCoordinate loc);

	void handleKeyUp(SDL_Event &keyUpEvent);
	void handleKeyDown(SDL_Event &keyDownEvent);

public:
	GameController(GameModel &model, GameView &view);
	bool handleInput(SDL_Event& event);

	void processDownKeys();

};

#endif
