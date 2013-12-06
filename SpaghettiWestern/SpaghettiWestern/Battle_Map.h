#ifndef BATTLE_MAP_H
#define BATTLE_MAP_H

class Battle_Map
{
public:
	Battle_Map();
	Battle_Map(Battle_Map& other);

	int render();

private:
	Setpiece* pieces; // array of all setpieces with this Battle_Map
	int num_pieces;
	int pieces_size;


	~Battle_Map();
}

#endif