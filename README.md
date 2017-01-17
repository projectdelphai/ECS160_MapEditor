# ECS160Tools

## Map files

Map files are to be stored in /bin/data/map, with file extension .map .
The file structure is as follows:
- Mapname
- Xsize Ysize
- Map ASCII
	* Note: Each letter corresponds to a tile (/src/TerrainMap.cpp)
	```
	case 'G':   DMap[Index][Inner] = ETileType::ttGrass;
                                break;
                    case 'F':   DMap[Index][Inner] = ETileType::ttTree;
                                break;
                    case 'D':   DMap[Index][Inner] = ETileType::ttDirt;
                                break;
                    case 'W':   DMap[Index][Inner] = ETileType::ttWall;
                                break;
                    case 'w':   DMap[Index][Inner] = ETileType::ttWallDamaged;
                                break;
                    case 'R':   DMap[Index][Inner] = ETileType::ttRock;
                                break;
                    case ' ':   DMap[Index][Inner] = ETileType::ttWater;
                                break;
  ```