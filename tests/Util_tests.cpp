#include "Util.h"
#include "UnitTest++.h"

SUITE(Util){
	TEST(coord_converters)
	{
		Coordinate loc(1,1);
		ScreenCoordinate conv = Util::coordToScreen(loc);
		Coordinate conv_back = Util::screenToCoord(conv);

		CHECK(loc == conv_back);
	}

}
