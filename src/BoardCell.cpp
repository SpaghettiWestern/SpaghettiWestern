#include <BoardCell.h>

BoardCell::BoardCell(Coordinate3D<int> location) : location(location){
	roomTag = 0;
}


bool BoardCell::isTraversable() const{
	return floor->isTraversable();
}

bool BoardCell::actorExists() const{
	return actor.get() != NULL;
}

bool BoardCell::addEffect(std::unique_ptr<Effect>& effect){
	effects.push_back(std::unique_ptr<Effect>(NULL));
	effects.back().swap(effect);
	return true;
}

bool BoardCell::setActor(std::shared_ptr<BoardActor>& actor){
	this->actor = actor;
	return true;
}

bool BoardCell::setFloor(std::unique_ptr<BoardFloor>& floor){
	floor.swap(floor);
	return true;
}

bool BoardCell::setWall(std::unique_ptr<BoardWall>& wall, WallEdge edge){
	walls[edge].swap(wall);
	return true;
}

bool BoardCell::addObject(std::unique_ptr<BoardStatic>& object){
	objects.push_back(std::unique_ptr<BoardStatic>(NULL));
	objects.back().swap(object);
	return true;
}

bool BoardCell::addDecoration(std::unique_ptr<BoardDecoration>& decoration){
	decorations.push_back(std::unique_ptr<BoardDecoration>(NULL));
	decorations.back().swap(decoration);
	return true;
}

bool BoardCell::removeActor(){
	actor.reset();
	return true;
}

std::shared_ptr<BoardActor>& BoardCell::getActor(){
	return actor;
}


bool BoardCell::update(){
	actor->update();
	floor->update();
	for(int i = 0; i < 4; i++){
		walls[i]->update();
	}
	for (unsigned int i = 0; i < effects.size(); i++){
		effects[i]->update();
	}
	for (unsigned int i = 0; i < objects.size(); i++){
		objects[i]->update();
	}
	for (unsigned int i = 0; i < decorations.size(); i++){
		decorations[i]->update();
	}
}









