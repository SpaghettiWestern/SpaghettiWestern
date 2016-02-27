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
			groundTexture[Coordinate2D<int>(x,y)] = 0;
			for(int z = 0; z < height; z++){
				environmentCells[Coordinate3D<int>(x,y,z)] = std::unique_ptr<BoardCell>(new BoardCell(Coordinate3D<int>(x,y,z)));
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
				groundTexture[Coordinate2D<int>(x,y)] = other.getGroundTexture(Coordinate2D<int>(x,y));
				for(int z = 0; z < height; z++){
					Coordinate3D<int> loc(x,y,z);
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
	return *(environmentCells[Coordinate3D<int>(x,y,z)]);
}

const BoardCell& GameBoardStructure::getEnvironmentCell(const Coordinate3D<int>& loc) const{
	return *(environmentCells[loc]);
}

GLuint GameBoardStructure::getGroundTexture(int x, int y) const{
	return groundTexture[Coordinate2D<int>(x,y)];
}

GLuint GameBoardStructure::getGroundTexture(const Coordinate2D<int>& loc) const{
	return groundTexture[loc];
}

bool GameBoardStructure::addEnvironmentPiece(std::unique_ptr<BoardStatic>& newpiece){
	if (newpiece.get() == NULL){
		return false;
	}

	Coordinate3D<int> loc = newpiece->getLocation();
	if (inBounds(loc)){
		std::unique_ptr<BoardStatic>& curr_ptr = this->environmentCells.find(loc)->second;
		curr_ptr.swap(newpiece);
		return true;
	}
	return false;
}

bool GameBoardStructure::addBoardEffect(std::unique_ptr<Effect>& effect){
	const Coordinate3D<int>& loc = Util::screenToCoord(effect->getScreenLocation());

	if(inBounds(loc)){
		environmentCells[loc]->addEffect(effect);
		return true;
	}
	return false;
}
bool GameBoardStructure::addActor(std::shared_ptr<BoardActor>& actor){
	const Coordinate3D<int>& actorloc = actor->getLocation();
	if(openSpace(actorloc)){
		environmentCells[actorloc]->setActor(actor);
		return true;
	}
	return false;
}
bool GameBoardStructure::addFloor(std::unique_ptr<BoardFloor>& floor){
	const Coordinate3D<int>& loc = floor->getLocation();

	if(inBounds(loc)){
		environmentCells[loc]->setFloor(floor);
		return true;
	}
	return false;
}
bool GameBoardStructure::addWall(std::unique_ptr<BoardWall>& wall){
	const Coordinate3D<int>& loc = wall->getLocation();
	WallEdge edge = wall->getEdge();

	if(inBounds(loc)){
		environmentCells[loc]->setWall(wall, edge);
		return true;
	}
	return false;
}
bool GameBoardStructure::addObject(std::unique_ptr<BoardStatic>& object){
	const Coordinate3D<int>& loc = object->getLocation();

	if(inBounds(loc)){
		environmentCells[loc]->addObject(object);
		return true;
	}
	return false;
}
bool GameBoardStructure::addDecoration(std::unique_ptr<BoardDecoration>& decoration){
	const Coordinate3D<int>& loc = decoration->getLocation();

	if(inBounds(loc)){
		environmentCells[loc]->addDecoration(decoration);
		return true;
	}
	return false;
}

bool GameBoardStructure::openSpace(const Coordinate3D<int>& loc) const{
	return (inBounds(loc) && !actorExists(loc) && traversableSpace(loc));
}

bool GameBoardStructure::traversableSpace(const Coordinate3D<int>& loc) const{
	BoardCell& cell = *environmentCells[loc];
	return cell.isTraversable();
}

bool GameBoardStructure::inBounds(const Coordinate3D<int>& loc) const{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < length && loc.z >= 0 && loc.z > height;
}

bool GameBoardStructure::actorExists(int x, int y, int z) const{
	BoardCell& cell = *environmentCells[Coordinate3D<int>(x,y,z)];
	return cell.actorExists();
}
bool GameBoardStructure::actorExists(const Coordinate3D<int>& loc) const{
	BoardCell& cell = *environmentCells[loc];
	return cell.actorExists();
}

const std::shared_ptr<BoardActor>& GameBoardStructure::getActor(int x, int y, int z) const{
	return getActor(Coordinate3D<int>(x,y,z));
}
const std::shared_ptr<BoardActor>& GameBoardStructure::getActor(const Coordinate3D<int>& loc) const{
	BoardCell& cell = *environmentCells[loc];
	return cell.getActor();
}

bool GameBoardStructure::removeActor(const Coordinate3D<int>& loc){
	if (actorExists(loc)){
		environmentCells[loc]->removeActor();
		return true;
	}
	return false;
}

bool GameBoardStructure::moveActor(const Coordinate3D<int>& curr_loc, const Coordinate3D<int>& new_loc){
	if(openSpace(new_loc) && actorExists(curr_loc)){
		std::shared_ptr<BoardActor> actor = environmentCells[curr_loc]->getActor();
		environmentCells[new_loc]->setActor(actor);
		environmentCells[curr_loc]->removeActor();
		return true;
	}
	return false;
}


bool GameBoardStructure::effectsExist(const Coordinate3D<int>& loc) const{
	return (effects.count(loc) > 0);
}

int GameBoardStructure::numEffects(const Coordinate3D<int>& loc) const{
	if(effectsExist(loc)){
		return effects.find(loc)->second.size();
	}
	return 0;
}

const std::map<Coordinate3D<int>, std::vector<std::unique_ptr<Effect>>>& GameBoardStructure::getEffects() const{
	return effects;
}


const std::vector<std::unique_ptr<Effect>>& GameBoardStructure::getEffects(const Coordinate3D<int>& loc) const{
	return effects.find(loc)->second;
}

const Effect& GameBoardStructure::getEffect(const Coordinate3D<int>& loc) const{
	return *(effects.find(loc)->second.back());
}

int GameBoardStructure::getLength() const{
	return length;
}


int GameBoardStructure::getWidth() const{
	return width;
}

int GameBoardStructure::getHeight() const{
	return height;
}

std::map<Coordinate3D<int>, std::shared_ptr<BoardCell>>& GameBoardStructure::getCells(){
	return environmentCells;
}

std::shared_ptr<BoardCell>& GameBoardStructure::getCell(Coordinate3D<int> loc){
	return environmentCells[loc];
}

bool GameBoardStructure::handleEffect(const std::unique_ptr<Effect>& effect, const Coordinate3D<int>& loc){
	if(!inBounds(loc))
		return true;

	switch (effect->getType()){
	case ATTACKEFFECT:
	{
		AttackEffect& attack_effect = (AttackEffect&)(*effect);
		if(actorExists(loc)){
			return getActor(loc)->recieveAttack(attack_effect.getAttack());
		}
		BoardCell& cell = *(this->environmentCells.find(loc)->second);
		for(unsigned int i = 0; i < cell.getObjects().size(); i++){
			BoardStatic& setpiece = cell.getObjects()[i];
			if(setpiece.getType() == STATICCOVER){
				return setpiece.recieveAttack(attack_effect.getAttack());
			}
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
	std::vector<Coordinate3D<int>> empty_cells;
	for (auto map_it = effects.begin(); map_it != effects.end(); ++map_it){
		Coordinate3D<int> board_loc = map_it->first;
		for(auto vec_it = map_it->second.begin(); vec_it < map_it->second.end(); ++vec_it){
			Coordinate3D<int> effect_loc = Util::screenToCoord((*vec_it)->getScreenLocation());
			if(effect_loc != board_loc){
				if(!handleEffect(*vec_it, effect_loc)){
					addBoardEffect(*vec_it);
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
			for(int z = 0; z < height; z++){
				environmentCells[Coordinate3D<int>(x,y,z)]->update();
			}
		}
	}
}

void GameBoardStructure::update(){
	updateEffects();
	updateEnvironment();
}


