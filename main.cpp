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
    auto cirlce = makeCircle(4);
    auto poly = makePolygon(6, 10);
    os << "% circle\n";
    cirlce->generatePostScript(os);
    os << "% polygon\n";
    poly->generatePostScript(os);
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