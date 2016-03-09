#include "PathGenerator.h"

PathGenerator::PathGenerator(std::shared_ptr<GameBoardStructure>& board) : board(board){
	resetSets();
	curr = Coordinate3D<int>(-1,-1,-1);
	end = Coordinate3D<int>(-1,-1,-1);
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

int PathGenerator::estimateDistance(const Coordinate3D<int>& start, const Coordinate3D<int>& end){
	return std::abs(start.x - end.x) + std::abs(start.y-end.y) + std::abs(start.z-end.z);
}

void PathGenerator::traverseNeighbors(){
	const BoardCell& currCell =  board->getEnvironmentCell(curr);
	for(unsigned int i = 0; i < currCell.getNumNeighbors(); i++){
		traverseNeighbor(currCell.getNeighbor(i).getLocation());
	}
}

void PathGenerator::traverseNeighbor(const Coordinate3D<int>& neighbor){
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

void PathGenerator::reconstructPath(const Coordinate3D<int>& start){
	path.clear();
	Coordinate3D<int> curr_step = end;
	while(curr_step != start){
		path.push_back(curr_step);
		curr_step = came_from[curr_step];
	}
	path.push_back(start);
}

bool PathGenerator::findPath(const Coordinate3D<int>& start, const Coordinate3D<int>& goal){
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

std::vector<Coordinate3D<int>> PathGenerator::getPath(){
	return path;
}

distanceCoordinate::distanceCoordinate(const Coordinate3D<int>& coord, int g_score, int f_score) :
	coord(coord), g_score(g_score), f_score(f_score){

}

CoordinateComparison::CoordinateComparison(){

}

bool CoordinateComparison::operator() (const distanceCoordinate& lhs, const distanceCoordinate& rhs) const {
	if(lhs.f_score > rhs.f_score)
		return true;
	return false;
}


