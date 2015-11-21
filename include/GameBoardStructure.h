#ifndef GAMEBOARDSTRUCTURE_H
#define GAMEBOARDSTRUCTURE_H

#include <memory>
#include <map>
#include <vector>

#include "Util.h"
#include "BoardActor.h"
#include "BoardStatic.h"
#include "Player.h"
#include "Effect.h"
#include "AttackEffect.h"

class GameBoardStructure{
private:
	std::map<Coordinate, std::shared_ptr<BoardActor>> actors;
	std::map<Coordinate, std::vector<std::unique_ptr<Effect>>> effects;
	std::map<Coordinate, std::unique_ptr<BoardStatic>> environment;

	int length;
	int width;

	void initEnvironment();
	void initActors();

	bool handleEffect(const std::unique_ptr<Effect>& effect, const Coordinate& loc);
	void updateEffects_base();
	void updateEffects_reposition();
	void updateEnvironment();
	void updateEffects();

public:
	GameBoardStructure(int length, int width);
	GameBoardStructure(const GameBoardStructure& other);
	GameBoardStructure& operator=(const GameBoardStructure& other);

	const BoardStatic& getEnvironmentPiece(int x, int y) const;
	const BoardStatic& getEnvironmentPiece(const Coordinate& loc) const;

	bool addEnvironmentPiece(std::unique_ptr<BoardStatic>& newpiece);

	bool openSpace(const Coordinate& loc) const;
	bool inBounds(const Coordinate& loc) const;
	bool traversableSpace(const Coordinate& loc) const;

	bool actorExists(int x, int y) const;
	bool actorExists(const Coordinate& loc) const;
	bool addActor(std::shared_ptr<BoardActor> actor);

	const std::map<Coordinate, std::shared_ptr<BoardActor>>& getActors() const;
	const std::shared_ptr<BoardActor>& getActor(int x, int y) const;
	const std::shared_ptr<BoardActor>& getActor(const Coordinate& loc) const;
	bool removeActor(const Coordinate& loc);
	bool moveActor(const Coordinate& curr_loc, const Coordinate& new_loc);

	const std::map<Coordinate, std::vector<std::unique_ptr<Effect>>>& getEffects() const;
	const std::vector<std::unique_ptr<Effect>>& getEffects(const Coordinate& loc) const;
	int numEffects(const Coordinate& loc) const;
	bool effectsExist(const Coordinate& loc) const;
	const Effect& getEffect(const Coordinate& loc) const;
	bool addEffect(std::unique_ptr<Effect>& new_effect);

	int getLength() const;
	int getWidth() const;

	void update();
};


#endif
