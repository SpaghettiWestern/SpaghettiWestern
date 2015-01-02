#include "Util.h"
#include "UnitTest++.h"

SUITE(Util){
	TEST(coord_converters)
	{
		std::cerr << "Testing Util\n";
		for(int x = 0; x < 300; x++){
			for(int y = 0; y < 300; y++){
				Coordinate loc(x,y);
				ScreenCoordinate conv = Util::coordToScreen(loc);
				Coordinate conv_back = Util::screenToCoord(conv);
				CHECK(loc == conv_back);
//				if(loc != conv_back){
//					std::cerr << "loc:";
//					Util::printErrCoordinate(loc);
//					std::cerr << "  conv_back:";
//					Util::printErrCoordinate(conv_back);
//					std::cerr << "  scrn_conv:";
//					Util::printErrScreenCoordinate(conv);
//					std::cerr << "\n";
//				}
			}
		}
	}
}
