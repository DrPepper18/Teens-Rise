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
int HUDOnScreen = 1;
int HintsOnScreen = 1;
int framedelay = 10;

int colorback[64][64], colorfront[64][64];
char screen[64][64];
int screentop, screenbottom, screenleft, screenright;

int lightingmap[256][256],
	lightsource[32][4],		//0 - power of light; 1 - Y; 2 - X; 3 - radius
	light = 0;				//Default lightning
char *quote;

void GameOverScreen()
{
	char FailDefault[128], CheckpointTitle[128], CancelMissionTitle[128];
	Localize(FailDefault, 16, "\\ingame.txt");
	Localize(CheckpointTitle, 17, "\\ingame.txt");
	Localize(CancelMissionTitle, 18, "\\ingame.txt");
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
	int i;
	int hpcolor, energycolor;
	Color(0,15);
	cout << "\t\t\t[";
	for(i = 0; ; i++)
	{
		hpcolor = 0, energycolor = 0;
		if(i >= FullHP && i >= stamina)
			break;

		if(i < HP)
			hpcolor = 2;
		if(i < energy)
			energycolor = 15;
		else if(HP - i > FullHP)
			hpcolor = 10;

		Color(hpcolor, energycolor);

		if(i < stamina)
			cout << "_";
		else
			cout << " ";
	}
	Color(0, 15);
	cout << "] ";
	if(weapon[weaponslot] != 0){
		cout << "[" << item[weapon[weaponslot]].name;
		if(weapon[weaponslot] == iWaterGun)
			cout << "(" << water << ")";
		else if(weapon[weaponslot] == iPaintSpray){
			Color(13,0);
			cout << " ";
			Color(0,15);
		}
		cout << "] ";
	}
	cout << "[" << hr << ":";
	if(mn < 10)	cout << "0";
	cout << mn << "]\t\t";
	Color(0,0);
	if(wantedlevel > 0)
		Color(0, 9);
	cout << wantedlevel << endl;
	Color(0,15);
	//cout << "[Y " << y << ";X " << x << "   " << LocationName[location] << "(" << MapSizeY << "x" << MapSizeX << ")]" << endl;
	//cout << "Performance:" << op << endl;
}
void Hint()
{/*
	
*/}
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
			else{
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
void DrawFrame()
{
	COORD cursor;
    cursor.X = 0, cursor.Y = 0;
    SetConsoleCursorPosition(hConsole, cursor);
	CONSOLE_CURSOR_INFO cursorinfo;
	cursorinfo.bVisible = 0;
	SetConsoleCursorInfo(hConsole, &cursorinfo);
	int a, b;
	for(a = 0; a < sizeY*2; a++)
	{
		Color(0,0);
		cout << "\t\t\t";
		for(b = 0; b < sizeX*2; b++){
			Color(colorback[a][b], colorfront[a][b]);
			cout << screen[a][b];
			op++;
		}
		cout << endl;
	}
	Color(0, 15);
	framemodulus = (framemodulus + 1) % 10;
}
void DrawWindow(char UI[64][64])
{
    CONSOLE_CURSOR_INFO cursorinfo;
	cursorinfo.bVisible = 0;
	SetConsoleCursorInfo(hConsole, &cursorinfo);
	Color(0,15);
	for(int j = 0; j < 14; j++){
		cout << "\t\t\t";
		for(int i = 0; i < 37; i++){
			Color(colorback[j][i], colorfront[j][i]);
			cout << UI[j][i];
		}
		Color(0,15);
		cout << endl;
	}
}
void Video(int map[256][256])
{
	CameraSetup();
	Render(map);
	DrawFrame();
	if(HUDOnScreen == 1)
		HUD();
	if(GetAsyncKeyState(Keyboard[Aim]))
		NPCBarOutput(1);
	else
		cout << "\t\t";
	Sleep(framedelay);
}