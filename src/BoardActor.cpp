#include "BoardActor.h"

BoardActor::BoardActor(Coordinate loc, Player& owner) :
		BoardPiece(loc, -1), owner(owner){
	move_speed = 5;
	destination = Coordinate(-1,-1);
	initAnimations();
}

BoardActor::BoardActor(Coordinate loc, Player& owner, int hitpoints) :
		BoardPiece(loc, hitpoints), owner(owner){
	move_speed = 5;
	destination = Coordinate(-1,-1);
	initAnimations();
}

BoardActor::~BoardActor(){
	BlitHelper::unloadImageGL(spriteSheet);
}

void BoardActor::initAnimations(){
	animations.clear();
	animations.push_back(Animation());
	animations.push_back(Animation());

	animations[0].addFrame(Frame(ScreenCoordinate(.25,0), ScreenCoordinate(.5,1), .04)); //idle
	animations[0].addFrame(Frame(ScreenCoordinate(.75,0), ScreenCoordinate(1,1), .04)); //idle
	animations[1].addFrame(Frame(ScreenCoordinate(0,0), ScreenCoordinate(.25,1), .04)); //moving
	animations[1].addFrame(Frame(ScreenCoordinate(.5,0), ScreenCoordinate(.75,1), .04)); //moving

	spriteSheet = BlitHelper::loadImageGL("C:\\Users\\banan\\workspace\\SpaghettiWestern\\Resources\\adude.bmp");

	active_animation = 0;
}

bool BoardActor::isMoving() const{
	return active_animation == 1;
}

void BoardActor::generateMovePath(Coordinate start, Coordinate end){
	ScreenCoordinate final_pos = Util::coordToScreen(end);
	ScreenCoordinate start_pos = Util::coordToScreen(start);
	double x_step = (final_pos.first - start_pos.first)/(float)move_speed;
	double y_step = (final_pos.second - start_pos.second)/(float)move_speed;

	//move_path.push_back(final_pos); Handled in the larger path wrapper
	ScreenCoordinate next_pos = final_pos;
	for(int i = 0; i < move_speed-1; i++){
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

bool BoardActor::isAlive() const{
	return !(curr_hitpoints == 0);
}

void BoardActor::setAnimation_Moving(){
	if(active_animation != 1){
		active_animation = 1;
		BoardPiece::resetAnimation();
	}
}

void BoardActor::setAnimation_Idle(){
	if(active_animation != 0){
		active_animation = 0;
		BoardPiece::resetAnimation();
	}
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
		location = Util::screenToCoord(screen_location);
		move_path.pop_back();
	}
}

Coordinate BoardActor::getNextStep() const{
	if(!move_path.empty() && isMoving()){
		return Util::screenToCoord(move_path.back());
	}
	return Coordinate(-1,-1);
}

const Coordinate& BoardActor::getDestination() const{
	return destination;
}

int BoardActor::getMoveSpeed() const{
	return move_speed;
}

bool BoardActor::update(){
	BoardPiece::update();
	moveStep();
	return true;
}

const Player& BoardActor::getOwner() const{
	return owner;
}

actor_type BoardActor::getType() const{
	return BOARDACTOR;
}













