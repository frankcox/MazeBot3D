// =====================================================================================
// 
//    Author       : Frank Lyon Cox - frank.l.cox@gmail.com
//    Date Created : 6/2/2012
//
//    Description  : 
//
//    Version      : 1.0
//    Revision     : none
//    Compiler     : g++
//
// 
// =====================================================================================


#include <iostream>
#include "mazeBot.h"

using namespace us_munging_cpp;
using namespace std;

int main() {
    MazeBot mb = MazeBot("maze.dat");
//  mb.show();
    mb.escape();
    mb.printPath();
}
