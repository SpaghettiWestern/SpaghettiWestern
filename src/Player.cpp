#include "Player.h"


Player::Player(std::string name, bool is_human) : name(name), human(is_human){
	actors.clear();
}

std::string Player::getName(){
	return name;
}

bool Player::isHuman(){
	return human;
}

void Player::createActor(Coordinate loc){
	addActor(std::shared_ptr<BoardActor>(new BoardActor(loc, *this)));
}

void Player::createActor(Coordinate loc, int hitpoints){
	addActor(std::shared_ptr<BoardActor>(new BoardActor(loc, *this, hitpoints)));
}

void Player::addActor(std::shared_ptr<BoardActor> actor){
	actors.push_back(actor);
}

int Player::getNumActors(){
	return actors.size();
}

bool Player::actorExists(int index){
	return index >= 0 && index < actors.size();
}

BoardActor& Player::getActor(int index){
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




