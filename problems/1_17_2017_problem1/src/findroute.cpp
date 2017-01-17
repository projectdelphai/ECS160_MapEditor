/*
   Copyright (c) 2017, Christopher Nitta
   All rights reserved.

   All source code has been provided to University of California, Davis
   students of course ECS 160 for educational purposes. It may not be
   distributed beyond those enrolled in the course without prior permission
   from the copyright holder.
 */
#include "findroute.h"

CRouteFinder::CRouteFinder(const std::vector<std::vector<char > > &map){
    DMap = map;
    DSearchMap.resize(DMap.size());
    for(int Index = 0; Index < DSearchMap.size(); Index++){
        DSearchMap[Index].resize(DMap[Index].size());
    }
}

void CRouteFinder::PrintMapWithCharacterAndDestination(int cx, int cy, int dx, int dy) const{
    for(int YPos = 0; YPos < (int)DMap.size(); YPos++){
        for(int XPos = 0; XPos < (int)DMap[YPos].size(); XPos++){
            if((cx + 1 == XPos) && (cy + 1 == YPos)) {
                printf("+");
            }
            else if((dx + 1 == XPos) && (dy + 1 == YPos)) {
                printf("d");
            }
            else{
                printf("%c", DMap[YPos][XPos]);
            }
        }
        printf("\n");
    }
}

using SSearchTarget = struct {
    int DX;
    int DY;
    int Steps;
    int target_distance_squared;
    CRouteFinder::EDirection DInDirection;
};

int SquareDistance(int sx,  int dx, int sy, int dy){
    int DX = sx - dx, DY = sy - dy;

    return DX * DX + DY * DY;
}

CRouteFinder::EDirection CRouteFinder::FindRoute(int sx, int sy, int dx, int dy){
    const EDirection SearchDirecitons[] = { EDirection::North, EDirection::East, EDirection::South, EDirection::West };
    const EDirection ReturnDirection[] = { EDirection::South, EDirection::West, EDirection::North, EDirection::East };
    EDirection DirectionBeforeLast, LastInDirection;
    SSearchTarget CurrentSearch, BestSearch;
    const int MapXOffsets[] = { 0, 1, 0, -1 };
    const int MapYOffsets[] = { -1, 0, 1, 0 };
    int DiagCheckXOffset[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int DiagCheckYOffset[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    std::queue<SSearchTarget> SearchQueue;


    for(auto &Row : DSearchMap){
        for(auto &Col : Row){
            Col = EDirection::Max;
        }
    }
    if(!(IsTraversable(sx, sy) && IsTraversable(dx, dy))){
        return EDirection::Max;
    }

    CurrentSearch.DX = sx;
    CurrentSearch.DY = sy;
    CurrentSearch.Steps = 0;
    CurrentSearch.target_distance_squared = SquareDistance(sx, dx, sy, dy);
    CurrentSearch.DInDirection = EDirection::Max;
    BestSearch = CurrentSearch;
    while(true){
        if((CurrentSearch.DY == dy) && (CurrentSearch.DX == dx)){
            BestSearch = CurrentSearch;
            break;
        }
        if(BestSearch.target_distance_squared > CurrentSearch.target_distance_squared){
            BestSearch = CurrentSearch;
        }
        for(int LoopIndex = 0; LoopIndex < sizeof(SearchDirecitons) / sizeof(EDirection); LoopIndex++) {
            if (SearchDirecitons[LoopIndex] != CurrentSearch.DInDirection) {
                int SearchX, SearchY;
                SearchX = CurrentSearch.DX + MapXOffsets[LoopIndex];
                SearchY = CurrentSearch.DY + MapYOffsets[LoopIndex];
                if(EDirection::Max == DSearchMap[SearchY + 1][SearchX + 1] && (IsTraversable(SearchX, SearchY)) && ((SearchX != sx) || (SearchY != sy))) {
                    SSearchTarget TempSearch;
                    TempSearch.DX = SearchX;
                    TempSearch.DY = SearchY;
                    TempSearch.Steps = CurrentSearch.Steps + 1;
                    TempSearch.target_distance_squared = SquareDistance(SearchX, dx, SearchY, dy);
                    TempSearch.DInDirection = DSearchMap[SearchY + 1][SearchX + 1] = ReturnDirection[LoopIndex];
                    SearchQueue.push(TempSearch);
                }
            }
        }

        if(SearchQueue.empty()){
            break;
        }
        CurrentSearch = SearchQueue.front();
        SearchQueue.pop();
    }
    DirectionBeforeLast = LastInDirection = BestSearch.DInDirection;
    CurrentSearch = BestSearch;
    while(DSearchMap[CurrentSearch.DY + 1][CurrentSearch.DX + 1] != EDirection::Max){
        int LoopIndex;
        for(LoopIndex = 0; LoopIndex < sizeof(SearchDirecitons) / sizeof(EDirection); LoopIndex++){
            if(DSearchMap[CurrentSearch.DY + 1][CurrentSearch.DX + 1] == SearchDirecitons[LoopIndex]){
                break;
            }
        }


        DirectionBeforeLast = LastInDirection;
        LastInDirection = DSearchMap[CurrentSearch.DY + 1][CurrentSearch.DX + 1];

        CurrentSearch.DX += MapXOffsets[LoopIndex];
        CurrentSearch.DY += MapYOffsets[LoopIndex];
    }

    if(DirectionBeforeLast != LastInDirection){
        EDirection FirstDirection, SecondDirection;
        for(int LoopIndex = 0; LoopIndex < sizeof(SearchDirecitons) / sizeof(EDirection); LoopIndex++){
            if(LastInDirection == SearchDirecitons[LoopIndex]){
                FirstDirection = ReturnDirection[LoopIndex];
            }
            if(DirectionBeforeLast == SearchDirecitons[LoopIndex]){
                SecondDirection = ReturnDirection[LoopIndex];
            }
        }
        int Sum = static_cast<int>(FirstDirection) + static_cast<int>(SecondDirection);
        if((6 == Sum) && ((EDirection::North != FirstDirection) || (EDirection::North != SecondDirection))){ // NW wrap around
            Sum += 8;
        }
        Sum /= 2;
        return static_cast<EDirection>(Sum);
    }

    for(int LoopIndex = 0; LoopIndex < sizeof(SearchDirecitons) / sizeof(EDirection); LoopIndex++){
        if(LastInDirection == SearchDirecitons[LoopIndex]){
            return ReturnDirection[LoopIndex];
        }
    }

    return EDirection::Max;
}

void CRouteFinder::Move(EDirection dir, int &x, int &y){
    EDirection MoveDirecitons[] = { EDirection::North, EDirection::NorthEast, EDirection::East, EDirection::SouthEast, EDirection::South, EDirection::SouthWest, EDirection::West, EDirection::NorthWest };
    const int XOffset[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    const int YOffset[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

    for(int Index = 0; Index < sizeof(MoveDirecitons) / sizeof(EDirection); Index++){
        if(dir == MoveDirecitons[Index]){
            x += XOffset[Index];
            y += YOffset[Index];
            return;
        }
    }

}
