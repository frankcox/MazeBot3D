// =====================================================================================
// 
//        Version:  3.0a
//        Created:  6/2/2012 12:53:00 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Frank L Cox, frank.l.cox@gmail.com 
// 
//    Description: Third cut at a Maze Bot class. See file README for description
//    of problem.
//
//    Constructor takes a file name for the map .dat file. It returns an object with
//    an initialized playground, start, and end points, and hight, width, depth
//
//    playgrond is a 3D vector of sturct's of type Node. [0, 0, 0] is the bottom, 
//    left, back corner. Node's are used to keep track of things the bot discovers
//    while exploring, like path length to this Node and a pointer back to the last
//    Node in that path. Also, if the node is solid and if it's been "visited". 
//
//    Node's are initialized to:
//    - solid: true or not, depending on the map, 
//    - pathLength: MAX_INT ("infinite"), 
//    - fromPoint: 0,0,0 (except for end which is -1,-1,-1 (so printPath will know if 
//    it's escapable, but visited probably would have worked...)
//    - visited: false
//
//    
//
// =====================================================================================

#ifndef MAZEBOT_H
#define MAZEBOT_H

#include <vector>
#include <list>


namespace us_munging_cpp {

    class MazeBot {
        private:
            int mb_height, mb_width, mb_depth, round;
            static const int MAX_INT; // "infinity"
            struct Point {int x; int y; int z;} start, end;
            struct Node {
                bool solid;
                int pathLength;
                Point fromPoint;
                bool visited;
            };
            std::vector< std::vector< std::vector<Node> > > playground;
            std::list<Point> toExplore;
            void findMazeSize(const char *filename);
            void checkNode(const Point &from, const Point &to);
            int getPathLength(const Point &point);
            void setVisited(const Point &p);
            void jsonMap();
            bool createJSON;

        public:
            friend class MazeBotJSON;
            MazeBot(const char *filename);
            void escape();
            void printPath();
            void setJSON();
            
            // debug and test methods
            void printList();
            void show();
            void showPoint(std::string name, const MazeBot::Point &p);
    };

};

#include "mazeBot.cpp"

#endif
