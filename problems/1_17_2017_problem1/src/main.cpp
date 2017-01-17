/*
   Copyright (c) 2017, Christopher Nitta
   All rights reserved.

   All source code has been provided to University of California, Davis
   students of course ECS 160 for educational purposes. It may not be
   distributed beyond those enrolled in the course without prior permission
   from the copyright holder.
 */
#include "findroute.h"

// Maps are oversized by 2 in each dimension to provide non-traversable border
// X =non-traversable border
// T =tree (non-traversable)
// Space =traversable path
std::vector<std::vector<char > > TestMap {
    { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
    { 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X' },
    { 'X', ' ', 'T', 'T', 'T', ' ', ' ', 'X' },
    { 'X', ' ', 'T', ' ', 'T', 'T', 'T', 'X' },
    { 'X', ' ', 'T', 'T', ' ', ' ', ' ', 'X' },
    { 'X', ' ', ' ', 'T', 'T', 'T', ' ', 'X' },
    { 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X' },
    { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
};

int main(int argc, char *argv[]){
    CRouteFinder TestMapRouteFinder(TestMap);
    CRouteFinder::EDirection NextDir;
    int SX = 3, SY = 3, DX = 5, DY = 1;
    int Steps = 0;

    printf("Step: %d\n", Steps);
    TestMapRouteFinder.PrintMapWithCharacterAndDestination(SX, SY, DX, DY);
    while(CRouteFinder::EDirection::Max != (NextDir = TestMapRouteFinder.FindRoute(SX, SY, DX, DY))){
        TestMapRouteFinder.Move(NextDir, SX, SY);
        Steps++;
        printf("\nStep: %d ", Steps);
        switch (NextDir){
            case CRouteFinder::EDirection::North:       printf("N\n"); 
                                                        break;
            case CRouteFinder::EDirection::NorthEast:   printf("NE\n"); 
                                                        break;
            case CRouteFinder::EDirection::East:        printf("E\n"); 
                                                        break;
            case CRouteFinder::EDirection::SouthEast:   printf("SE\n"); 
                                                        break;
            case CRouteFinder::EDirection::South:       printf("S\n"); 
                                                        break;
            case CRouteFinder::EDirection::SouthWest:   printf("SW\n"); 
                                                        break;
            case CRouteFinder::EDirection::West:        printf("W\n"); 
                                                        break;
            case CRouteFinder::EDirection::NorthWest:   printf("NW\n"); 
                                                        break;
            default: break;
        }
        TestMapRouteFinder.PrintMapWithCharacterAndDestination(SX, SY, DX, DY);
    }
    if((SX == DX) && (SY == DY)){
        printf("Goal attained!\n");
    }
    else{
        printf("No path exists!\n");
    }
    return 0;
}
