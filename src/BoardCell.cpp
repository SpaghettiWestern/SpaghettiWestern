#include <BoardCell.h>

BoardCell::BoardCell(Coordinate3D<int> location) : location(location), boardfloor(new BoardFloor(location, true)), actor(NULL) {

	for (int i = 0; i < 4; i++){
		walls[i].reset(new BoardWall((BoardWall::WallEdge)i, location, true));
	}

	neighbors.clear();
	effects.clear();
	objects.clear();
	decorations.clear();
	roomTag = 0;
}

BoardCell::BoardCell(const BoardCell& other){
	deepCopy(other);
}

BoardCell& BoardCell::operator=(const BoardCell& other){
	deepCopy(other);
	return *this;
}

void BoardCell::deepCopy(const BoardCell& other){
	location = other.getLocation();

	boardfloor.reset(new BoardFloor(other.getFloor()));
	actor = other.actor;

	neighbors = other.neighbors;

	for(int i = 0; i < 4; i++){
		walls[i].reset(new BoardWall(other.getWall((BoardWall::WallEdge)i)));
	}

	effects.clear();
	for(unsigned int i = 0; i < other.getNumEffects(); i++){
		effects.push_back(std::unique_ptr<Effect>(new Effect(other.getEffect(i))));
	}

	objects.clear();
	for(unsigned int i = 0; i < other.getNumObjects(); i++){
		objects.push_back(std::unique_ptr<BoardStatic>(new BoardStatic(other.getObject(i))));
	}

	decorations.clear();
	for(unsigned int i = 0; i < other.getNumDecorations(); i++){
		decorations.push_back(std::unique_ptr<BoardDecoration>(new BoardDecoration(other.getDecoration(i))));
	}

	roomTag = other.getRoomTag();
}

bool BoardCell::isTraversable() const{
	return boardfloor->isTraversable();
}

bool BoardCell::actorExists() const{
	return actor.get() != NULL;
}

bool BoardCell::addEffect(std::unique_ptr<Effect>& effect){
	effects.push_back(std::unique_ptr<Effect>());
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

bool BoardCell::setWall(std::unique_ptr<BoardWall>& wall, BoardWall::WallEdge edge){
	walls[edge].swap(wall);
	return true;
}

bool BoardCell::addObject(std::unique_ptr<BoardStatic>& object){
	objects.push_back(std::unique_ptr<BoardStatic>());
	objects.back().swap(object);
	return true;
}

bool BoardCell::addDecoration(std::unique_ptr<BoardDecoration>& decoration){
	decorations.push_back(std::unique_ptr<BoardDecoration>());
	decorations.back().swap(decoration);
	return true;
}

bool BoardCell::removeActor(){
	actor.reset();
	return true;
}

unsigned int BoardCell::getNumNeighbors() const{
	return neighbors.size();
}

unsigned int BoardCell::getNumEffects() const{
	return effects.size();
}

unsigned int BoardCell::getNumObjects() const{
	return objects.size();
}

unsigned int BoardCell::getNumDecorations() const{
	return decorations.size();
}

const BoardActor& BoardCell::getActor() const{
	return *actor;
}

const BoardCell& BoardCell::getNeighbor(int index) const{
	return *neighbors[index];
}

const BoardFloor& BoardCell::getFloor() const{
	return *floor;
}

const BoardWall& BoardCell::getWall(BoardWall::WallEdge edge) const{
	return *(walls[edge]);
}

const Effect& BoardCell::getEffect(int index) const{
	return *effects[index];
}

const BoardStatic& BoardCell::getObject(int index) const{
	return *objects[index];
}

const BoardDecoration& BoardCell::getDecoration(int index) const{
	return *decorations[index];
}

Coordinate3D<int> BoardCell::getLocation() const{
	return location;
}

int BoardCell::getRoomTag() const{
	return roomTag;
}


bool BoardCell::receiveAttack(const Attack& attack){
	return false;
}

std::shared_ptr<BoardActor> BoardCell::getActorPointer(){
	return actor;
}

bool BoardCell::update(){
	if(actor != NULL){
		actor->update();
	}

	if(boardfloor != NULL){
		boardfloor->update();
	}

	for(int i = 0; i < 4; i++){
		if(walls[i] != NULL){
			walls[i]->update();
		}
	}
	for (unsigned int i = 0; i < effects.size(); i++){
		if(effects[i] != NULL){
			effects[i]->update();
		}
	}
	for (unsigned int i = 0; i < objects.size(); i++){
		if(objects[i] != NULL){
			objects[i]->update();
		}
	}
	for (unsigned int i = 0; i < decorations.size(); i++){
		if(decorations[i] != NULL){
			decorations[i]->update();
		}
	}
}









