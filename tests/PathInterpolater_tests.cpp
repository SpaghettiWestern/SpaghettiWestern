#include "UnitTest++.h"
#include "PathInterpolater.h"

SUITE(PathInterpolater){

	TEST(constructor){
		std::cerr << "Testing PathInterpolater\n";

		PathInterpolater test_interpolater;
		CHECK(test_interpolater.getPath().empty() ==  true);
	}

	TEST(transfer_path){
		PathInterpolater test_interpolater;
		Coordinate2D<double> start(0.0,0.0);
		Coordinate2D<double> end(1.0, 4.0);
		double speed = 1.0;
		std::vector<Coordinate2D<double>> dest_path;
		dest_path.clear();
		test_interpolater.generatePath(start, end, speed);

		CHECK(test_interpolater.getPath().empty() == false);

		test_interpolater.transferPath(dest_path);

		CHECK(dest_path.size() > 0);
		CHECK(test_interpolater.getPath().empty() == true);
	}

	TEST(generate_path_simple1){
		PathInterpolater test_interpolater;

		Coordinate2D<double> start(0.0,0.0);
		Coordinate2D<double> end(0.0, 4.0);
		double speed = 1.0;
		std::vector<Coordinate2D<double>> dest_path;
		test_interpolater.generatePath(start, end, speed);
		test_interpolater.transferPath(dest_path);

		CHECK(dest_path.size() == 5);
		for(double i = 0.0; i < 5.0; i+=1.0){
			Coordinate2D<double> loc(0.0, 0.0+i);
			if(!dest_path.empty()){
				CHECK(dest_path.back() == loc);
				dest_path.pop_back();
			}
		}
	}

	TEST(generate_path_simple2){
		PathInterpolater test_interpolater;

		Coordinate2D<double> start(0.0,0.0);
		Coordinate2D<double> end(0.0, -4.0);
		double speed = 1.0;
		std::vector<Coordinate2D<double>> dest_path;
		test_interpolater.generatePath(start, end, speed);
		test_interpolater.transferPath(dest_path);

		CHECK(dest_path.size() == 5);
		for(double i = 0.0; i < 5.0; i+=1.0){
			Coordinate2D<double> loc(0.0, 0.0-i);
			if(!dest_path.empty()){
				CHECK(dest_path.back() == loc);
				dest_path.pop_back();
			}
		}
	}

	TEST(generate_path_simple3){
		PathInterpolater test_interpolater;

		Coordinate2D<double> start(1.0,1.0);
		Coordinate2D<double> end(5.0, 1.0);
		double speed = 1.0;
		std::vector<Coordinate2D<double>> dest_path;
		test_interpolater.generatePath(start, end, speed);
		test_interpolater.transferPath(dest_path);

		CHECK(dest_path.size() == 5);
		for(double i = 0.0; i < 5.0; i+=1.0){
			Coordinate2D<double> loc(1.0+i, 1.0);
			if(!dest_path.empty()){
				CHECK(dest_path.back() == loc);
				dest_path.pop_back();
			}
		}
	}

	TEST(generate_path_complex){
		PathInterpolater test_interpolater;

		Coordinate2D<double> start(1.3, 7.24);
		Coordinate2D<double> end(-4.3, 9.3333);
		double speed = 0.345;

		double x_dist = end.first - start.first;
		double y_dist = end.second - start.second;
		double dist = sqrt(x_dist*x_dist + y_dist*y_dist);

		double x_step = speed * (x_dist/dist);
		double y_step = speed * (y_dist/dist);

		std::vector<Coordinate2D<double>> dest_path;
		test_interpolater.generatePath(start, end, speed);
		test_interpolater.transferPath(dest_path);

		unsigned int num_steps = (int)(dist/speed +2);
		CHECK(dest_path.size() == num_steps);
		for(unsigned int i = 0; i < dest_path.size()-1 && !dest_path.empty(); i++){
			Coordinate2D<double> loc(-4.3-(x_step*i), 9.3333-(y_step*i));
			CHECK(Util::almostEquals_ScreenCoordinate(dest_path[i], loc));
		}
		if(!dest_path.empty())
			CHECK(dest_path.back() == start);
	}
}





