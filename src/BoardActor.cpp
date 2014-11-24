#include "BoardActor.h"

BoardActor::BoardActor(Coordinate loc, Player& owner) : BoardPiece(loc), owner(owner){
	max_hitpoints = -1;
	curr_hitpoints = -1;
	move_speed = 5;
	destination = Coordinate(-1,-1);
	initAnimations();
}

BoardActor::BoardActor(Coordinate loc, Player& owner, int hitpoints) :
		BoardPiece(loc), owner(owner), max_hitpoints(hitpoints), curr_hitpoints(hitpoints){
	move_speed = 5;
	destination = Coordinate(-1,-1);
	initAnimations();
}

void BoardActor::initAnimations(){
	animations.clear();
	animations.push_back(Animation());
	animations.push_back(Animation());
	animations[0].addFrame(Frame(std::make_tuple(255,0,0), .05)); //idle
	animations[0].addFrame(Frame(std::make_tuple(0,0,0), .05));
	animations[1].addFrame(Frame(std::make_tuple(0,255,0), .05)); //moving
	animations[1].addFrame(Frame(std::make_tuple(0,0,0), .05));

	active_animation = 0;
}

bool BoardActor::isMoving(){
	return active_animation == 1;
}

void BoardActor::generateMovePath(Coordinate start, Coordinate end){
	ScreenCoordinate final_pos = Util::coordToScreen(end);
	ScreenCoordinate start_pos = Util::coordToScreen(start);
	float x_step = (final_pos.first - screen_location.first)/(float)move_speed;
	float y_step = (final_pos.second - screen_location.second)/(float)move_speed;

	//move_path.push_back(final_pos); Handled in the larger path wrapper
	for(int i = 0; i < move_speed-1; i++){
		ScreenCoordinate next_pos = move_path[i];
		next_pos.first-=x_step;
		next_pos.second-=y_step;
		move_path.push_back(next_pos);
	}
	move_path.push_back(start_pos);
}

void BoardActor::generateMovePath(std::vector<Coordinate> path){
	move_path.clear();
	if(path.size() > 1){
		destination = path[0];
		move_path.push_back(Util::coordToScreen(destination));
	}

	for(int i = 0; i < ((int)path.size())-1; i++){
		generateMovePath(path[i+1], path[i]);
	}
	moveStep();
}

void BoardActor::recieveAttack(Attack& attack){
	recieveDamage(attack.getDamage());
}

int BoardActor::getCurrentHealth(){
	return curr_hitpoints;
}
int BoardActor::getMaxHealth(){
	return max_hitpoints;
}

void BoardActor::recieveDamage(int damage){
	// negative health is signaling invincibility right now
	if (curr_hitpoints < 0 ){
		return;
	}
	curr_hitpoints = curr_hitpoints - damage;
	if(curr_hitpoints <= 0){
		curr_hitpoints = 0;
		return;
	}
	if(curr_hitpoints > max_hitpoints){
		curr_hitpoints = max_hitpoints;
	}
}

bool BoardActor::isAlive(){
	return !(curr_hitpoints == 0);
}

void BoardActor::setAnimation_Moving(){
	if(active_animation != 1){
		active_animation = 1;
		resetAnimation();
	}

}
void BoardActor::setAnimation_Idle(){
	if(active_animation != 0){
		active_animation = 0;
		resetAnimation();
	}
}

Frame& BoardActor::getCurrentAnimationFrame(){
	return animations[active_animation].getCurrFrame();
}

void BoardActor::updateAnimation(){
	animations[active_animation].update();
}

void BoardActor::resetAnimation(){
	animations[active_animation].reset();
}

void BoardActor::startMove(std::vector<Coordinate> path){
	setAnimation_Moving();	//start moving
	generateMovePath(path);
}

void BoardActor::stopMove(){
	setAnimation_Idle();
	setLocation(location); //resets the screen coordinates, not just the Coordinate
}

void BoardActor::moveStep(){
	if(isMoving()){
		if(move_path.empty()){
			stopMove();
			return;
		}
		screen_location = move_path.back();
		move_path.pop_back();
		location = Util::screenToCoord(screen_location);
	}
}

Coordinate BoardActor::getNextStep(){
	if(!move_path.empty() && isMoving()){
		return Util::screenToCoord(move_path.back());
	}
	return Coordinate(-1,-1);
}

Coordinate BoardActor::getDestination(){
	return destination;
}

int BoardActor::getMoveSpeed(){
	return move_speed;
}


void BoardActor::update(){
	updateAnimation();
	moveStep();
}

Player& BoardActor::getOwner(){
	return owner;
}

actor_type BoardActor::getType(){
	return BOARDACTOR;
}













