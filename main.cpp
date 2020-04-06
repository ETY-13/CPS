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
    auto rect = makeRectangle(20, 20);
    auto tria = makeTriangle(45);
    auto triaRot = makeRotatedShape(tria,Angle::R270);
    auto triaScal = makeScaledShape(tria,5.0,10.0);
    os << "% circle\n";
    circle->generatePostScript(os);
    os << "% polygon\n";
    poly->generatePostScript(os);
    os << "% polygon 2\n";
    poly2->generatePostScript(os);
    os << "% polygon 3\n";
    poly3->generatePostScript(os);
    os << "%rectangle\n";
    rect->generatePostScript(os);
    os << "%triangle\n";
    tria->generatePostScript(os);
    os << "%Rotated triangle\n";
    triaRot->generatePostScript(os);
    os << "%Scaled triangle\n";
    triaScal->generatePostScript(os);
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
