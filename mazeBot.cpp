// =====================================================================================
// 
//    Author       : Frank Lyon Cox - frank.l.cox@gmail.com - All rights reserved
//    Date Created : 6/2/2012
//
//    Description  : A third cut at implementing a single class Maze Bot. 
//
//            escape() is inspired by Dijstra's algorithm except the edges are not
//            known at the start. Nodes are discovered by exploring and all edges are 
//            length 1. For each node with the shortest path, starting with 'start', 
//            examen all reachable, unvisited, adjacent nodes. Assign a tentative
//            'pathLength' one more than the current pathLength of the examining node, 
//            and set 'fromPoint'. If the node already has a shorter pathLength though, we 
//            leave it. Then add the examined node point to the toExplore list
//            and set the current node 'visited'. When visited is set also remove any other
//            listings of the current node point from toExplore. For the next round take 
//            the shortest path length point from toExplore and repeat.
//
//            If we are examining the end point we are done and can escape. Since we 
//            always explore the shortest path, we can just follow the fromPoint's back to
//            start to have the shortest path. If toExplore is empty we are stuck.
//
//            
//
//    Version      : 3.0a
//    Revision     : none
//    Compiler     : g++
//
// 
// =====================================================================================


#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <assert.h>
#include <limits>
#include "mazeBot.h"

namespace us_munging_cpp {

    const int MazeBot::MAX_INT = std::numeric_limits<int>::max();
    const bool DEBUG = false;





    MazeBot::MazeBot(const char *filename) {
        findMazeSize(filename);

        std::string line;
        std::ifstream in;
        in.open(filename);
        assert(in != NULL);
        getline(in, line);

        start.x = -1; start.y = -1;
        end.x = -1; end.y = -1;

        playground.resize(mb_depth);
        for (int d = 0; d < mb_depth; d++) {
            playground[d].resize(mb_height);
            for (int h = 0; h < mb_height; h++) {
                getline(in, line);
                // all data lines must be the same length with one space between levels
                assert(line.length() == mb_width +1);
                playground[d][h].resize(mb_width);
                if (DEBUG) std::cout << line << std::endl;
                for (int w = 0; w < mb_width; w++) {
                    playground[d][h][w].pathLength = MAX_INT;

                    playground[d][h][w].solid = (line[w] == '#') ? true : false;                     
                    if (line[w] == 'B') { 
                        start.x = w; 
                        start.y = h; 
                        start.z = d;
                        playground[d][h][w].pathLength = 0;
                    }
                    if (line[w] == 'E') { 
                        end.x = w; 
                        end.y = h; 
                        end.z = d;
                        playground[d][h][w].fromPoint.x = -1;
                        playground[d][h][w].fromPoint.y = -1;
                        playground[d][h][w].fromPoint.z = -1;
                        playground[d][h][w].visited = false;
                    }
                    else {
                        playground[d][h][w].fromPoint.x = 0;
                        playground[d][h][w].fromPoint.y = 0;
                        playground[d][h][w].fromPoint.z = 0;
                        playground[d][h][w].visited = false;
                    }
                }
            }
            getline(in, line);
        }
        in.close();    
        // start and end must be set (changed from default -1)
        assert (start.x >= 0);
        assert (end.x >= 0);
        if (DEBUG) showPoint("start", start);
        if (DEBUG) showPoint("end", end);
    }







    void MazeBot::findMazeSize(const char *filename) {
        char nextChar;
        std::string line;
        std::string::iterator it;
        int height, width, depth;

        std::ifstream in;
        in.open(filename);
        assert(in != NULL);

        getline(in, line);
        assert(line.length() >= 2);
        std::stringstream strStream(line);
        strStream >> depth;
        if (DEBUG) std::cout << "depth: " << depth << std::endl;

        getline(in, line);
        width = line.length() -1;
        if (DEBUG) std::cout << "width: " << width << std::endl;

        height = 0;
        while (! in.eof() and line.length() > 1) {
            // data lines are all the same length
            assert(line.length() == width +1);
            getline(in, line);
            height++;
        }
        if (DEBUG) std::cout << "height: " << height << std::endl;
        in.close();    

        mb_depth = depth;
        mb_height = height;
        mb_width = width;
    }





    // Inspired by Dijstra but all paths are not know at the start. 
    // Uses checkNode() and setVisited()
    void MazeBot::escape() {
        Point thisPoint, toPoint;
        thisPoint = start;
        bool done = false, foundOne = false;
        int round = 1;
        std::vector<Point>::iterator it;


        while (not done) {
            if (DEBUG) {std::cout << std::endl << round++ <<"))))) "; showPoint("thisPoint", thisPoint); }

            // find closest unvisited to thisPoint (look N S E W U D)
            // North
            toPoint.x = thisPoint.x;  toPoint.y = thisPoint.y -1;  toPoint.z = thisPoint.z;
            checkNode(thisPoint, toPoint);

            // South
            toPoint.x = thisPoint.x;  toPoint.y = thisPoint.y +1;  toPoint.z = thisPoint.z;
            checkNode(thisPoint, toPoint);
            
            // East
            toPoint.x = thisPoint.x +1;  toPoint.y = thisPoint.y; toPoint.z = thisPoint.z;
            checkNode(thisPoint, toPoint);
            
            // West
            toPoint.x = thisPoint.x -1;  toPoint.y = thisPoint.y;  toPoint.z = thisPoint.z;
            checkNode(thisPoint, toPoint);

            // Up
            toPoint.x = thisPoint.x;  toPoint.y = thisPoint.y;  toPoint.z = thisPoint.z +1;
            checkNode(thisPoint, toPoint);

            // Down
            toPoint.x = thisPoint.x;  toPoint.y = thisPoint.y;  toPoint.z = thisPoint.z -1;
            checkNode(thisPoint, toPoint);

            setVisited(thisPoint);

            // Now, check if we have exit, if not, then...
            // Take the shortest from toExplore (head(), since it's sorted)
            // If toExplore is empty we are done -- and probably stuck

            if (thisPoint.x == end.x and thisPoint.y == end.y and thisPoint.y == end.y 
                and playground[end.z][end.y][end.x].visited) {

                done = true;
            }
            else {
                if (not toExplore.empty()) {
                    thisPoint = toExplore.front();
                    toExplore.pop_front();
                }
                else {
                    done = true;
                }
            }

            if (DEBUG) show();
            if (DEBUG) printList();
        }

    }
    
    
    
    
    
    
    void MazeBot::checkNode(const Point &from, const Point &to) {

        if (to.x >= 0 and to.y >= 0 and to.z >= 0 and to.x < mb_width and to.y < mb_height and to.z < mb_depth
            and not playground[to.z][to.y][to.x].solid and not playground[to.z][to.y][to.x].visited)  {

            if (getPathLength(to) > getPathLength(to) +1) {
                playground[to.z][to.y][to.x].pathLength = getPathLength(from) +1;
                playground[to.z][to.y][to.x].fromPoint = from;
            }

            // put in list in sorted order...
            if ( toExplore.empty() or getPathLength(to) >= getPathLength(toExplore.back()) ) {
                toExplore.push_back(to);
            }
            else {
                for (std::list<Point>::iterator it = toExplore.begin(); it != toExplore.end(); it++) {
                    if (getPathLength(*it) < getPathLength(to)) {
                        it = toExplore.insert(it, to);
                        break;
                    }
                }
            }
        }
    }






    void MazeBot::setVisited(const Point &p) {
        // set this node visited and erase all references to this point in toExplore
        playground[p.z][p.y][p.x].visited = true;
        for (std::list<Point>::iterator it = toExplore.begin(); it != toExplore.end(); it++) {
            if (p.x == it->x and p.y == it->y and p.z == it->z) {
                it = toExplore.erase(it);
            }
        }
    }





    int MazeBot::getPathLength(const Point &p) {
        return MazeBot::playground[p.z][p.y][p.x].pathLength;
    }






    void MazeBot::printPath() {
        std::stack<Point> path;
        Point thisPoint, nextPoint;
        char move;

        if (playground[end.z][end.y][end.x].fromPoint.x == -1) {
            std::cout << "Not Escapable" << std::endl;
        }
        else {
            std::cout << "Escapable ";

            thisPoint = end;
            while (not (thisPoint.x == start.x and thisPoint.y == start.y and thisPoint.z == start.z) ) {
                path.push(thisPoint);
                thisPoint = playground[thisPoint.z][thisPoint.y][thisPoint.x].fromPoint;
            }
            path.push(thisPoint);

            while (not path.empty()) {
                thisPoint = path.top();
                path.pop();
                if (path.empty()) break;
                nextPoint = path.top();

                if      ((nextPoint.y == thisPoint.y -1) and (nextPoint.x == thisPoint.x) and (nextPoint.z == thisPoint.z)) {move = 'N';}
                else if ((nextPoint.y == thisPoint.y +1) and (nextPoint.x == thisPoint.x) and (nextPoint.z == thisPoint.z)) {move = 'S';}
                else if ((nextPoint.y == thisPoint.y) and (nextPoint.x == thisPoint.x +1) and (nextPoint.z == thisPoint.z)) {move = 'E';}
                else if ((nextPoint.y == thisPoint.y) and (nextPoint.x == thisPoint.x -1) and (nextPoint.z == thisPoint.z)) {move = 'W';}
                else if ((nextPoint.y == thisPoint.y) and (nextPoint.x == thisPoint.x) and (nextPoint.z == thisPoint.z +1)) {move = 'U';}
                else if ((nextPoint.y == thisPoint.y) and (nextPoint.x == thisPoint.x) and (nextPoint.z == thisPoint.z -1)) {move = 'D';}
                std::cout << move;
            }
        }
    }






    void MazeBot::printList() {
        std::list<Point>::iterator it;
        std::cout << "PRINT List:::::: " << std::endl;
        if (not toExplore.empty()) {
            for (it = toExplore.begin(); it != toExplore.end(); it++) {
                showPoint("toExplore", *it);
            }
        }
        else {
            std::cout << "EMPTY" << std::endl;
        }
    }






    void MazeBot::show() {
        for (int d = 0; d < mb_depth; d++) {
            for (int h = 0; h < mb_height; h++) {
                for (int w = 0; w < mb_width; w++) {
                    std::cout << "[";
                    std::cout << playground[d][h][w].solid << ", ";
                    if (playground[d][h][w].pathLength == MAX_INT) {
                        std::cout << "inf, ";
                    }
                    else {
                        printf ("%3d, ", playground[d][h][w].pathLength);
                    }
                    std::cout << "("  << playground[d][h][w].fromPoint.x;
                    std::cout << ", " << playground[d][h][w].fromPoint.y;
                    std::cout << ", " << playground[d][h][w].fromPoint.z <<  "), ";
                    std::cout << playground[d][h][w].visited << "] ";
                }
                std::cout << std::endl;
            }        
            std::cout << std::endl << std::endl;
        }
    }





    void MazeBot::showPoint(std::string name, const Point &p) {
        std::cout << name << "[" << p.x << ", " << p.y << ", " << p.z << "]" << std::endl;
    }



};
