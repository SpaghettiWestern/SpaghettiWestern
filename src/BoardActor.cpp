#include "BoardActor.h"
#include "Player.h"

BoardActor::BoardActor(Coordinate3D<int> loc, Player& owner) :
		BoardPiece(loc, -1), owner(owner){
	move_speed = 5;
	destination = Coordinate3D<int>(-1,-1,-1);
	initAnimations();
}

BoardActor::BoardActor(Coordinate3D<int> loc, Player& owner, int hitpoints) :
		BoardPiece(loc, hitpoints), owner(owner){
	move_speed = 5;
	destination = Coordinate3D<int>(-1,-1,-1);
	initAnimations();
}

BoardActor::~BoardActor(){
	BlitHelper::unloadImageGL(spriteSheet);
}

BoardActor& BoardActor::operator=(const BoardActor& other){
	BoardPiece::operator=((const BoardPiece&) other);
	deepCopy(other);
}

void BoardActor::deepCopy(const BoardActor& other){
	owner = other.owner;

	move_path = other.move_path;
	move_path_index = other.move_path_index;
	destination = other.destination;

	move_speed = other.move_speed;
}

void BoardActor::initAnimations(){
	animations.clear();
	animations.push_back(Animation());
	animations.push_back(Animation());

	animations[0].addFrame(Frame(Coordinate2D<double>(.25,0), Coordinate2D<double>(.5,1), .04)); //idle
	animations[0].addFrame(Frame(Coordinate2D<double>(.75,0), Coordinate2D<double>(1,1), .04)); //idle
	animations[1].addFrame(Frame(Coordinate2D<double>(0,0), Coordinate2D<double>(.25,1), .04)); //moving
	animations[1].addFrame(Frame(Coordinate2D<double>(.5,0), Coordinate2D<double>(.75,1), .04)); //moving

	spriteSheet = BlitHelper::loadImageGL("C:\\Users\\banan\\workspace\\SpaghettiWestern\\Resources\\adude.bmp");

	active_animation = 0;
}

bool BoardActor::isMoving() const{
	return active_animation == 1;
}

void BoardActor::generateMovePath(Coordinate3D<int> start, Coordinate3D<int> end){
	Coordinate2D<double> final_pos = Util::coordToScreen(end);
	Coordinate2D<double> start_pos = Util::coordToScreen(start);
	double x_step = (final_pos.x - start_pos.x)/(float)move_speed;
	double y_step = (final_pos.y - start_pos.y)/(float)move_speed;

	//move_path.push_back(final_pos); Handled in the larger path wrapper
	Coordinate2D<double> next_pos = final_pos;
	for(int i = 0; i < move_speed-1; i++){
		next_pos.x-=x_step;
		next_pos.y-=y_step;
		move_path.push_back(next_pos);
	}
	move_path.push_back(start_pos);
}

void BoardActor::generateMovePath(std::vector<Coordinate3D<int>> path){
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

void BoardActor::startMove(std::vector<Coordinate3D<int>>& path){
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

Coordinate3D<int> BoardActor::getNextStep() const{
	if(!move_path.empty() && isMoving()){
		return Util::screenToCoord(move_path.back());
	}
	return Coordinate3D<int>(-1,-1,-1);
}

const Coordinate3D<int>& BoardActor::getDestination() const{
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













