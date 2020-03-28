#include"catch.hpp"
#include"CPS.hpp"

TEST_CASE("Test heigth and width function()") {
	SECTION("Circle heigth and width") {
		{
			INFO("Circle height");
			Circle cir(4.0);
			REQUIRE(cir.getHeight() == 8.0);
		}
	}
}