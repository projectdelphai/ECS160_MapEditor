/*
   Copyright (c) 2017, Christopher Nitta
   All rights reserved.

   All source code has been provided to University of California, Davis
   students of course ECS 160 for educational purposes. It may not be
   distributed beyond those enrolled in the course without prior permission
   from the copyright holder.
 */
#ifndef FINDROUTE_H
#define FINDROUTE_H
#include <cstdint>
#include <vector>
#include <queue>
#include <cstdio>


class CRouteFinder{
    public:
        enum class EDirection { North =0,
                                NorthEast,
                                East,     
                                SouthEast,
                                South,
                                SouthWest,   
                                West,
                                NorthWest,
                                Max 
                            };
    protected:
        std::vector<std::vector<char > > DMap;
        std::vector<std::vector<EDirection > > DSearchMap;

    public:
        CRouteFinder(const std::vector<std::vector<char > > &map);

        bool IsTraversable(int x, int y){
            if((0 > x) || (0 > y)){
                return false;
            }
            if(y + 1 >= DMap.size()){
                return false;
            }
            return ' ' == DMap[x+1][y+1];
        };
        
        void PrintMapWithCharacterAndDestination(int cx, int cy, int dx, int dy) const;
        EDirection FindRoute(int sx, int sy, int dx, int dy);
        void Move(EDirection dir, int &x, int &y);

};

#endif
