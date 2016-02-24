#include "GameBoardStructure.h"

GameBoardStructure::GameBoardStructure(int length, int width){
	if(length < 0 || width < 0){
		length = 0;
		width = 0;
	}
	this->length = length;
	this->width = width;
	this->height = 1;
	initEnvironment();
	initActors();
}

void GameBoardStructure::initEnvironment(){
	environmentCells.clear();
	for(int x = 0; x < width; x++){
		for(int y = 0; y < length; y++){
			groundTexture[Coordinate(x,y)] = 0;
			for(int z = 0; z < height; z++){
				environmentCells[BoardCoordinate(x,y,z)] = std::unique_ptr<BoardCell>(new BoardCell);
			}
		}
	}
}

GameBoardStructure::GameBoardStructure(const GameBoardStructure& other){
	*this = other;
}

GameBoardStructure& GameBoardStructure::operator=(const GameBoardStructure& other){
	if(this != &other){
		environmentCells.clear();
		groundTexture.clear();
		effects.clear();

		length = other.getLength();
		width = other.getWidth();
		height = other.getHeight();

		for(int x = 0; x < width; x++){
			for(int y = 0; y < length; y++){
				groundTexture[Coordinate(x,y)] = other.getGroundTexture(Coordinate(x,y));
				for(int z = 0; z < height; z++){
					BoardCoordinate loc(x,y,z);
					environmentCells[loc] = std::unique_ptr<BoardCell>(new BoardCell(other.getEnvironmentCell(loc)));
				}
			}
		}

		for(auto it = other.getEffects().begin(); it != other.getEffects().end(); ++it){
			effects[it->first] = std::vector<std::unique_ptr<Effect>>();
			for(auto it_vec = it->second.begin(); it_vec != it->second.end(); ++it_vec){
				effects[it->first].push_back(std::unique_ptr<Effect>(new Effect(**it_vec)));
			}
		}
	}
	return *this;
}

const BoardCell& GameBoardStructure::getEnvironmentCell(int x, int y, int z) const{
	return *(environmentCells[BoardCoordinate(x,y,z)]);
}

const BoardCell& GameBoardStructure::getEnvironmentCell(const BoardCoordinate& loc) const{
	return *(environmentCells[loc]);
}

GLuint GameBoardStructure::getGroundTexture(int x, int y) const{
	return groundTexture[Coordinate(x,y)];
}

GLuint GameBoardStructure::getGroundTexture(const Coordinate& loc) const{
	return groundTexture[loc];
}

bool GameBoardStructure::addEnvironmentPiece(std::unique_ptr<BoardStatic>& newpiece){
	if (newpiece.get() == NULL){
		return false;
	}

	BoardCoordinate loc = newpiece->getLocation();
	if (inBounds(loc)){
		std::unique_ptr<BoardStatic>& curr_ptr = this->environment.find(loc)->second;
		curr_ptr.swap(newpiece);
		return true;
	}
	return false;
}

bool GameBoardStructure::addBoardEffect(std::unique_ptr<Effect>& effect){
	const BoardCoordinate& loc = Util::screenToCoord(effect->getScreenLocation());

	if(inBounds(loc)){
		environmentCells[loc]->addEffect(effect);
		return true;
	}
	return false;
}
bool GameBoardStructure::addActor(std::shared_ptr<BoardActor>& actor){
	const BoardCoordinate& actorloc = actor->getLocation();
	if(openSpace(actorloc)){
		environmentCells[actorloc]->addActor(actor);
		return true;
	}
	return false;
}
bool GameBoardStructure::addFloor(std::unique_ptr<BoardFloor>& floor){
	const BoardCoordinate& loc = floor->getLocation();

	if(inBounds(loc)){
		environmentCells[loc]->addFloor(floor);
		return true;
	}
	return false;
}
bool GameBoardStructure::addWall(std::unique_ptr<BoardWall>& wall){
	const BoardCoordinate& loc = wall->getLocation();

	if(inBounds(loc)){
		environmentCells[loc]->addWall(wall);
		return true;
	}
	return false;
}
bool GameBoardStructure::addObject(std::unique_ptr<BoardStatic>& object){
	const BoardCoordinate& loc = object->getLocation();

	if(inBounds(loc)){
		environmentCells[loc]->addObject(object);
		return true;
	}
	return false;
}
bool GameBoardStructure::addDecoration(std::unique_ptr<BoardDecoration>& decoration){
	const BoardCoordinate& loc = decoration->getLocation();

	if(inBounds(loc)){
		environmentCells[loc]->addDecoration(decoration);
		return true;
	}
	return false;
}

bool GameBoardStructure::openSpace(const BoardCoordinate& loc) const{
	return (inBounds(loc) && !actorExists(loc) && traversableSpace(loc));
}

bool GameBoardStructure::traversableSpace(const BoardCoordinate& loc) const{
	return environmentCells[loc]->isTraversable();
}

bool GameBoardStructure::inBounds(const BoardCoordinate& loc) const{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < length && loc.z >= 0 && loc.z > height;
}

bool GameBoardStructure::actorExists(int x, int y, int z) const{
	return environmentCells[BoardCoordinate(x,y,z)]->actorExists();
}
bool GameBoardStructure::actorExists(const BoardCoordinate& loc) const{
	return environmentCells[loc]->actorExists();
}

const std::vector<std::shared_ptr<BoardActor>>& GameBoardStructure::getActors(const BoardCoordinate& loc) const{
	return environmentCells[loc]->getActors();
}

const std::shared_ptr<BoardActor>& GameBoardStructure::getActor(int x, int y, int z) const{
	return getActor(BoardCoordinate(x,y,z));
}
const std::shared_ptr<BoardActor>& GameBoardStructure::getActor(const BoardCoordinate& loc) const{
	return environmentCells[loc]->getActor(0);
}

bool GameBoardStructure::removeActor(const BoardCoordinate& loc){
	if (actorExists(loc)){
		environmentCells[loc]->removeActor(0);
		return true;
	}
	return false;
}

bool GameBoardStructure::moveActor(const BoardCoordinate& curr_loc, const BoardCoordinate& new_loc){
	if(openSpace(new_loc) && actorExists(curr_loc)){
		std::shared_ptr<BoardActor> actor = environmentCells[curr_loc]->getActor(0);
		environmentCells[new_loc]->addActor(actor);
		environmentCells[curr_loc]->removeActor(0);
		return true;
	}
	return false;
}


bool GameBoardStructure::effectsExist(const BoardCoordinate& loc) const{
	return (effects.count(loc) > 0);
}

int GameBoardStructure::numEffects(const BoardCoordinate& loc) const{
	if(effectsExist(loc)){
		return effects.find(loc)->second.size();
	}
	return 0;
}

const std::map<BoardCoordinate, std::vector<std::unique_ptr<Effect>>>& GameBoardStructure::getEffects() const{
	return effects;
}


const std::vector<std::unique_ptr<Effect>>& GameBoardStructure::getEffects(const BoardCoordinate& loc) const{
	return effects.find(loc)->second;
}

const Effect& GameBoardStructure::getEffect(const BoardCoordinate& loc) const{
	return *(effects.find(loc)->second.back());
}

bool GameBoardStructure::addSurfaceEffect(std::unique_ptr<Effect>& new_effect){
	BoardCoordinate loc = Util::screenToCoord(new_effect->getScreenLocation());
	if(!inBounds(loc)){
		return false;
	}
	effects[loc].push_back(std::unique_ptr<Effect>(new_effect.release()));
	return true;
}

int GameBoardStructure::getLength() const{
	return length;
}


int GameBoardStructure::getWidth() const{
	return width;
}

int GameBoardStructure::getHeight() const{

}

bool GameBoardStructure::handleEffect(const std::unique_ptr<Effect>& effect, const BoardCoordinate& loc){
	if(!inBounds(loc))
		return true;

	switch (effect->getType()){
	case ATTACKEFFECT:
	{
		AttackEffect& attack_effect = (AttackEffect&)(*effect);
		if(actorExists(loc)){
			return getActor(loc)->recieveAttack(attack_effect.getAttack());
		}
		BoardCell& setpiece = *(this->environmentCells.find(loc)->second);
		if(setpiece.getType() == STATICCOVER){
			return setpiece.recieveAttack(attack_effect.getAttack());
		}
	}
		break;
	default:
		return false;
		break;
	}
	return false;
}

void GameBoardStructure::updateEffects_base(){
	for (auto map_it = effects.begin(); map_it != effects.end(); ++map_it){
		for(auto vec_it = map_it->second.begin(); vec_it < map_it->second.end(); ++vec_it){
			if(!(*vec_it)->update()){
				vec_it = map_it->second.erase(vec_it);
			}
		}
	}
}

void GameBoardStructure::updateEffects_reposition(){
	std::vector<Coordinate> empty_cells;
	for (auto map_it = effects.begin(); map_it != effects.end(); ++map_it){
		Coordinate board_loc = map_it->first;
		for(auto vec_it = map_it->second.begin(); vec_it < map_it->second.end(); ++vec_it){
			Coordinate effect_loc = Util::screenToCoord((*vec_it)->getScreenLocation());
			if(effect_loc != board_loc){
				if(!handleEffect(*vec_it, effect_loc)){
					addEffect(*vec_it);
				}
				vec_it = map_it->second.erase(vec_it);
			}
		}
		if(map_it->second.empty()){
			empty_cells.push_back(board_loc);
		}
	}

	for(unsigned int i = 0; i < empty_cells.size(); i++)
		effects.erase(effects.find(empty_cells[i]));
}

void GameBoardStructure::updateEffects(){
	updateEffects_base();
	updateEffects_reposition();
}


void GameBoardStructure::updateEnvironment(){
	for(int x = 0; x < width; x++){
		for(int y = 0; y < length; y++){
			environment[Coordinate(x,y)]->update();
		}
	}
}

void GameBoardStructure::update(){
	updateEffects();
	updateEnvironment();
}


