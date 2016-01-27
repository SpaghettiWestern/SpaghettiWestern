#include "PathGenerator.h"

PathGenerator::PathGenerator(std::shared_ptr<GameBoardStructure>& board) : board(board){
	resetSets();
	curr = Coordinate(-1,-1);
	end = Coordinate(-1,-1);
}

void PathGenerator::resetSets(){
	closed_set.clear();
	open_set.clear();
	came_from.clear();
	g_score.clear();
	f_score.clear();
	path.clear();
}

int PathGenerator::estimateDistance(Coordinate& start, Coordinate& end){
	return std::abs(start.first - end.first) + std::abs(start.second-end.second);
}

Coordinate PathGenerator::getSmallestOpen(){
	Coordinate smallest = open_set.begin()->first;
	for(auto it = open_set.begin(); it != open_set.end(); ++it){
		if(f_score[smallest] > f_score[it->first]){
			smallest = it->first;
		}
	}
	open_set.erase(smallest);
	return smallest;
}

void PathGenerator::traverseNeighbors(){
	traverseNeighbor(Coordinate(curr.first+1, curr.second));
	traverseNeighbor(Coordinate(curr.first-1, curr.second));
	traverseNeighbor(Coordinate(curr.first, curr.second+1));
	traverseNeighbor(Coordinate(curr.first, curr.second-1));

}

void PathGenerator::traverseNeighbor(Coordinate neighbor){
	if(closed_set.count(neighbor) > 0){
		return;
	}
	if(!(board->openSpace(neighbor))){
		closed_set[neighbor] = true;
		return;
	}

	int tmp_g_score = g_score[curr] + 1;

	if(open_set.count(neighbor) == 0 || g_score.count(neighbor) == 0 || tmp_g_score < g_score[neighbor]){
		came_from[neighbor] = curr;
		g_score[neighbor] = tmp_g_score;
		f_score[neighbor] = tmp_g_score + estimateDistance(neighbor, end);
		open_set[neighbor] = true;
	}
}

void PathGenerator::reconstructPath(Coordinate start){
	path.clear();
	Coordinate curr_step = end;
	while(curr_step != start){
		path.push_back(curr_step);
		curr_step = came_from[curr_step];
	}
	path.push_back(start);
}

bool PathGenerator::findPath(Coordinate start, Coordinate goal){
	resetSets();

	end = goal;

	open_set[start] = true;
	g_score[start] = 0;
	f_score[start] = g_score[start] + estimateDistance(start, end);

	while(!open_set.empty()){
		curr = getSmallestOpen();
		if (curr == end){
			reconstructPath(start);
			return true;
		}
		closed_set[curr] = true;
		traverseNeighbors();
	}
	return false;
}

std::vector<Coordinate> PathGenerator::getPath(){
	return path;
}



