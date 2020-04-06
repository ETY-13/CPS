// Main file for test suite

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_RUNNER
#include"catch.hpp"
#include"CPS.hpp"

#include<iostream>
using std::cout;
using std::endl;
using std::ostream;

#include<fstream>
using std::filebuf;

#include<iostream>
using std::ios;

// out put shape to file 
void getShapetoFile() {
    filebuf outfile;
    outfile.open("shape.ps", ios::out);
    auto center = inCenter();
    ostream os(&outfile);
    auto cirlce = makeCircle(4);
    auto poly = makePolygon(8, 10);
    auto rect = makeRectangle(20, 20);
    auto sqaure = makeSquare(40);
    auto triangle = makeTriangle(40);
    auto roshape = makeRotatedShape(triangle, Angle::R270);
    auto scaleShape = makeScaledShape(triangle,2.0, 2.0);
    auto layer = makeLayeredShape({ sqaure,triangle,poly });
    auto vertical = makeVerticalShape({ poly, rect, sqaure });

    os << "% circle\n"<<center;
    cirlce->generatePostScript(os);
    os << show();
    os << "% polygon\n" << center;;
    poly->generatePostScript(os);
    os << show();
    os << "%rectangle\n" << center;;
    rect->generatePostScript(os);
    os << show();
    os << "%sqaure\n" << center;;
    sqaure->generatePostScript(os);
    os << show();
    os << "%triangle\n" << center;;
    triangle->generatePostScript(os);
    os << show();
    os << "%rotatedShape\n" << center;
    roshape->generatePostScript(os);
    os << show();
    os << "%scaleShape\n" << center;
    scaleShape->generatePostScript(os);
    os << show();
    os << "%layeredShaped\n" << center;
    layer->generatePostScript(os);
    os << show();
    os << "%verticalShape\n";
    vertical->generatePostScript(os);
    os << show();

    std::string stuff;

    outfile.close();
   


}

int main(int argc, char* argv[]) {

    Catch::Session session;  
    int result;         

    result = session.applyCommandLine(argc, argv);

    if (result !=0){
        return result;
    }
    
    result = session.run();
   
    getShapetoFile();

    return result;
}