// =====================================================================================
// 
// 
//        Version:  1.0
//        Created:  7/12/2012 6:04:20 PM
//       Revision:  none
//       Compiler:  g++
//         Author:  YOUR NAME (flc), frank.l.cox@gmail.com
//
//    Description:  
// 
// =====================================================================================

#ifndef MAZEBOTJSON_H
#define MAZEBOTJSON_H

#include <vector>

namespace us_munging_cpp {


    class MazeBotJSON {
        private: 
            struct Point {int x; int y; int z;} start, end;
            struct change {
                Point node;
                int pathLength;
                Point fromPoint;
                bool visited;
            };
            std::vector<change> moves;

        public:
            void jsonMap(const MazeBot &mb);
    
    };

    
    void MazeBotJSON::jsonMap(const MazeBot &mb) {
        std::ofstream jfile;
        jfile.open("game.json", std::ios::out);

        if (jfile.is_open()) {
            jfile << "{ \"start\":[" << mb.start.x << "," << mb.start.y << "," << mb.start.z << "]," << std::endl;
            jfile << "\"end\":[" << mb.end.x << "," << mb.end.y << "," << mb.end.z << "]," << std::endl;
            jfile << "\"mb_height\":" << mb.mb_height << "," << std::endl;
            jfile << "\"mb_width\":" << mb.mb_width << "," << std::endl;
            jfile << "\"mb_depth\":" << mb.mb_depth << "," << std::endl;

            jfile << "\"map\":[" << std::endl;
            for (int d = 0; d < mb.mb_depth; d++) {
                jfile << "  [" << std::endl;
                for (int h = 0; h < mb.mb_height; h++) {
                    jfile << "    [ ";
                    for (int w = 0; w < mb.mb_width; w++) {
                        jfile << "[{" << "\"solid\":";
                        mb.playground[d][h][w].solid ? jfile << "true" : jfile << "false";
                        jfile << ",\"pathLength\":"; 
                        (mb.playground[d][h][w].pathLength == mb.MAX_INT) ? jfile<<"\"inf\"" 
                                                                    : jfile<<mb.playground[d][h][w].pathLength;
                        jfile << ",\"fromPoint\":";
                        jfile << "[" << mb.playground[d][h][w].fromPoint.x 
                                  << "," << mb.playground[d][h][w].fromPoint.y 
                                  << "," << mb.playground[d][h][w].fromPoint.z << "]";
                        jfile << ",\"visited\":"; 
                        mb.playground[d][h][w].visited ? jfile << "true" : jfile << "false";
                        (w < mb.mb_width -1) ? jfile << "}]," : jfile << "}]";
                    }

                    (h < mb.mb_height -1) ? jfile << " ],"<< std::endl : jfile << " ]" << std::endl;
                }

               (d < mb.mb_depth -1) ?  jfile << "  ]," << std::endl :  jfile << "  ]" << std::endl;
            }
            jfile << "]" << std::endl;

            jfile.close();
        }
    }
};


#endif    
