#define CONFIG_CATCH_MAIN
#include"catch.hpp"
#include"CPS.hpp"

TEST_CASE("Test height and width function()") {
	SECTION("Circle heigth and width") {
		{
			INFO("Circle height");
			auto cir = makeCircle(4.0);
			REQUIRE(cir->getHeight() == 8.0);
		}
        {
            INFO("Circle width");
			auto cir = makeCircle(4.0);
			REQUIRE(cir->getWidth() == 8.0);
        }
    }

    SECTION("Polygon height and width") {
        {
            INFO("Polygon height");
            auto pol = makePolygon(5,5.0);
            REQUIRE(pol->getHeight() ==  );
        }
        {
            INFO("Polygon width");
            auto pol = makePolygon(5,5.0);
            REQUIRE(pol->getWidth() ==  );   
        }
    }
    SECTION("Rectangle height and width") {
        {
            INFO("Rectangle height");
            auto rec = makeRectangle(5.0,3.0);
            REQUIRE(rec->getHeight() == 3.0 );
        }
        {
            INFO("Rectangle width");
            auto rec = makeRectangle(5.0,3.0);
            REQUIRE(rec->getWidth() == 5.0);
        }
    }
    SECTION("Spacer height and width"){
        {
            INFO("Spacer height");
            auto spac = makeSpacer(6.0,4.0);
            REQUIRE(spac-> getHeight() == 4.0);
        }
        {
            INFO("Spacer width");4
            auto spac = makeSpacer(6.0,4.0);
            REQUIRE(spac-> getWidth() == 6.0);
        }
    }
    SECTION("Square height and width"){
        {
            INFO("Square height");
            auto spac = makeSquare(2.0);
            REQUIRE(spac-> getHeight() == 2.0 );
        }
        {
            INFO("Spacer width");
            auto spac = makeSpacer(2.0); 
            REQUIRE(spac-> getWidth() == 2.0 );
        }
    }

    //NOT COMPLETED
     SECTION("Triangle height and width"){ 
        {
            INFO("Triangle height");
            auto spac = makeTriangle(4.0); 
            REQUIRE(spac-> getHeight() == );
        }
        {
            INFO("Triangle width");
            auto spac = makeTriangle(4.0); 
            REQUIRE(spac-> getWidth() == );
        }
    }
}
