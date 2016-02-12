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
	pq_open_set = std::priority_queue<distanceCoordinate,
								   	  std::vector<distanceCoordinate>,
									  CoordinateComparison>();
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

int PathGenerator::estimateDistance(const Coordinate& start, const Coordinate& end){
	return std::abs(start.first - end.first) + std::abs(start.second-end.second);
}

void PathGenerator::traverseNeighbors(){
	traverseNeighbor(Coordinate(curr.first+1, curr.second));
	traverseNeighbor(Coordinate(curr.first-1, curr.second));
	traverseNeighbor(Coordinate(curr.first, curr.second+1));
	traverseNeighbor(Coordinate(curr.first, curr.second-1));
}

void PathGenerator::traverseNeighbor(const Coordinate& neighbor){
	if(closed_set.count(neighbor) > 0){
		return;
	}

	if(!(board->openSpace(neighbor))){
		closed_set[neighbor] = true;
		return;
	}

	if(open_set.count(neighbor) == 0){
		open_set[neighbor] = true;
	}

	if(!open_set[neighbor]){
		return;
	}

	int tmp_g_score = g_score[curr] + 1;

	if(g_score.count(neighbor) == 0 || tmp_g_score < g_score[neighbor]){
		came_from[neighbor] = curr;
		g_score[neighbor] = tmp_g_score;
		f_score[neighbor] = tmp_g_score + estimateDistance(neighbor, end);

		pq_open_set.push(distanceCoordinate(neighbor, g_score[neighbor], f_score[neighbor]));
	}
}

void PathGenerator::reconstructPath(const Coordinate& start){
	path.clear();
	Coordinate curr_step = end;
	while(curr_step != start){
		path.push_back(curr_step);
		curr_step = came_from[curr_step];
	}
	path.push_back(start);
}

bool PathGenerator::findPath(const Coordinate& start, const Coordinate& goal){
	resetSets();

	if(!board->openSpace(goal))
		return false;

	end = goal;

	pq_open_set.push(distanceCoordinate(start, 0, estimateDistance(start, end)));
	open_set[start] = true;

	while(!open_set.empty()){
		curr = pq_open_set.top().coord;
		pq_open_set.pop();

		open_set[curr] = false;
		closed_set[curr] = true;
		if (curr == end){
			reconstructPath(start);
			return true;
		}

		traverseNeighbors();
	}
	return false;
}

std::vector<Coordinate> PathGenerator::getPath(){
	return path;
}

distanceCoordinate::distanceCoordinate(const Coordinate& coord, int g_score, int f_score) :
	coord(coord), g_score(g_score), f_score(f_score){

}

CoordinateComparison::CoordinateComparison(){

}

bool CoordinateComparison::operator() (const distanceCoordinate& lhs, const distanceCoordinate &rhs) const {
	if(lhs.f_score > rhs.f_score)
		return true;
	return false;
}


