#include "GameBoard.h"

GameBoard::GameBoard() : pathgen(PathGenerator(board)){
	auto tmp = std::make_shared<GameBoardStructure>(20,20);
	board.swap(tmp);
}

GameBoard::GameBoard(int length, int width) : pathgen(PathGenerator(board)){
	auto tmp = std::make_shared<GameBoardStructure>(length,width);
	board.swap(tmp);
}

GameBoardStructure& GameBoard::getBoard(){
	return *board;
}

bool GameBoard::openSpace(const Coordinate& loc){
	return board->openSpace(loc);
}

bool GameBoard::canAttack(const Coordinate& attacker_loc, const Coordinate& attack_loc){
	if(board->actorExists(attacker_loc) && board->actorExists(attack_loc)){
		BoardActor& attacker = getActor(attacker_loc);
		if(attacker.getType() == ACTIONACTOR){
			return true;
		}
	}
	return false;
}

bool GameBoard::actorExists(const Coordinate& loc){
	return board->actorExists(loc);
}

BoardActor& GameBoard::getActor(const Coordinate& loc){
	return *(board->getActor(loc));
}

bool GameBoard::addActor(std::shared_ptr<BoardActor> new_actor){
	return board->addActor(new_actor);
}

bool GameBoard::moveActor(Coordinate start, Coordinate end){
	if(board->openSpace(end) && board->actorExists(start) && pathgen.findPath(start, end)){
		BoardActor& actor = getActor(start);
		actor.startMove(pathgen.getPath());
		return true;
	}
	return false;
}

bool GameBoard::moveActor(BoardActor& actor, Coordinate goal){
	if(board->openSpace(goal) && pathgen.findPath(actor.getLocation(), goal)){
		actor.startMove(pathgen.getPath());
		return true;
	}
	return false;
}

void GameBoard::update(){
	for (auto it = board->getActors().begin(); it != board->getActors().end(); ++it){
		BoardActor& curr_actor = *(it->second);
		if(curr_actor.isMoving() && !board->openSpace(curr_actor.getNextStep())){
			bool found = pathgen.findPath(curr_actor.getLocation(), curr_actor.getDestination());
			if(found)
				curr_actor.startMove(pathgen.getPath());
			else
				curr_actor.stopMove();
		}
		curr_actor.update();
		if(curr_actor.getLocation() != it->first){
			board->moveActor(it->first, curr_actor.getLocation());
		}
	}

}
