#include "GameBoardStructure.h"

GameBoardStructure::GameBoardStructure(int length, int width){
	if(length < 0 || width < 0){
		length = 0;
		width = 0;
	}
	this->length = length;
	this->width = width;
	initEnvironment();
	initActors();
}

void GameBoardStructure::initEnvironment(){
	environment.clear();
	for(int i = 0; i < width; i++){
		for(int j = 0; j < length; j++){
			environment[Coordinate(i,j)] = std::unique_ptr<BoardStatic>(new BoardStatic(Coordinate(i,j), true));
		}
	}
}

void GameBoardStructure::initActors(){
	actors.clear();
}

bool GameBoardStructure::addActor(std::shared_ptr<BoardActor> actor){
	Coordinate actorloc = actor->getLocation();
	if(!actorExists(actorloc)){
		actors[actorloc] = actor;
		return true;
	}
	return false;
}

BoardStatic& GameBoardStructure::getEnvironmentPiece(int x, int y){
	return getEnvironmentPiece(Coordinate(x,y));
}
BoardStatic& GameBoardStructure::getEnvironmentPiece(const Coordinate& loc){
	return *(this->environment.find(loc)->second);
}


bool GameBoardStructure::openSpace(const Coordinate& loc){
	return (inBounds(loc) && !actorExists(loc));
}

bool GameBoardStructure::inBounds(const Coordinate& loc){
	return loc.first >= 0 && loc.first < width && loc.second >= 0 && loc.second < length;
}

bool GameBoardStructure::actorExists(int x, int y){
	return actorExists(Coordinate(x,y));
}
bool GameBoardStructure::actorExists(const Coordinate& loc){
	if (actors.count(loc) > 0){
		return true;
	}
	return false;
}

std::map<Coordinate, std::shared_ptr<BoardActor>>& GameBoardStructure::getActors(){
	return actors;
}

std::shared_ptr<BoardActor> GameBoardStructure::getActor(int x, int y){
	return getActor(Coordinate(x,y));
}
std::shared_ptr<BoardActor> GameBoardStructure::getActor(const Coordinate& loc){
	return (this->actors.find(loc)->second);
}

bool GameBoardStructure::removeActor(const Coordinate& loc){
	if (actorExists(loc)){
		actors.erase(loc);
		return true;
	}
	return false;
}

bool GameBoardStructure::moveActor(const Coordinate& curr_loc, const Coordinate& new_loc){
	if(openSpace(new_loc) && actorExists(curr_loc)){
		actors[new_loc] = actors[curr_loc];
		getActor(new_loc)->setLocation(new_loc);
		removeActor(curr_loc);
		return true;
	}
	return false;
}


int GameBoardStructure::getLength(){
	return length;
}
int GameBoardStructure::getWidth(){
	return width;
}
