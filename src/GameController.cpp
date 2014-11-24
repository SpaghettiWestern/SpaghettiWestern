#include "GameController.h"

GameController::GameController(GameModel& model) : model(model){
	selected.reset();
}

bool GameController::handleInput(SDL_Event& event){
	//std::cout << "Type:" << event.type << "\n";
	if(event.type == SDL_QUIT){
		std::cout << "Quit";
		return false;
	}

	if(event.type == SDL_MOUSEBUTTONUP){
		handleClick(event);
	}

	if(event.type == SDL_KEYUP){
		std::cout << "Key:" << event.key.keysym.sym << "\n";
	}

	return true;

}

ScreenCoordinate GameController::inputToScreen(int x, int y){
	return ScreenCoordinate((float)x/800.0, (float)y/600.0);
}

bool GameController::handleClick(SDL_Event& click){
	std::cout << "X :" << click.button.x << "  Y :" << click.button.y << "\n";
	ScreenCoordinate s = inputToScreen(click.button.x, click.button.y);
	std::cout << "Xs:" << s.first << "  Ys:" << s.second << "\n";
	Coordinate c = Util::screenToCoord(s);
	std::cout << "Xc:" << c.first << "  Yc:" << c.second << "\n";
	if((int)click.button.button == SDL_BUTTON_LEFT){
		return handleLClick(s);
	}
	if((int)click.button.button == SDL_BUTTON_RIGHT){
		return handleRClick(s);
	}
	return false;
}

bool GameController::handleLClick(ScreenCoordinate loc){
	GameBoardStructure& board = model.getGameBoard().getBoard();
	Coordinate boardloc = Util::screenToCoord(loc);
	std::cout << "Left Click\n";
	if (board.actorExists(boardloc)){
		selected = board.getActor(boardloc);
		std::cout << "selected actor\n";
		std::cout << "curr_hp: " << selected->getCurrentHealth() << "\n";
		return true;
	}
	selected.reset();
	return false;
}

bool GameController::handleRClick(ScreenCoordinate loc){
	std::cout << "Right Click\n";
	GameBoard& board = model.getGameBoard();
	Coordinate boardloc = Util::screenToCoord(loc);
	if (selected && board.openSpace(boardloc)){
		std::cout << "moving actor\n";
		return board.moveActor(*selected, boardloc);
	}
	if (selected && board.actorExists(boardloc)){
		std::cout << "attacking..." << "\n";
		model.sendAttack(selected->getLocation(), boardloc);
		return true;
	}
	return false;
}
