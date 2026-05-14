#pragma once
#include <iostream> //System Libraries
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <Xinput.h>

#include "script.h" //Local libraries
#include "input.h"

using namespace std;

//Video Settings
int sizeX = 20, sizeY = 7;
bool HUDOnScreen = true;
bool HintsOnScreen = true;
int framedelay = 50;

int colorback[64][64], colorfront[64][64];
char screen[64][64];
int screentop, screenbottom, screenleft, screenright;

int lightingmap[256][256],
	lightsource[32][4],		//0 - power of light; 1 - Y; 2 - X; 3 - radius
	light = 0;				//Default lightning

void GameOverScreen()
{
	char FailDefault[128], CheckpointTitle[128], CancelMissionTitle[128];
	Localize(FailDefault, 16, "/ingame.txt");
	Localize(CheckpointTitle, 17, "/ingame.txt");
	Localize(CancelMissionTitle, 18, "/ingame.txt");
	if(failreason == 0)
		failreason = FailDefault;
	while(1)
	{
		system("cls");
		Color(0, 12);
		printf("\
%s\n\
[Enter] - %s\n\
[Back]  - %s\n", failreason, CheckpointTitle, CancelMissionTitle);
		switch(_getch())
		{
			case Enter:
				failreason = FailDefault;
				return;
			break;
			case Back:
				mission = 0;
				return;
			break;
			default:
				continue;
		}
	}
}
void NPCBarOutput(int i)
{
	if(skill[HealthAnalysis].ismastered){
		cout << "HP:" << npc[i][npc_HP] << " ";
	}
	if(skill[StaminaAnalysis].ismastered){
		cout << "EP:" << npc[i][npc_energy];
	}
}
/*void BarOutput(	// DO NOT DELETE!!! KEEP IT FOR ENEMIES' HUD
	char screen[64][64], int colorback[64][64], int colorfront[64][64], 
	char *name, int Value, int MaxValue, int y, int x,
	int BarCell, int BorderCellLeft, int BorderCellRight,
	int BorderColorback, int BorderColorfront,
	int BarColorback, int BarColorfront)
{
	if(BorderCellLeft != 0)
	{
		screen[y][x] = BorderCellLeft;
		x = x + 1;
	}
	if(BorderCellRight != 0)
		screen[y][x+MaxValue+1] = BorderCellRight;
	for(int i = 0; i < MaxValue; i++)
	{
		if(i < Value)
			screen[y][x+i] = BarCell;
	}
}*/
void TextOutput(
	char screen[64][64], 
	char *text, int coordY, int coordX, int backplan, int textcolor, int border)
{
	for(int i = 0, k = 0; text[i] != 0; i++, k++)
	{
		if(k > border)
			coordY++, k = 0;
		if(backplan < 16)
			colorback[coordY][coordX+k] = backplan;
		if(textcolor < 16)
			colorfront[coordY][coordX+k] = textcolor;
		screen[coordY][coordX+k] = text[i];
	}
}
void Shadow(int j, int i, int a, int b) //Rendering shadows and lightings
{
	if(lightingmap[j][i] == -2)
		colorback[a][b] = 0, colorfront[a][b] = 0;
	if(lightingmap[j][i] == -1){
	//Primary color
		if(colorback[a][b] > 8)
			colorback[a][b] -= 8;
		else 
			colorback[a][b] = 0;
	//Secondary color
		if(colorfront[a][b] > 8)
			colorfront[a][b] -= 8;
		else
			colorfront[a][b] = 0;
	}
	if(lightingmap[j][i] == 0){

	}
	if(lightingmap[j][i] == 1){
	//Primary color
		if(colorback[a][b] > 8)
			colorback[a][b] = 15;
		else 
			colorback[a][b] += 8;
	//Secondary color
		if(colorfront[a][b] > 8)
			colorfront[a][b] = 15;
		else
			colorfront[a][b] += 8;
	}
	else if(lightingmap[j][i] == 2)
		colorback[a][b] = 15, colorfront[a][b] = 15;
	op++;
}
void LightMapLoad()
{
	int k, j, i;
	for (j = -(sizeY+2); j < sizeY+2; j++)
		for (i = -(sizeX+2); i < sizeX+2; i++) {
			if(cameracenter[0] + j >= 0 && cameracenter[1] + i >= 0)
				lightingmap[cameracenter[0] + j][cameracenter[1] + i] = light;
			op++;
		}
	for (k = 0; k < 32; k++)
		for (j = -lightsource[k][3]; j < lightsource[k][3]; j++)
			for (i = -lightsource[k][3]; i < lightsource[k][3]; i++) {
				lightingmap[lightsource[k][1] + j][lightsource[k][2] + i] += lightsource[k][0];
				op++;
			}
}
void Details(char screen[64][64], int a, int b)
{
	for(int k = 0; k < 32; k++)
	{
		if(particles[k][2] != 0)
		{
			if(a == particles[k][0] && b == particles[k][1])
			{
				screen[a][b] = particles[k][2];
				if(weather == rain)
					colorfront[a][b] = objectmodel[63][3];
				else if(weather == snow)
					colorfront[a][b] = objectmodel[67][3];
				else if(weather == leaffall)
					colorfront[a][b] = 14;
			}
		}
		op++;
	}
}
void AmmoRender(int j, int i, int a, int b)
{
	for(int k = 0; k < 32; k++)
	{
		if(j == physicalbody[k][CoordY] && i == physicalbody[k][CoordX])
		{
			screen[a][b] = objectmodel[physicalbody[k][Texture]][1],
			colorfront[a][b] = objectmodel[physicalbody[k][Texture]][3];
		}
		op++;
	}
}
void PostEffects()
{
	if(kissed)
		system("color 5f");
	if(gotdamage)
		system("color c0");
}
void CameraSetup()
{
	if(cameratype == actor){
	//DYNAMIC CAMERA: 
	//Switches to static by Y- and/or X-axis if close to the end of a map.
		//Otherwise it's free
		if(y-sizeY <= 0)//Y-axis
			cameracenter[camposY] = sizeY;
		else if(y+sizeY > MapSizeY || sizeY*2 > MapSizeY)
			cameracenter[camposY] = MapSizeY-sizeY;
		else
			cameracenter[camposY] = y;

		if(x-sizeX <= 0 && sizeX*2+1 < MapSizeX)//X-axis
			cameracenter[camposX] = sizeX;
		else if(x+sizeX > MapSizeX || sizeX*2+1 >= MapSizeX)
			cameracenter[camposX] = MapSizeX-sizeX;
		else
			cameracenter[camposX] = x;
	//FREE CAMERA: always centered on the player
		//cameracenter[camposY] = y, cameracenter[camposX] = x;
		//Comment what you don't need, uncomment what you need
	}
	else if(cameratype == point)
		cameracenter[camposY] = AimY, cameracenter[camposX] = AimX;
}
void HUD()
{
    static char health_buffer[64]; 
    static char weapon_buffer[32];
	static char time_buffer[8];

    int bar_limit = (FullHP > 60) ? 60 : (int)FullHP;

    health_buffer[0] = '[';
    for(int i = 1; i <= bar_limit; i++)
    {
        health_buffer[i] = (i <= HP) ? '#' : ' ';
    }
    health_buffer[bar_limit + 1] = ']';
    health_buffer[bar_limit + 2] = '\0';

    const char* w_name = item[weapon[weaponslot]].name;
    weapon_buffer[0] = '[';
    int i = 0;
    while(w_name[i] != '\0' && i < 29) {
        weapon_buffer[i+1] = w_name[i];
        i++;
    }
    weapon_buffer[i+1] = ']';
    weapon_buffer[i+2] = '\0';

	time_buffer[0] = '[';
	if (hr >= 10)
	{
		time_buffer[1] = '0' + hr / 10;
		time_buffer[2] = '0' + hr % 10;
	}
	else
	{
		time_buffer[1] = '0';
		time_buffer[2] = '0' + hr;
	}
	time_buffer[3] = ':';
	if (mn >= 10)
	{
		time_buffer[4] = '0' + mn / 10;
		time_buffer[5] = '0' + mn % 10;
	}
	else
	{
		time_buffer[4] = '0';
		time_buffer[5] = '0' + mn;
	}
	time_buffer[6] = ']';
	time_buffer[7] = '\0';

    TextOutput(screen, health_buffer, sizeY*2-2, 1, 0, 15, bar_limit + 2);
    TextOutput(screen, weapon_buffer, sizeY*2-2, (int)(FullHP+4), 0, 15, i + 2);
    TextOutput(screen, time_buffer, sizeY*2-2, (int)(FullHP+i+7), 0, 15, 8);
}
void Hint() {}
void Render(int map[256][256])
{
	int j, i, a, b;
	screentop = cameracenter[camposY] - sizeY, screenbottom = cameracenter[camposY] + sizeY, 
	screenleft = cameracenter[camposX] - sizeX, screenright = cameracenter[camposX] + sizeX;
	Color(0, 15);
	
	for(j = screentop, a = 0; j < screenbottom, a < sizeY*2; j++, a++)
	{
		for(i = screenleft, b = 0; i < screenright, b < sizeX*2; i++, b++)
		{
			if(j < 0 || i < 0 || j >= MapSizeY || i >= MapSizeX){
				screen[a][b] = ' ', colorback[a][b] = 0, colorfront[a][b] = 0;
			}
			else {
				screen[a][b] = objectmodel[map[j][i]][1], colorfront[a][b] = objectmodel[map[j][i]][3];
				if(objectmodel[map[j][i]][2] != 16)
					colorback[a][b] = objectmodel[map[j][i]][2];
				else
					colorback[a][b] = 0;
			}
			AmmoRender(j,i, a,b);
			Details(screen, a,b);
			Shadow(j,i, a,b);
			PostEffects();
		}
	}
	a = AimY - screentop, b = AimX - screenleft;
	if(LockOn != 0)
		screen[a][b-1] = '(', screen[a][b+1] = ')', 
		colorfront[a][b-1] = 15, colorfront[a][b+1] = 15;
	else
		screen[a][b] = '+', colorfront[a][b] = 15;
	//TextOutput(screen, colorback, colorfront, subtitle, sizeY * 2 - 3, 3, 0, 15, 32);
}
void DrawFrame(char screen[64][64])
{
	const int SCREEN_WIDTH = sizeX * 2;
	const int SCREEN_HEIGHT = sizeY * 2;
	CHAR_INFO consoleBuffer[600];
	for (int j = 0; j < SCREEN_HEIGHT; j++) {
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            int index = j * SCREEN_WIDTH + i;
            consoleBuffer[index].Char.AsciiChar = screen[j][i];
            consoleBuffer[index].Attributes = (colorback[j][i] << 4) | colorfront[j][i];
        }
    }
    COORD bufferSize = { (short)SCREEN_WIDTH, (short)SCREEN_HEIGHT };
    COORD bufferCoord = { 0, 0 };
    SMALL_RECT writeRegion = { 0, 0, (short)(SCREEN_WIDTH - 1), (short)(SCREEN_HEIGHT - 1) };
    WriteConsoleOutput(hConsole, consoleBuffer, bufferSize, bufferCoord, &writeRegion);
    framemodulus = (framemodulus + 1) % 10;
	Sleep(framedelay);
}
void Video(int map[256][256])
{
	CameraSetup();
	Render(map);
	if(caption) {
		TextOutput(screen, caption, sizeY * 2 - 3, 3, 0, 15, 32);
		TextOutput(screen, "[Enter] - Next", sizeY * 2 - 2, 3, 0, 15, 32);
	}
	else if(HUDOnScreen)
		HUD();
	// if(GetAsyncKeyState(Keyboard[Aim]))
	// 	NPCBarOutput(1);
	DrawFrame(screen);
}