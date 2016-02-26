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

	this->numTiers = 1;
	this->spriteSheet = BlitHelper::loadImageGL("C:\\workspace\\SpaghettiWestern\\Resources\\floor_wood1.png");

	hSize = .10;
	vSize = .10;
	double theta = 80;
	double pi = 3.14159265358;
	h = vSize / (cos(theta/180*pi) + 1);
	s = h * cos(theta/180*pi);
	lookAtCoord.first = 0;
	lookAtCoord.second = 0;
}

void GameBoardStructure::initEnvironment(){
	environment.clear();
	for(int i = 0; i < width; i++){
		for(int j = 0; j < length; j++){
//			if (j > 6)
//				environment[Coordinate(i,j)] = std::unique_ptr<BoardStatic>(new BoardStatic(Coordinate(i,j), false));
//			else
				environment[Coordinate(i,j)] = std::unique_ptr<BoardStatic>(new BoardStatic(Coordinate(i,j), true, -1));
		}
	}
}

void GameBoardStructure::initActors(){
	actors.clear();
}

GameBoardStructure::GameBoardStructure(const GameBoardStructure& other){
	*this = other;
}

GameBoardStructure& GameBoardStructure::operator=(const GameBoardStructure& other){
	if(this != &other){
		length = other.getLength();
		width = other.getWidth();

		environment.clear();
		effects.clear();
		actors.clear();

		for(int x = 0; x < width; x++){
			for(int y = 0; y < length; y++){
				Coordinate loc(x,y);
				environment[loc] = std::unique_ptr<BoardStatic>(new BoardStatic(other.getEnvironmentPiece(loc)));
				if (other.actorExists(loc)){
					actors[loc] = std::shared_ptr<BoardActor>(new BoardActor(*(other.getActor(loc))));
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

bool GameBoardStructure::addActor(std::shared_ptr<BoardActor> actor){
	Coordinate actorloc = actor->getLocation();
	if(openSpace(actorloc)){
		actors[actorloc] = actor;
		return true;
	}
	return false;
}

const BoardStatic& GameBoardStructure::getEnvironmentPiece(int x, int y) const{
	return getEnvironmentPiece(Coordinate(x,y));
}
const BoardStatic& GameBoardStructure::getEnvironmentPiece(const Coordinate& loc) const{
	return *(this->environment.find(loc)->second);
}

bool GameBoardStructure::addEnvironmentPiece(std::unique_ptr<BoardStatic>& newpiece){
	if (newpiece.get() == NULL){
		return false;
	}

	Coordinate loc = newpiece->getLocation();
	if (inBounds(loc)){
		std::unique_ptr<BoardStatic>& curr_ptr = this->environment.find(loc)->second;
		curr_ptr.swap(newpiece);
		return true;
	}
	return false;
}

bool GameBoardStructure::openSpace(const Coordinate& loc) const{
	return (inBounds(loc) && !actorExists(loc) && traversableSpace(loc));
}

bool GameBoardStructure::traversableSpace(const Coordinate& loc) const{
	return (this->environment.find(loc)->second)->isTraversable();
}

bool GameBoardStructure::inBounds(const Coordinate& loc) const{
	return loc.first >= 0 && loc.first < width && loc.second >= 0 && loc.second < length;
}

bool GameBoardStructure::actorExists(int x, int y) const{
	return actorExists(Coordinate(x,y));
}
bool GameBoardStructure::actorExists(const Coordinate& loc) const{
	return actors.count(loc) > 0;
}

const std::map<Coordinate, std::shared_ptr<BoardActor>>& GameBoardStructure::getActors() const{
	return actors;
}

const std::shared_ptr<BoardActor>& GameBoardStructure::getActor(int x, int y) const{
	return getActor(Coordinate(x,y));
}
const std::shared_ptr<BoardActor>& GameBoardStructure::getActor(const Coordinate& loc) const{
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


bool GameBoardStructure::effectsExist(const Coordinate& loc) const{
	return (effects.count(loc) > 0);
}

int GameBoardStructure::numEffects(const Coordinate& loc) const{
	if(effectsExist(loc)){
		return effects.find(loc)->second.size();
	}
	return 0;
}

const std::map<Coordinate, std::vector<std::unique_ptr<Effect>>>& GameBoardStructure::getEffects() const{
	return effects;
}


const std::vector<std::unique_ptr<Effect>>& GameBoardStructure::getEffects(const Coordinate& loc) const{
	return effects.find(loc)->second;
}

const Effect& GameBoardStructure::getEffect(const Coordinate& loc) const{
	return *(effects.find(loc)->second.back());
}

bool GameBoardStructure::addEffect(std::unique_ptr<Effect>& new_effect){
	Coordinate loc = Util::screenToCoord(new_effect->getScreenLocation());
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

bool GameBoardStructure::handleEffect(const std::unique_ptr<Effect>& effect, const Coordinate& loc){
	if(!inBounds(loc))
		return true;

	switch (effect->getType()){
	case ATTACKEFFECT:
	{
		AttackEffect& attack_effect = (AttackEffect&)(*effect);
		if(actorExists(loc)){
			return getActor(loc)->recieveAttack(attack_effect.getAttack());
		}
		BoardStatic& setpiece = *(this->environment.find(loc)->second);
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
