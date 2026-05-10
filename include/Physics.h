#pragma once
#include "GameMechanics.h"
//Physics
int physicalbody[32][5];
enum termins
{
	Texture,
	CoordY,
	CoordX,
	VectorY,
	VectorX,
};
void BodyPrep(int i, int texture, int coordY, int coordX, int vectorY, int vectorX)
{
	physicalbody[i][Texture] = texture;
	physicalbody[i][CoordY] = coordY;
	physicalbody[i][CoordX] = coordX;
	physicalbody[i][VectorY] = vectorY;
	physicalbody[i][VectorX] = vectorX;
}
void Physics()
{
	for(int i = 0; i < sizeof(physicalbody)/sizeof(physicalbody[0]); i++)
	{
		if(physicalbody[i][Texture] != 0)
		{
			for(int j = 0; j < abs(physicalbody[i][VectorY]); j++)
			{
				if(physicalbody[i][CoordY] > 0 && physicalbody[i][CoordX] > 0){
					physicalbody[i][CoordY] += physicalbody[i][VectorY]/abs(physicalbody[i][VectorY]);
				}
				if(objectmodel[loadedmap[physicalbody[i][CoordY]][physicalbody[i][CoordX]]][4] == 1 || 
				physicalbody[i][CoordY] == 1 || physicalbody[i][CoordY] == MapSizeY-1){
					BodyPrep(i,0,0,0,0,0);
					break;
				}
				for(int k = 0; k < sizeof(npc)/sizeof(npc[0]); k++)
				{
					if(physicalbody[k][CoordY] == npc[k][0] && physicalbody[k][CoordX] == npc[k][1])
						if(npc[k][4] > 0)
							npc[k][4]--;
					op++;
				}
			}
			if(physicalbody[i][Texture] == 0)
				break;
			for(int j = 0; j < abs(physicalbody[i][VectorX]); j++)
			{
				if(physicalbody[i][CoordY] > 0 && physicalbody[i][CoordX] > 0){
					physicalbody[i][CoordX] += physicalbody[i][VectorX]/abs(physicalbody[i][VectorX]);
				}
				if(objectmodel[loadedmap[physicalbody[i][CoordY]][physicalbody[i][CoordX]]][4] == 1 || 
				physicalbody[i][CoordX] == 1 || physicalbody[i][CoordX] > 256){
					BodyPrep(i,0,0,0,0,0);
					break;
				}
				for (int k = 0; k < sizeof(npc) / sizeof(npc[0]); k++)
				{
					if (physicalbody[k][CoordY] == npc[k][0] && physicalbody[k][CoordX] == npc[k][1])
						if (npc[k][4] > 0)
							npc[k][4]--;
					op++;
				}
			}
		}
	}
}
