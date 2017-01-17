/*
   Copyright (c) 2017, Christopher Nitta
   All rights reserved.

   All source code has been provided to University of California, Davis 
   students of course ECS 160 for educational purposes. It may not be 
   distributed beyond those enrolled in the course without prior permission 
   from the copyright holder.
   */

#include<cstdint>
#include<vector>
#include<queue>
#include<cstdio>


// Maps are oversized by 2 in each dimension to provide non-traversable border
// X =non-traversable border
// T =tree (non-traversable)
// Space =traversable path
std::vector<std::vector<char > > TestMap{
  {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
    {'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X'},
    {'X', ' ', 'T', 'T', 'T', ' ', ' ', 'X'},
    {'X', ' ', 'T', ' ', 'T', 'T', 'T', 'X'},
    {'X', ' ', 'T', 'T', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', 'T', 'T', 'T', ' ', 'X'},
    {'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}};

class CRouteFinder{
  public:
    enum class EDirection{
      North =0,
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
    bool IsTraversable(int x, int y){
      if(0 > x || y<0) return false;
      if(y+1 >= DMap.size()) return false;
      return ' ' == DMap[y][x];
    };		
  public:
    CRouteFinder(const std::vector<std::vector<char > > &map);
    void PrintMapWithCharacterAndDestination(int cx, int cy, int dx, int dy) const;
    EDirection FindRoute(int sx, int sy, int dx, int dy);
    void Move(EDirection dir, int &x, int &y);
};

int main(int argc, char *argv[]){
  CRouteFinder TestMapRouteFinder(TestMap);
  CRouteFinder::EDirection NextDir;
  int SX =3, SY =3, DX =5, DY =1;
  int Steps =0;

  printf("Step: %d\n", Steps);
  TestMapRouteFinder.PrintMapWithCharacterAndDestination(SX, SY, DX, DY);
  while(CRouteFinder::EDirection::Max !=(NextDir =TestMapRouteFinder.FindRoute(SX, SY, DX, DY))){
    TestMapRouteFinder.Move(NextDir, SX, SY);
    Steps++;
    printf("\nStep: %d ", Steps);
    switch(NextDir){
      case CRouteFinder::EDirection::North:   	printf("N\n");break;
      case CRouteFinder::EDirection::NorthEast:   printf("NE\n");break;
      case CRouteFinder::EDirection::East:      printf("E\n");break;
      case CRouteFinder::EDirection::SouthEast:   printf("SE\n");break;
      case CRouteFinder::EDirection::South:      printf("S\n");break;
      case CRouteFinder::EDirection::SouthWest:   printf("SW\n");break;
      case CRouteFinder::EDirection::West:   	printf("W\n");break;
      case CRouteFinder::EDirection::NorthWest:	printf("NW\n");break;
      default:break;
    }
    TestMapRouteFinder.PrintMapWithCharacterAndDestination(SX, SY, DX, DY);
  }
  if(SX ==DX &&(DY ==SY)){
    printf("Goal attained!\n");   
  }
  else{
    printf("No path exists!\n");   
  }
  return 0;
}


CRouteFinder::CRouteFinder(const std::vector<std::vector<char > > &map){
  DMap =map;
  DSearchMap.resize(DMap.size());
  for(int Index =0; Index<DSearchMap.size(); Index++){
    DSearchMap[Index].resize(DMap[Index].size());
  }
}

void CRouteFinder::PrintMapWithCharacterAndDestination(int cx, int cy, int dx, int dy) const
{
  for(int YPos =0; YPos<DMap.size();YPos++){
    for(int XPos=0;XPos<DMap[YPos].size();XPos++){
      if(YPos==cy+1&&XPos-1==cx)
        printf("+");
      else		
        if(YPos-1==dy&&dx+1==XPos){
          printf("d");
        }else
          printf("%c",DMap[YPos][XPos]);						
    }
    printf("\n");
  }
}

using SSearchTarget =struct{
  int DX;
  int DY;
  int Steps;
  int target_distance_squared;
  CRouteFinder::EDirection DInDirection;
};

int SquareDistance(int sx,  int dx, int sy, int dy){
  int DX =sx - dx, DY =sy - dy;
  return DX * DX + DY * DY;
}

CRouteFinder::EDirection CRouteFinder::FindRoute(int sx, int sy, int dx, int dy){
  const EDirection searchDirecitons[] ={EDirection::North,EDirection::East,EDirection::South,EDirection::West};
  const EDirection Ret_Dir[] ={EDirection::South,EDirection::West,EDirection::North,EDirection::East};
  EDirection dir_bef_last, LastInDirection;
  SSearchTarget current_search, BestSearch;
  const int lciMapXOffsets[] ={0,1,0,-1};
  const int lciMapYOffsets[] ={-1,0,1,0};               
  int DiagCheckXOffset[] ={0,1,1,1,0,-1,-1,-1};
  int DiagCheckYOffset[] ={-1,-1,0,1,1,1,0,-1};
  std::queue<SSearchTarget> Search_queue;


  for(auto &Row : DSearchMap){
    for(auto &Col : Row)
      Col =EDirection::Max;
  }
  if(!(IsTraversable(sx,sy)&&IsTraversable(dx,dy))){
    return EDirection::Max;      
  }

  current_search.DX =sx;
  current_search.DY =sy;
  current_search.Steps =0;
  current_search.target_distance_squared =SquareDistance(sx, dx,sy, dy);
  current_search.DInDirection =EDirection::Max;
  BestSearch =current_search;
  while(true){
    if(current_search.DY==dy&&dx==current_search.DX){
      BestSearch =current_search;
      break;
    }
    if(BestSearch.target_distance_squared > current_search.target_distance_squared){			BestSearch =current_search;				}
    for(int loop_index =0; loop_index<sizeof(searchDirecitons) / sizeof(EDirection); loop_index++){
      if(searchDirecitons[loop_index] !=current_search.DInDirection){
        int Search_X, SearchY;
        Search_X =current_search.DX + lciMapXOffsets[loop_index];
        SearchY =current_search.DY + lciMapYOffsets[loop_index];
        if(EDirection::Max ==DSearchMap[SearchY+1][Search_X+1] &&(IsTraversable(Search_X, SearchY))&&((Search_X !=sx)||sy !=SearchY)){
          SSearchTarget TempSearch;
          TempSearch.DX =Search_X;
          TempSearch.DY =SearchY;
          TempSearch.Steps =current_search.Steps + 1;
          TempSearch.target_distance_squared =SquareDistance(Search_X,dx, SearchY,dy);
          TempSearch.DInDirection =DSearchMap[SearchY+1][Search_X+1] =Ret_Dir[loop_index];
          Search_queue.push(TempSearch);
        }
      }
    }



    if(Search_queue.empty())                                                                                                                                                                                                                                                                                               break;   
    current_search =Search_queue.front();
    Search_queue.pop();
  }
  dir_bef_last =LastInDirection =BestSearch.DInDirection;
  current_search =BestSearch;
  while(DSearchMap[current_search.DY+1][current_search.DX+1] !=EDirection::Max){
    int loop_index;
    for(loop_index =0; loop_index<sizeof(searchDirecitons) / sizeof(EDirection); loop_index++)
      if(DSearchMap[current_search.DY+1][current_search.DX+1] ==searchDirecitons[loop_index]) break;


    dir_bef_last =LastInDirection;
    LastInDirection =DSearchMap[current_search.DY+1][current_search.DX+1];

    current_search.DX +=lciMapXOffsets[loop_index];
    current_search.DY +=lciMapYOffsets[loop_index];
  }

  if(dir_bef_last !=LastInDirection){
    EDirection FirstDirection, SecondDirection;
    for(int loop_index =0; loop_index<sizeof(searchDirecitons) / sizeof(EDirection); loop_index++){
      if(LastInDirection ==searchDirecitons[loop_index]){
        FirstDirection =Ret_Dir[loop_index];   
      }
      if(dir_bef_last ==searchDirecitons[loop_index]){
        SecondDirection =Ret_Dir[loop_index];   
      }
    }
    int Sum =static_cast<int>(FirstDirection) + static_cast<int>(SecondDirection);
    if((6 ==Sum)&&((EDirection::North !=FirstDirection) || (EDirection::North !=SecondDirection))){ // NW wrap around
      Sum +=8;}
    Sum /=2;
    return static_cast<EDirection>(Sum);}

  for(int loop_index =0; loop_index<sizeof(searchDirecitons) / sizeof(EDirection); loop_index++)
  {
    if(LastInDirection ==searchDirecitons[loop_index])
    {
      return Ret_Dir[loop_index];
    }
  }

  return EDirection::Max;
}

void CRouteFinder::Move(EDirection dir, int &x, int &y){
  EDirection MoveDirecitons[] ={EDirection::North,EDirection::NorthEast,EDirection::East,EDirection::SouthEast,EDirection::South,EDirection::SouthWest,EDirection::West,EDirection::NorthWest};
  const int xOffset[] ={0,1,1,1,0,-1,-1,-1};
  const int YOffset[] ={-1,-1,0,1,1,1,0,-1};

  for(int Index =0; Index<sizeof(MoveDirecitons)/sizeof(EDirection); Index++)                                                                                                                                                                          if(dir ==  MoveDirecitons[Index]){
    x +=   xOffset[Index];
    y+=YOffset[Index];
    return;
  }

}
