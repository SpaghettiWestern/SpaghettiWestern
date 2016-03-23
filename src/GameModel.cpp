#include "GameModel.h"

GameModel::GameModel(int board_length, int board_width,int board_height) :
	board(GameBoard(board_length, board_width, board_height)){

	players.clear();
}

GameModel::GameModel(int board_length, int board_width, int board_height, std::vector<std::pair<std::string,bool>> init_players) :
		board(GameBoard(board_length, board_width, board_height)){

	players.clear();
	for (unsigned int i = 0; i < init_players.size(); i++){
		players.push_back(Player(init_players[i].first, init_players[i].second));
	}
}

const GameBoard& GameModel::getGameBoard() const {
	return board;
}
const std::vector<Player>& GameModel::getPlayers() const{
	return players;
}

bool GameModel::playerExists(int index) const{
	return index >= 0 && (unsigned int)index < players.size();
}

const Player& GameModel::getPlayer(int index) const{
	return players[index];
}

bool GameModel::createActor(Coordinate3D<int> loc, int owner_index, int hitpoints){
	if(playerExists(owner_index) && board.openSpace(loc)){
		Player& owner = players[owner_index];
		std::shared_ptr<BoardActor> new_actor(new BoardActor(loc, owner, hitpoints));
		owner.addActor(new_actor);
		board.addActor(new_actor);
		return true;
	}
	return false;
}

bool GameModel::createActor(Coordinate3D<int> loc, int owner_index, int hitpoints, Attack attack){
	if(playerExists(owner_index) && board.openSpace(loc)){
		Player& owner = players[owner_index];
		std::shared_ptr<BoardActor> new_actor(new ActionActor(loc, owner, hitpoints, attack));
		owner.addActor(new_actor);
		board.addActor(new_actor);
		return true;
	}
	return false;
}

bool GameModel::createWall(Coordinate3D<int> loc, int hitpoints){
	board.addStaticCoverPiece(loc, false, hitpoints, 1000);
	return true;
}

bool GameModel::sendAttack(Coordinate3D<int> attacker_loc, Coordinate3D<int> attack_loc){
	if(board.canAttack(attacker_loc, attack_loc)){
		return sendAttack((ActionActor&)*(board.getActorPointer(attacker_loc)), *(board.getActorPointer(attack_loc)));
	}
	return false;
}

bool GameModel::sendAttack(ActionActor& attacker, BoardActor& receiver){
	std::unique_ptr<Effect> attack_ptr(new AttackEffect(attacker.getScreenLocation(), attacker.getAttack()));
	AttackEffect& bullet = (AttackEffect&)(*attack_ptr);
	bullet.generatePath(receiver.getScreenLocation());
	bullet.MovingEffect::startMove();
	board.addBoardEffect(attack_ptr);
	return true;
}

bool GameModel::playStaticEffect(const Coordinate2D<double>& loc, bool surface_level){
	std::unique_ptr<Effect> new_effect_ptr(new Effect(loc));
	if(surface_level)
		board.addSurfaceEffect(new_effect_ptr);
	else
		board.addBoardEffect(new_effect_ptr);

	return true;
}

bool GameModel::playMovingEffect(const Coordinate2D<double>& start, const Coordinate2D<double>& dest, bool surface_level){
	std::unique_ptr<Effect> new_effect_ptr(new MovingEffect(start));
	MovingEffect& new_effect = (MovingEffect&)(*new_effect_ptr);
	new_effect.generatePath(dest, .001);
	new_effect.startMove();
	if(surface_level)
		board.addSurfaceEffect(new_effect_ptr);
	else
		board.addBoardEffect(new_effect_ptr);

	return true;
}

void GameModel::update(){
	for(unsigned int i = 0; i < players.size(); i++){
		players[i].update();
	}
	board.update();
}

