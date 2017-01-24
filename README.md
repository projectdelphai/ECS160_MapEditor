# ECS160Tools
Change by Beshoy
## Map files

Map files are to be stored in /bin/data/map, with file extension .map .
The file structure is as follows:
- Mapname
- Xsize Ysize
- Map ASCII
	* Note: Each letter corresponds to a tile, and there must be a one-unit border around the entire mapset (so 96x64 needs 98x66 characters)
	```
	# from /src/TerrainMap.cpp
	case 'G':   Grass;
  case 'F':   Tree;
  case 'D':   Dirt;
  case 'W':   Wall;    
  case 'w':   WallDamaged;
  case 'R':   Rock;
  case ' ':   Water;
  ```
- Number of players
- Resource values
	* Global Cap:  
	`0 30000 500 ==> Maximum any player can have is 30000 gold, 500 lumber`
	* PlayerNum GoldStarting LumberStarting  
	`1 1000 0 => player 1 starts with 1000 gold, 0 lumber`
- Number of units to render (should match number of lines below)
- Buildings and Units
	* `Name PlayerNum X Y`
	* 0 for neutral
	```
	# more unit names TBA 
	GoldMine 0 1 12 
	GoldMine 0 92 49 
	Peasant 1 3 4
	TownHall 1 3 5
	Peasant 2 94 59    
	TownHall 2 92 54
	```
- 2 empty new lines (not sure if necessary, but all the .map files have them)  

# Code Example (with comments)
```
North-South Divide  	// map name in map selection screen
96 64   		// Xsize Ysize
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
GFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFG
GFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFG
GFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFG
GFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFG
GGGGGGGGGGGGGGGGGGFFFFFFFGGGGGGGGGGGGGGGGGGGGGGGGFFFFFFFFFGGGGGGGGGGGGGGGGGGFFFFFFFFGGGGGGGGGGGDRR
GGGGGGGGGGGGGGGGGGGGGFFFGGGGGGGGGGGGGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGDRR
GGGGGGGGGGGGGGGGGGGGGFFFGGGGGGGGGGGGGGGGGGGGGGGGGGGGFFFGGGGGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGGGDRR
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGGGDRR
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGRRRRGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGDDDDDDGGGGGGGGGGGGGGDRR
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGRRRRGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGGGDDDRRRDDGGGGGGGGGGGGGGDRR
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGRRRGGGGGGGGGGGGGGGGFFFFFGGGGGGGGGGGGGGGGGGDDDRRRRDDGGGGGGGGGGGGDRR
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGRRRGGGGGGGGGGGGGGGGGFFFFFGGGGGGGGGGGGGGGGGGGDDRRRRDDGGGGGGGGGGGDRR
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGRRRGGGGGGGGGGGGGGGGGFFFFFGGGGGGGGGGGGGGGGGGGDDRRRRDDGGGGGGGGGGDRR
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGGGGGGDDRRRRDDGGGGGGGGDDRR
GGGGGGGGGGGGGGGGGGGGGGGGGGGGRRRGGGGGGGGGGGGGGGGGGGGGGGFFFGGGGGGGGGGGGGGGGGGGGGGDDRRRRDDGGGGGGGDRRR
GGGGGGGGGGGGGGGGGGGGGGGGGGGRRRRRRGGGGGGGGGGGGGGGGGGGFFFFFGGGGGGGGGGGGGGGGGGGGGGGDDRRRRDDDDDDDRRRRR
GGGGGGGGGGGGGGGGGGGGGGGGGGRRRRRRRGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGDDDDRRRRRRRRRRRRRR
GGGGGGGGGGGGGGGGGGGGGGGGGRRRRRRRGGGGGGGGGGGGGGGGRRRRRRRRRGGGGGGGGGGGGGGGGGGGGGGRRDDDDRRRRRRRRRRRRR
GGGGGGGGGGGGGGGGGGGGGGGGGRRRRRRRGGGGGGGGGGGGGGRRRRRRRRRRRGGGGGGGGGGGGGGGGGGGGGGRRRDDDDRRRRRRRRRRRR
GGGGGGGGGGGGGGGGGGGGGGGGRRRRRRRRRGGGGGGGGGGGGRRRRRRRRRRRRRGGGGGGGGGGGGGGGGGGGGGRRRRDDDDDRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDDRRRRRRRRRRRRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDDDDRRRRRRRRRRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDDDDDDRRRRRRRRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRDDDDDDRRRRRRRRRRRRRRRRRRDDDDDDDDRRRRRRRRRRRRRRRRRRRDDDDDDDRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRDDDDDDDRRRRRRRRRRRRRRRRRRRDDDDDDDDRRRRRRRRRRRRRRRRRRDDDDDDRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRRRRRRRRRDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRDDDDRRRRGGGGGGGGGGGGGGGGGGGGGGRRRRRRRRRRRRRGGGGGGGGGGGGGGGRRRRRRRRRGGGGGGGGGGGGGGGGGGGG
RRRRRRRRRRRRDDDDRRRGGGGGGGGGGGGGGGGGGGGGGGRRRRRRRRRRRGGGGGGGGGGGGGGGGGRRRRRRRGGGGGGGGGGGGGGGGGGGGG
RRRRRRRRRRRRRDDDDRRGGGGGGGGGGGGGGGGGGGGGGGGGRRRRRRRRRGGGGGGGGGGGGGGGGGRRRRRRRGGGGGGGGGGGGGGGGGGGGG
RRRRRRRRRRRRRRDDDDGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGRRRRRRRGGGGGGGGGGGGGGGGGGGGGG
RRRRRDDDDDDDRRRRDDGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGFFFFFGGGGGGGGGGGGGGGGRRRRRRGGGGGGGGGGGGGGGGGGGGGGG
RRRDDGGGGGGDDRRRRDDGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGFFFGGGGGGGGGGGGGGGGGGRRRGGGGGGGGGGGGGGGGGGGGGGGG
RRDDGGGGGGGGDDRRRRDDGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
RRDGGGGGGGGGGDDRRRRDDGGGGGGGGGGGGGGGGGGGGGGGGGGGGFFFFFGGGGGGGGGGGGRRRGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
RRDGGGGGGGGGGGDDRRRRDDGGGGGGGGGGGGGGGGGGGGGGGGGGFFFFFGGGGGGGGGGGGRRRGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
RRDGGGGGGGGGGGGDDRRRRDDGGGGGGGGGGGGGGGGGGGGGGGGFFFFFGGGGGGGGGGGGGRRRGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
RRDGGGGGGGGGGGGGDDRRRRDDGGGGGGGGGGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGRRRRGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
RRDGGGGGGGGGGGGGGDDDDDGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGRRRRGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
RRDGGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
RRDGGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGGGGGGGGGGGFFFGGGGGGGGGGGGGGGGGGGGGGGFFFGGGGGGGGGGGGGGGGGGGGG
RRDGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGGGGGGGGGGGFFFFGGGGGGGGGGGGGGGGGGGGGGGFFFGGGGGGGGGGGGGGGGGGGGG
RRDGGGGGGGGGGFFFFFFFFGGGGGGGGGGGGGGGGGGGGGGGGFFFFFFFFFGGGGGGGGGGGGGGGGGGGFFFFFFFGGGGGGGGGGGGGGGGGG
GFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFG
GFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFG
GFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFG
GFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFG
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
3               //Number of players
0 30000 500     // global maxes                                    
1 900 125       // player 1's starting resources
2 1000 0        // player 2's
3 1000 0        // player 3's
8               // number of units to render
GoldMine 0 1 12 // Name PlayerNum X Y
GoldMine 0 92 49 
Peasant 1 3 4
TownHall 1 3 5
Peasant 2 94 59    
TownHall 2 92 54
Peasant 3 7 8
TownHall 3 10 10


```
