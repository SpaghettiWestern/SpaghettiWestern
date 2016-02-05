#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "Renderer.h"
#include "GameModel.h"

class GameView{
private:
	GameModel& model;
	Renderer renderer;


public:
	GameView(GameModel& model);
	void render();

};


#endif
