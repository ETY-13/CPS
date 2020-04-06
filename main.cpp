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
    
    ostream os(&outfile);
    auto circle = makeCircle(4);
    auto poly = makePolygon(6, 50);
    auto poly2 = makePolygon(8, 75.5);
    auto poly3 = makePolygon(5, 50);
    auto rect = makeRectangle(40, 50);
    auto sqaure = makeSquare(50);
    auto triangle = makeTriangle(50);
    auto roshape = makeRotatedShape(triangle, Angle::R270);
    auto scaleShape = makeScaledShape(triangle,2.0, 2.0);
    auto layer = makeLayeredShape({ sqaure,triangle,rect });
    auto vertical = makeVerticalShape({ poly, rect, sqaure });
    auto horizontal = makeHorizontalShape({ poly,rect,sqaure });
    auto arc = makeArcShape({ poly,rect,sqaure }, Angle::R180, 20.0);
    auto center = inCenter();
    os << "% circle\n"<<center;
    circle->generatePostScript(os);
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
    os << "%verticalShape\n" << center;
    vertical->generatePostScript(os);
    os << show();
    os << "%horon\n" << center;
    horizontal->generatePostScript(os);
    os << show();
    os << "%arc\n";
    arc->generatePostScript(os);
    os << show();
   


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
