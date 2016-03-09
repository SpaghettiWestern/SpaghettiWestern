#include "UnitTest++.h"
#include "PathGenerator.h"
#include "BoardActor.h"
#include "Player.h"

SUITE(PathGenerator){

	TEST(constructor){
		std::cerr << "Testing PathGenerator\n";

		std::shared_ptr<GameBoardStructure> test_board = std::make_shared<GameBoardStructure>(3,3,3);
		PathGenerator test_pathgen(test_board);
		CHECK(test_pathgen.getPath().size() == 0);
	}


	void check_findpath(PathGenerator& testgen, Coordinate3D<int> start, Coordinate3D<int> end, unsigned int expected_length){
		bool pathfound = testgen.findPath(start, end);
		CHECK(pathfound == true);
		if(pathfound){
			std::vector<Coordinate3D<int>> test_path = testgen.getPath();
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

	void check_simple_findpath(PathGenerator& testgen, Coordinate3D<int> start, Coordinate3D<int> end){
		unsigned int expected_length = testgen.estimateDistance(start, end) +1;
		check_findpath(testgen, start, end, expected_length);
	}

	TEST(find_path_simple_long){
		std::cerr << "find path simple long\n";
		int length = 100;
		int width = 120;
		int height = 1;
		std::shared_ptr<GameBoardStructure> test_board = std::make_shared<GameBoardStructure>(length,width, height);
		PathGenerator test_pathgen(test_board);
		CHECK(test_pathgen.findPath(Coordinate3D<int>(0,0,0), Coordinate3D<int>(width,length,0)) == false);
		CHECK(test_pathgen.findPath(Coordinate3D<int>(0,0,0), Coordinate3D<int>(-1,-1,0)) == false);

		check_simple_findpath(test_pathgen, Coordinate3D<int>(0,0,0), Coordinate3D<int>(width-1, length-1,0));
		check_simple_findpath(test_pathgen, Coordinate3D<int>(width-1, length-1,0), Coordinate3D<int>(0,0,0));
	}

	TEST(find_path_simple_short_exhaustive){
		std::cerr << "find path simple exhaustive\n";
		int length = 20;
		int width = 40;
		int height = 1;
		std::shared_ptr<GameBoardStructure> test_board = std::make_shared<GameBoardStructure>(length,width, height);
		PathGenerator test_pathgen(test_board);
		CHECK(test_pathgen.findPath(Coordinate3D<int>(0,0,0), Coordinate3D<int>(width,length,0)) == false);
		CHECK(test_pathgen.findPath(Coordinate3D<int>(0,0,0), Coordinate3D<int>(-1,-1,0)) == false);

		for(int x = 0; x < width; x++){
			for(int y = 0; y < length;  y++){
				//std::cerr << "x:" << x << "   y:" << y << "\n";
				check_simple_findpath(test_pathgen, Coordinate3D<int>(x,y,0), Coordinate3D<int>(width-1, length-1,0));
				check_simple_findpath(test_pathgen, Coordinate3D<int>(0, 0,0), Coordinate3D<int>(x,y,0));
			}
		}
	}

	TEST(find_path_zigzag){
		std::cerr << "find path zig zag\n";
		int length = 20;
		int width = 2;
		int height = 1;

		Player test_player("tester", true);
		std::shared_ptr<GameBoardStructure> test_board = std::make_shared<GameBoardStructure>(length,width, height);
		PathGenerator test_pathgen(test_board);
		CHECK(test_pathgen.findPath(Coordinate3D<int>(0,0,0), Coordinate3D<int>(width,length,0)) == false);
		CHECK(test_pathgen.findPath(Coordinate3D<int>(0,0,0), Coordinate3D<int>(-1,-1,0)) == false);

		int x = 0;
		for(int y = 1; y < length-1; y+=2){
			std::shared_ptr<BoardActor> actor = std::make_shared<BoardActor>(Coordinate3D<int>(x,y,0), test_player);
			test_board->addActor(actor);
			if(x)
				x--;
			else
				x++;
		}
		Coordinate3D<int> start(0,0,0);
		Coordinate3D<int> end(0,19,0);
		check_findpath(test_pathgen, start, end, 30);

	}

	TEST(find_path_walls){
		std::cerr << "find path walls\n";
		int length = 10;
		int width = 10;
		int height = 1;

		Player test_player("tester", true);
		std::shared_ptr<GameBoardStructure> test_board = std::make_shared<GameBoardStructure>(length,width, height);
		PathGenerator test_pathgen(test_board);
		CHECK(test_pathgen.findPath(Coordinate3D<int>(0,0,0), Coordinate3D<int>(width,length,0)) == false);
		CHECK(test_pathgen.findPath(Coordinate3D<int>(0,0,0), Coordinate3D<int>(-1,-1,0)) == false);

		for(int x = 1, y = 8; x < width && y > -1; x++, y--){
			std::shared_ptr<BoardActor> actor = std::make_shared<BoardActor>(Coordinate3D<int>(x,y,0), test_player);
			test_board->addActor(actor);
		}
		for(int y = 9; y > 5; y--){
			std::shared_ptr<BoardActor> actor = std::make_shared<BoardActor>(Coordinate3D<int>(8,y,0), test_player);
			test_board->addActor(actor);
		}
		Coordinate3D<int> start(0,0,0);
		Coordinate3D<int> end(9,9,0);
		check_findpath(test_pathgen, start, end, 27);
	}



}
