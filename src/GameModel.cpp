#include "GameModel.h"

GameModel::GameModel(int board_length, int board_width) : board(GameBoard(board_length, board_width)){
	players.clear();
}

GameModel::GameModel(int board_length, int board_width, std::vector<std::pair<std::string,bool>> init_players) :
		board(GameBoard(board_length, board_width)){

	players.clear();
	for (unsigned int i = 0; i < init_players.size(); i++){
		players.push_back(Player(init_players[i].first, init_players[i].second));
	}
}

GameBoard& GameModel::getGameBoard(){
	return board;
}
std::vector<Player>& GameModel::getPlayers(){
	return players;
}

bool GameModel::playerExists(int index){
	return index >= 0 && (unsigned int)index < players.size();
}

Player& GameModel::getPlayer(int index){
	return players[index];
}

bool GameModel::createActor(Coordinate loc, int owner_index, int hitpoints){
	if(playerExists(owner_index) && board.openSpace(loc)){
		Player& owner = getPlayer(owner_index);
		std::shared_ptr<BoardActor> new_actor(new BoardActor(loc, owner, hitpoints));
		owner.addActor(new_actor);
		board.addActor(new_actor);
		return true;
	}
	return false;
}

bool GameModel::createActor(Coordinate loc, int owner_index, int hitpoints, Attack attack){
	if(playerExists(owner_index) && board.openSpace(loc)){
		Player& owner = getPlayer(owner_index);
		std::shared_ptr<BoardActor> new_actor(new ActionActor(loc, owner, hitpoints, attack));
		owner.addActor(new_actor);
		board.addActor(new_actor);
		return true;
	}
	return false;
}

bool GameModel::sendAttack(Coordinate attacker_loc, Coordinate attack_loc){
	if(board.canAttack(attacker_loc, attack_loc)){
		return sendAttack((ActionActor&)board.getActor(attacker_loc), board.getActor(attack_loc));
	}
	return false;
}

bool GameModel::sendAttack(ActionActor& attacker, BoardActor& receiver){
	receiver.recieveAttack(attacker.getAttack());
	return true;
}

void GameModel::update(){
	for(unsigned int i = 0; i < players.size(); i++){
		players[i].update();
	}
	board.update();
}









