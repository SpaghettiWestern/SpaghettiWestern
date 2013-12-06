#include "Battle_Map.h"
#include <omp.h>

Battle_Map::Battle_Map()
{
	pieces_size = 200;
	pieces = new Setpiece[pieces_size];
	num_pieces = 0;
}

Battle_Map::Battle_Map(Battle_Map& other)
{
	pieces_size = other.pieces_size;
	num_pieces = other.num_pieces;
	pieces = new Setpiece[pieces_size];
	for (int i = 0; i < num_pieces; i++)
	{
		pieces[i] = new SetPiece(other.pieces[i]);
	}
}

int Battle_Map::render()
{
	#pragma omp parallel for
	for (int i = 0; i < num_pieces; i++)
	{
		pieces[i].render();
	}
}

Battle_Map::~Battle_Map()
{
	delete pieces;
}