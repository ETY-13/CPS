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
            REQUIRE(pol->getHeight() == 7.7 ); // 7.694..
        }

        {
            INFO("Polygon width");
            auto pol = makePolygon(5,5.0);
            REQUIRE(pol->getWidth() == 8.1 ); //8.0901...
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
            INFO("Spacer width");
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
            auto spac = makeSpacer(2.0,2.0); 
            REQUIRE(spac-> getWidth() == 2.0 );
        }
    }

     SECTION("Triangle height and width"){ 
        {
            INFO("Triangle height");
            auto spac = makeTriangle(4.0); 
            REQUIRE(spac-> getHeight() == 3.5); //3.464...
        }

        {
            INFO("Triangle width");
            auto spac = makeTriangle(4.0); 
            REQUIRE(spac-> getWidth() == 4.0 ); //4.0
        }
     }

     SECTION("RotatedShape height and width") {
         {
             auto rectangle = makeRectangle(5.0, 4.0);
             auto rotShape = makeRotatedShape(rectangle, Angle::R90);
             INFO("Rotated Shape height");
             REQUIRE(rotShape->getHeight() == 5.0);
             INFO("Rotated Shape width");
             REQUIRE(rotShape->getWidth() == 4.0);
         }
     }

     SECTION("ScaledShape height and width") {
         {
             auto circle = makeCircle(6.0);
             auto scaledCircle = makeScaledShape(circle, 0.5, 0.5);
             INFO("Scaled Shape height");
             REQUIRE(scaledCircle->getHeight() == 6.0);
             INFO("Scaled Shape height");
             REQUIRE(scaledCircle->getWidth() == 6.0);
         }
     }

     SECTION("Vertical Shape height and width") {
         {
             auto circle = makeCircle(3.0);
             auto rectangle = makeRectangle(7.0, 7.0);
             auto square = makeSquare(8.0);
             auto vertical = makeVerticalShape({ circle, rectangle, square });
             INFO("Vertical Shape height");
             REQUIRE(vertical->getHeight() == 21.0);
             INFO("Vertical Shape width");
             REQUIRE(vertical->getWidth() == 8.0);
         }
     }

     SECTION("Horizontal Shape heigth and width") {
         {
             auto circle = makeCircle(3.0);
             auto rectangle = makeRectangle(7.0, 7.0);
             auto square = makeSquare(8.0);
             auto horizontal = makeHorizontalShape({ circle, rectangle, square });

             INFO("Horzontal Shape height");
             REQUIRE(horizontal->getHeight() == 8.0);
             INFO("Vertical Shape width");
             REQUIRE(horizontal->getWidth() == 21.0);
         }
     }
}
