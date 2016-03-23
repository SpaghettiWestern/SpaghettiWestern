#include "GameBoard.h"

GameBoard::GameBoard() : pathgen(PathGenerator(board)){
	auto tmp = std::make_shared<GameBoardStructure>(20,20,20);
	board.swap(tmp);
}

GameBoard::GameBoard(int length, int width, int height) : pathgen(PathGenerator(board)){
	auto tmp = std::make_shared<GameBoardStructure>(length,width, height);
	board.swap(tmp);
}

GameBoard::GameBoard(const GameBoard& other_board) : pathgen(PathGenerator(board)){
	*this = other_board;
}

GameBoard& GameBoard::operator=(const GameBoard& other){
	if(this != &other){
		auto tmp = std::make_shared<GameBoardStructure>(other.getBoard());
		board.swap(tmp);

		surface_effects.clear();
		const std::vector<std::unique_ptr<Effect>>& other_effects = other.getSurfaceEffects();
		for(auto it = other_effects.begin(); it != other_effects.end(); ++it){
			surface_effects.push_back(std::unique_ptr<Effect>(new Effect(**it)));
		}
	}
	return *this;
}

const GameBoardStructure& GameBoard::getBoard() const{
	return *board;
}

bool GameBoard::openSpace(const Coordinate3D<int>& loc){
	return board->openSpace(loc);
}

bool GameBoard::canAttack(const Coordinate3D<int>& attacker_loc, const Coordinate3D<int>& attack_loc){
	if(board->actorExists(attacker_loc) && board->actorExists(attack_loc)){
		const BoardActor& attacker = getActor(attacker_loc);
		if(attacker.getType() == ACTIONACTOR){
			return true;
		}
	}
	return false;
}

bool GameBoard::actorExists(const Coordinate3D<int>& loc){
	return board->actorExists(loc);
}

const BoardActor& GameBoard::getActor(const Coordinate3D<int>& loc) const{
	return (board->getActor(loc));
}

std::shared_ptr<BoardActor> GameBoard::getActorPointer(const Coordinate3D<int>& loc){
	return board->getBoardActorPointer(loc);
}

bool GameBoard::addActor(std::shared_ptr<BoardActor> new_actor){
	return board->addActor(new_actor);
}


bool GameBoard::addStaticCoverPiece(Coordinate3D<int> loc, bool traversable, int hitpoints, int deflection_chance){
	std::unique_ptr<BoardStatic> coverpiece = std::unique_ptr<BoardStatic>(new StaticCover(loc, traversable, hitpoints, deflection_chance));
	return board->addEnvironmentPiece(coverpiece);
}


bool GameBoard::removeActor(const Coordinate3D<int>& loc){
	return board->removeActor(loc);
}

bool GameBoard::moveActor(Coordinate3D<int> start, Coordinate3D<int> end){
	if(board->openSpace(end) && board->actorExists(start) && pathgen.findPath(start, end)){
		std::shared_ptr<BoardActor> actor = getActorPointer(start);
		std::vector<Coordinate3D<int>> thePath = pathgen.getPath();
		actor->startMove(thePath);
		return true;
	}
	return false;
}

bool GameBoard::moveActor(BoardActor& actor, Coordinate3D<int> goal){
	if(board->openSpace(goal) && pathgen.findPath(actor.getLocation(), goal)){
		std::vector<Coordinate3D<int>> thePath = pathgen.getPath();
		actor.startMove(thePath);
		return true;
	}
	return false;
}

const std::map<Coordinate3D<int>, std::vector<std::unique_ptr<Effect>>>& GameBoard::getBoardEffects() const{
	return board->getEffects();
}


bool GameBoard::addBoardEffect(const Coordinate2D<double>& loc){
	std::unique_ptr<Effect> new_effect(new Effect(loc));
	board->addBoardEffect(new_effect);
	return true;
}

bool GameBoard::addBoardEffect(const Coordinate2D<double>& loc, const Animation& animation){
	std::unique_ptr<Effect> new_effect(new Effect(loc, animation));
	board->addBoardEffect(new_effect);
	return true;
}

bool GameBoard::addBoardEffect(std::unique_ptr<Effect>& new_effect){
	board->addBoardEffect(new_effect);
	return true;
}

bool GameBoard::addMovingBoardEffect(const Coordinate2D<double>& loc, const std::vector<Coordinate2D<double>>& path){
	surface_effects.push_back(std::unique_ptr<Effect>(new MovingEffect(loc, path)));
	return true;
}

const std::vector<std::unique_ptr<Effect>>& GameBoard::getSurfaceEffects() const{
	return surface_effects;
}

bool GameBoard::addSurfaceEffect(const Coordinate2D<double>& loc){
	surface_effects.push_back(std::unique_ptr<Effect>(new Effect(loc)));
	return true;
}

bool GameBoard::addSurfaceEffect(const Coordinate2D<double>& loc, const Animation& animation){
	surface_effects.push_back(std::unique_ptr<Effect>(new Effect(loc,animation)));
	return true;
}

bool GameBoard::addSurfaceEffect(std::unique_ptr<Effect>& new_effect){
	surface_effects.push_back(std::unique_ptr<Effect>(new_effect.release()));
	return true;
}

bool GameBoard::addMovingSurfaceEffect(const Coordinate2D<double>& loc, const std::vector<Coordinate2D<double>>& path){
	surface_effects.push_back(std::unique_ptr<Effect>(new MovingEffect(loc, path)));
	return true;
}

void GameBoard::updateActor(BoardActor& curr_actor, const Coordinate3D<int>& curr_location){
	Coordinate3D<int> next_loc = curr_actor.getNextStep();
	if(curr_actor.isMoving() && next_loc != curr_actor.getLocation() && !board->openSpace(next_loc)){
		bool found = pathgen.findPath(curr_actor.getLocation(), curr_actor.getDestination());
		if(found){
			std::vector<Coordinate3D<int>> thePath = pathgen.getPath();
			curr_actor.startMove(thePath);
		}
		else{
			curr_actor.stopMove();
		}
	}
	curr_actor.update();
	if(curr_actor.getLocation() != curr_location){
		board->moveActor(curr_location, curr_actor.getLocation());
	}
}

void GameBoard::updateActors(){
	for (auto it = board->getCells().begin(); it != board->getCells().end(); ++it){
		if(board->actorExists(it->first)){
			updateActor(*(it->second->getActorPointer()), it->first);
		}
	}
}

void GameBoard::updateEffects(){
	for(auto it = surface_effects.begin(); it < surface_effects.end(); ++it){
		if(!(*it)->update()){
			it = surface_effects.erase(it);
		}
	}
}

void GameBoard::updateBoard(){
	//updateActors();
	board->update();
}

void GameBoard::update(){
	updateBoard();
	updateEffects();
}
