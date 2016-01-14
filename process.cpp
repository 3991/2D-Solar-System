#include "process.h"

Process::Process(){
}

Process::~Process(){

}

float Process::translateKmInPixel(float nb){
    //400px=6378km
    return nb/15;
}
