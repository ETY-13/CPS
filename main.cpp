// Main file for test suite

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_RUNNER
#include"catch.hpp"

#include<iostream>
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    Catch::Session session;  
    int result;         

    result = session.applyCommandLine(argc, argv);

    if (result !=0){
        return result;
    }

    result = session.run();
   
    return result;
}