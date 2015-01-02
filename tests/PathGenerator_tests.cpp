#include "UnitTest++.h"
#include "PathGenerator.h"
#include "BoardActor.h"
#include "Player.h"

SUITE(PathGenerator){

	TEST(constructor){
		std::cerr << "Testing PathGenerator\n";

		std::shared_ptr<GameBoardStructure> test_board = std::make_shared<GameBoardStructure>(3,3);
		PathGenerator test_pathgen(test_board);
		CHECK(test_pathgen.getPath().size() == 0);
	}


	void check_findpath(PathGenerator& testgen, Coordinate start, Coordinate end, unsigned int expected_length){
		bool pathfound = testgen.findPath(start, end);
		CHECK(pathfound == true);
		if(pathfound){
			std::vector<Coordinate> test_path = testgen.getPath();
			CHECK(test_path.size() == expected_length);
			CHECK(test_path[0] == end);
			CHECK(test_path[expected_length-1] == start);
		}


//		std::cerr << "path: ";
//		for(unsigned int i = 0; i < expected_length; i++){
//			Util::printErrCoordinate(test_path[i]);
//			std::cerr << " ";
//		}
//		std::cerr << "\n";
	}

	void check_simple_findpath(PathGenerator& testgen, Coordinate start, Coordinate end){
		unsigned int expected_length = testgen.estimateDistance(start, end) +1;
		check_findpath(testgen, start, end, expected_length);
	}

	TEST(find_path_simple_long){
		int length = 100;
		int width = 120;
		std::shared_ptr<GameBoardStructure> test_board = std::make_shared<GameBoardStructure>(length,width);
		PathGenerator test_pathgen(test_board);
		CHECK(test_pathgen.findPath(Coordinate(0,0), Coordinate(width,length)) == false);
		CHECK(test_pathgen.findPath(Coordinate(0,0), Coordinate(-1,-1)) == false);

		check_simple_findpath(test_pathgen, Coordinate(0,0), Coordinate(width-1, length-1));
		check_simple_findpath(test_pathgen, Coordinate(width-1, length-1), Coordinate(0,0));
	}

	TEST(find_path_simple_short_exhaustive){
		int length = 20;
		int width = 40;
		std::shared_ptr<GameBoardStructure> test_board = std::make_shared<GameBoardStructure>(length,width);
		PathGenerator test_pathgen(test_board);
		CHECK(test_pathgen.findPath(Coordinate(0,0), Coordinate(width,length)) == false);
		CHECK(test_pathgen.findPath(Coordinate(0,0), Coordinate(-1,-1)) == false);

		for(int x = 0; x < width; x++){
			for(int y = 0; y < length;  y++){
				//std::cerr << "x:" << x << "   y:" << y << "\n";
				check_simple_findpath(test_pathgen, Coordinate(x,y), Coordinate(width-1, length-1));
				check_simple_findpath(test_pathgen, Coordinate(0, 0), Coordinate(x,y));
			}
		}
	}

	TEST(find_path_zigzag){
		int length = 20;
		int width = 2;

		Player test_player("tester", true);
		std::shared_ptr<GameBoardStructure> test_board = std::make_shared<GameBoardStructure>(length,width);
		PathGenerator test_pathgen(test_board);
		CHECK(test_pathgen.findPath(Coordinate(0,0), Coordinate(width,length)) == false);
		CHECK(test_pathgen.findPath(Coordinate(0,0), Coordinate(-1,-1)) == false);

		int x = 0;
		for(int y = 1; y < length-1; y+=2){
			test_board->addActor(std::make_shared<BoardActor>(Coordinate(x, y), test_player));
			if(x)
				x--;
			else
				x++;
		}
		Coordinate start(0,0);
		Coordinate end(0,19);
		check_findpath(test_pathgen, start, end, 30);

	}

	TEST(find_path_walls){
		int length = 10;
		int width = 10;

		Player test_player("tester", true);
		std::shared_ptr<GameBoardStructure> test_board = std::make_shared<GameBoardStructure>(length,width);
		PathGenerator test_pathgen(test_board);
		CHECK(test_pathgen.findPath(Coordinate(0,0), Coordinate(width,length)) == false);
		CHECK(test_pathgen.findPath(Coordinate(0,0), Coordinate(-1,-1)) == false);

		for(int x = 1, y = 8; x < width && y > -1; x++, y--){
			test_board->addActor(std::make_shared<BoardActor>(Coordinate(x,y), test_player));
		}
		for(int y = 9; y > 5; y--){
			test_board->addActor(std::make_shared<BoardActor>(Coordinate(8,y), test_player));
		}
		Coordinate start(0,0);
		Coordinate end(9,9);
		check_findpath(test_pathgen, start, end, 27);
	}



}
