#include "Player.h"


Player::Player(std::string name, bool is_human) : name(name), human(is_human){
	actors.clear();
}

Player::Player(const Player& other){
	deepCopy(other);
}

Player& Player::operator=(const Player& other){
	deepCopy(other);
	return *this;
}

void Player::deepCopy(const Player& other){
	actors = other.actors;
	name = other.name;
	human = other.human;
}

std::string Player::getName() const{
	return name;
}

bool Player::isHuman() const{
	return human;
}

void Player::createActor(Coordinate3D<int> loc){
	addActor(std::shared_ptr<BoardActor>(new BoardActor(loc, *this)));
}

void Player::createActor(Coordinate3D<int> loc, int hitpoints){
	addActor(std::shared_ptr<BoardActor>(new BoardActor(loc, *this, hitpoints)));
}

void Player::addActor(std::shared_ptr<BoardActor> actor){
	actors.push_back(actor);
}

int Player::getNumActors() const{
	return actors.size();
}

bool Player::actorExists(int index) const{
	return index >= 0 && index < actors.size();
}

const BoardActor& Player::getActor(int index) const{
	return *(actors[index]);
}

bool Player::deleteActor(int index){
	if (actorExists(index)){
		actors.erase(actors.begin()+index);
		return true;
	}
	return false;
}

void Player::update(){

}




