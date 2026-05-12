/****************************************************
*(c)Bluscreendez, 2021-2025. Teen's Rise source code*
*                                                   *
*Minimal requirments:                               *
*CPU: ~180 MHz                                      *
*RAM: ~640 Kb                                       *
*Recommended requirements:                          *
*CPU: ~240 MHz                                      *
*RAM: ~720 Kb                                       *
*Disc space: ~214 Kb                                *
*                                                   *
*NOTICE: Excluding conhost.exe requirments          *
*****************************************************/


#include <iostream>//System libraries
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <Lmcons.h>
#include <vector>
#include <WinUser.h>
#include <time.h>
#include <MMSystem.h> 

#include "graphics.h"//Engine fragments
#include "audio.h"
#include "GameMechanics.h"
#include "ai.h"
#include "script.h"
#include "input.h"

using namespace std;

void ControlsSettings()
{
	system("cls");

	char SprintLabel[128];
	char CrawlLabel[128];
	char ActionLabel[128];
	char PunchLabel[128];
	char LockOnLabel[128];
	char WeaponLabel[128];
	char Slot1Label[128];
	char Slot2Label[128];
	char Slot3Label[128];
	char Slot4Label[128];
	char UseItemLabel[128];
	char BindLabel[128];
	char ConflictLabel[128];

	Localize(SprintLabel,	55, "/menu.txt");
	Localize(CrawlLabel,	56, "/menu.txt");
	Localize(ActionLabel,	57, "/menu.txt");
	Localize(PunchLabel,	58, "/menu.txt");
	Localize(LockOnLabel,	59, "/menu.txt");
	Localize(WeaponLabel,	60, "/menu.txt");
	Localize(Slot1Label,	61, "/menu.txt");
	Localize(Slot2Label,	62, "/menu.txt");
	Localize(Slot3Label,	63, "/menu.txt");
	Localize(Slot4Label,	64, "/menu.txt");
	Localize(UseItemLabel,	65, "/menu.txt");
	Localize(BindLabel,		66, "/menu.txt");
	Localize(ConflictLabel, 67, "/menu.txt");

	int pointer = 0;
	bool click = false;
	// int type = 0; //Control type
	bool conflict;
	int k, j, i;
	
	char 
	*keyboardtype[4] = {
	"Default - Keyboard+mouse",
	"Keyboard only",},
	*gamepadtype[4] = {
	"Standard",
	"Alternative",};

	while(1)
	{
		COORD cursor;
		cursor.X = 0, cursor.Y = 0;
		SetConsoleCursorPosition(hConsole, cursor);
		conflict = false;
		
		char UI[64][64];
		for (j = 0; j < 14; j++)
			for (i = 0; menupattern[j][i] != 0; i++)
				UI[j][i] = menupattern[j][i];
		for(i = 0; i < 12; i++)
			TextOutput(UI, "|", 2+i, 7, 16, 0, 10);
		TextOutput(UI, "_________________", 9, 19, 16, 0, 16);
		TextOutput(UI, "[Q] <-", 1, 2, 16, 0, 10);
		TextOutput(UI, "-> [E]", 1, 30, 16, 0, 10);

		TextOutput(UI, SprintLabel,	2,1, 16,0, 10);
		TextOutput(UI, CrawlLabel,	3,1, 16,0, 10);
		TextOutput(UI, ActionLabel,	4,1, 16,0, 10);
		TextOutput(UI, PunchLabel,	5,1, 16,0, 10);
		TextOutput(UI, LockOnLabel,	6,1, 16,0, 10);
		TextOutput(UI, WeaponLabel,	7,1, 16,0, 10);
		TextOutput(UI, Slot1Label,	8,1, 16,0, 10);
		TextOutput(UI, Slot2Label,	9,1, 16,0, 10);
		TextOutput(UI, Slot3Label,	10,1,16,0, 10);
		TextOutput(UI, Slot4Label,	11,1,16,0, 10);
		TextOutput(UI, UseItemLabel,	12,1,16,0, 10);

		for(j = 0; j < 64; j++)
			for(i = 0; i < 64; i++)
				colorback[j][i] = 15, colorfront[j][i] = 0;
		j = 2+pointer;
		for(i = 1; i < 17; i++)
			colorback[j][i] = 0, colorfront[j][i] = 15;

		for(k = Sprint; k < 15; k++){
			for(j = Sprint; j < 15; j++){
				if(Keyboard[k] == Keyboard[j] && k != j){
					for(i = 1; i < 17; i++){
						conflict = true;
						colorback[k-2][i] = 12, colorback[j-2][i] = 12;
					}
				}
			}
		}
		if(conflict && !click)
			TextOutput(UI, ConflictLabel, 10,18, 16,0, 16);
		if(click)
			TextOutput(UI, BindLabel, 10,18, 16,0, 16);
		else
			TextOutput(UI, backhint, 12,27, 16,0, 16);

		if(InputDevice == keyboard){
			TextOutput(UI, KeyName(Keyboard[Sprint]),	2,9, 7,0, 10);
			TextOutput(UI, KeyName(Keyboard[Crawl]),	3,9, 7,0, 10);
			TextOutput(UI, KeyName(Keyboard[Action]),	4,9, 7,0, 10);
			TextOutput(UI, KeyName(Keyboard[Punch]),	5,9, 7,0, 10);
			TextOutput(UI, KeyName(Keyboard[Aim]),		6,9, 7,0, 10);
			TextOutput(UI, KeyName(Keyboard[Weapon]),	7,9, 7,0, 10);
			TextOutput(UI, KeyName(Keyboard[Slot1]),	8,9, 7,0, 10);
			TextOutput(UI, KeyName(Keyboard[Slot2]),	9,9, 7,0, 10);
			TextOutput(UI, KeyName(Keyboard[Slot3]),	10,9, 7,0, 10);
			TextOutput(UI, KeyName(Keyboard[Slot4]),	11,9, 7,0, 10);
			TextOutput(UI, KeyName(Keyboard[UseItem]),	12,9, 7,0, 10);
		}
		else if(InputDevice == Xbox_gamepad){
			TextOutput(UI, "(A)",	2,9, 0,10, 10);
			TextOutput(UI, "(B)",	3,9, 0,12, 10);
			TextOutput(UI, "(Y)",	4,9, 0,14, 10);
			TextOutput(UI, "(X)",	5,9, 0,9, 10);
			TextOutput(UI, "|LT\\",	6,9, 0,15, 10);
			TextOutput(UI, "/RT|",	7,9, 0,15, 10);
			TextOutput(UI, "[^]",	8,9, 0,15, 10);
			TextOutput(UI, "[>]",	9,9, 0,15, 10);
			TextOutput(UI, "[<]",	10,9,0,15, 10);
			TextOutput(UI, "[v]",	11,9,0,15, 10);
			TextOutput(UI, "[LB]",	12,9,0,15, 16);
		}
		else if(InputDevice == DualShock){
			char square[3] = {'(','n',')'};
			char triangle[3] = {'(', 127, ')'};
			TextOutput(UI, "(X)",	2,9, 0,9, 10);
			TextOutput(UI, "(O)",	3,9, 0,12, 10);
			TextOutput(UI, triangle,	4,9, 0,10, 10);
			TextOutput(UI, square,	5,9, 0,13, 10);
			TextOutput(UI, "[L1]",	6,9, 0,15, 10);
			TextOutput(UI, "[R1]",	7,9, 0,15, 10);
			TextOutput(UI, "[^]",	8,9, 0,15, 10);
			TextOutput(UI, "[>]",	9,9, 0,15, 10);
			TextOutput(UI, "[<]",	10,9, 0,15, 10);
			TextOutput(UI, "[v]",	11,9, 0,15, 10);
			TextOutput(UI, "[L2]",	12,9,0,15, 16);
		}

		GetCursorPos(&p);
		MouseY = p.y / SensivityY, MouseX = p.x / SensivityX;
		UI[MouseY][MouseX] = '+';
		colorfront[MouseY][MouseX] = 12;

		DrawWindow(UI);

		if(!click)
		{
			if (MouseX <= 20 && MouseY >= 2)
				pointer = MouseY - 2;
			if(GetAsyncKeyState(Esc))
				return;
			else if(GetAsyncKeyState('W') && pointer > 0)
				pointer--;
			else if(GetAsyncKeyState('S') && pointer < 10)
				pointer++;
			else if(GetAsyncKeyState(VK_UP) && pointer > 0)
				pointer--;
			else if(GetAsyncKeyState(VK_DOWN) && pointer < 10)
				pointer++;
			else if(GetAsyncKeyState('Q'))
			{
				if(KeyboardType == 0)	KeyboardType = 1;
				else					KeyboardType--;
				for(i = 0; i < 16; i++)
					Keyboard[i] = KeyboardControlsType[KeyboardType][i];
			}
			else if(GetAsyncKeyState('E'))
			{
				if(KeyboardType == 1)	KeyboardType = 0;
				else					KeyboardType++;
				for(i = 0; i < 16; i++)
					Keyboard[i] = KeyboardControlsType[KeyboardType][i];
			}
			else if(GetAsyncKeyState(Enter) || GetAsyncKeyState(VK_LBUTTON)){
				click = true;
			}
		}
		else if(click)
		{
			for(i = 0; i < 256; i++){
				if(GetAsyncKeyState(i)){
					Keyboard[pointer+4] = i;
					break;
				}
			}
			cout << Keyboard[pointer+4];
			click = false;
		}
	}
	system("cls");
}
void Settings()
{
	//char SettingsLabel[128];
	char VideoButton[128];
	char AudioButton[128];
	char GameButton[128];
	char ControlsButton[128];

	char VideoInfoLabel[128];
	char AudioInfoLabel[128];
	char GameInfoLabel[128];
	char ControlsInfoLabel[128];

	char FrameDelayButton[128];
	char FontButton[128];
	char FontSizeButton[128];
	char LanguageButton[128];

	Localize(VideoButton, 28, "/menu.txt");
	Localize(AudioButton, 29, "/menu.txt");
	Localize(GameButton, 30, "/menu.txt");
	Localize(ControlsButton, 31, "/menu.txt");

	Localize(VideoInfoLabel, 32, "/menu.txt");
	Localize(AudioInfoLabel, 33, "/menu.txt");
	Localize(GameInfoLabel, 34, "/menu.txt");
	Localize(ControlsInfoLabel, 35, "/menu.txt");

	Localize(FrameDelayButton, 37, "/menu.txt");
	Localize(FontButton, 38, "/menu.txt");
	Localize(FontSizeButton, 39, "/menu.txt");
	Localize(LanguageButton, 40, "/menu.txt");

	int j;
	system("cls");
	enum settingstype
	{
		none = 0,
		video,
		audio,
		game,
		controls,
	};
	int pointer = 1, settingof = 0;
	while(1)
	{
		COORD cursor;
		cursor.X = 0, cursor.Y = 0;
		SetConsoleCursorPosition(hConsole, cursor);

		char UI[64][64];
		for (j = 0; j < 14; j++)
			for (int i = 0; menupattern[j][i] != 0; i++)
				UI[j][i] = menupattern[j][i];

		TextOutput(UI,
			"SETTINGS",
			1, 2, 16, 0, 15);
		for(int i = 2; i < 6; i++)
			TextOutput(UI,
				"..............",
				i, 2, 16, 0, 15);
		if(settingof == none)
		{
			TextOutput(UI, 
					VideoButton, 
					2,2, 16,0, 15);
			TextOutput(UI, 
					AudioButton, 
					3,2, 16,0, 15);
			TextOutput(UI, 
					GameButton, 
					4,2, 16,0, 15);
			TextOutput(UI, 
					ControlsButton, 
					5,2, 16,0, 15);
			switch(pointer)
			{
			case video:
				TextOutput(UI, 
					VideoInfoLabel, 
					2,19, 16,0, 16);
				break;
			case audio:
				TextOutput(UI, 
					AudioInfoLabel, 
					2,19, 16,0, 16);
				break;
			case game:
				TextOutput(UI, 
					GameInfoLabel, 
					2,19, 16,0, 16);
				break;
			case controls:
				TextOutput(UI, 
					ControlsInfoLabel, 
					2,19, 16,0, 16);
				break;
			}
		}
		else if(settingof == video)
		{
			TextOutput(UI, 
					FrameDelayButton, 
					2,2, 16,0, 15);
			TextOutput(UI, 
					"10 ms", 
					2,20, 16,0, 15);
			TextOutput(UI, 
					FontButton, 
					3,2, 16,0, 15);
			TextOutput(UI, 
					"Pixel", 
					3,20, 16,0, 15);
			TextOutput(UI, 
					FontSizeButton, 
					4,2, 16,0, 15);
			TextOutput(UI, 
					"12x16", 
					4,20, 16,0, 15);
			TextOutput(UI, 
					LanguageButton, 
					5,2, 16,0, 15);
			TextOutput(UI, 
					"Russian", 
					5,20, 16,0, 15);
		}
		else if(settingof == audio)
		{
			TextOutput(UI, 
					"Sound", 
					2,2, 16,0, 15);
			TextOutput(UI, 
					"On", 
					2,20, 16,0, 15);
		}
		else if(settingof == game)
		{
			//Lock-on type
		}
		else if(settingof == controls)
		{
			TextOutput(UI, 
					"Movement:", 
					2,2, 16,0, 15);
			TextOutput(UI, 
					"Input device:", 
					3,2, 16,0, 15);
			TextOutput(UI, 
					"[Controls]", 
					4,2, 16,0, 15);
			TextOutput(UI, 
					"[DEFAULT]", 
					5,2, 16,0, 15);
			TextOutput(UI, 
					"[W][S][A][D]", 
					2,20, 16,0, 15);
			if(InputDevice == keyboard){
				TextOutput(UI, 
					"Keyboard+mouse", 
					3,20, 16,0, 15);
			}
			else if(InputDevice == Xbox_gamepad){
				TextOutput(UI, 
					"XINPUT gamepad", 
					3,20, 16,0, 15);
			}
			else if(InputDevice == DualShock){
				TextOutput(UI, 
					"Dualshock", 
					3,20, 16,0, 15);
			}
			
		}

		for(j = 0; j < 64; j++)
			for(int i = 0; i < 64; i++)
				colorback[j][i] = 15, colorfront[j][i] = 0;
		j = 1+pointer;
		for(int i = 2; i < 17; i++)
			colorback[j][i] = 0, colorfront[j][i] = 15;

		GetCursorPos(&p);
		MouseY = p.y / SensivityY, MouseX = p.x / SensivityX;
		UI[MouseY][MouseX] = '+';
		colorfront[MouseY][MouseX] = 12;

		DrawWindow(UI);
		cout << "Frame delay - " << framedelay << "ms";

		if (MouseX < 20 && MouseY >= 2 && MouseY <= 5)
			pointer = MouseY - 1;
		if(GetAsyncKeyState(Esc))
		{
			if(framedelay < 0)
				framedelay = 0;
			if(settingof == 0)
				return;
			else
				settingof = 0;
		}
		if(GetAsyncKeyState('W') && pointer > 1)
			pointer--;
		else if(GetAsyncKeyState('S') && pointer < 4)
			pointer++;
		else if(GetAsyncKeyState(VK_UP) && pointer > 1)
			pointer--;
		else if(GetAsyncKeyState(VK_DOWN) && pointer < 4)
			pointer++;
		if(settingof == video){
			if(GetAsyncKeyState('A') && framedelay > 0)
				framedelay -= 5;
			else if(GetAsyncKeyState('D'))
				framedelay += 5;
		}
		else if(settingof == audio){

		}
		else if(settingof == controls){
			if(pointer == 2){
				if(GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)){
					if(InputDevice > keyboard)
						InputDevice--;
				}
				else if(GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)){
					if(InputDevice < DualShock)
						InputDevice++;
				}
			}
			if(GetAsyncKeyState(Enter) || GetAsyncKeyState(VK_LBUTTON)){
				if(pointer == 3)
					ControlsSettings();
			}
		}
		else
			if(GetAsyncKeyState(Enter) || GetAsyncKeyState(VK_LBUTTON))
				settingof = pointer;
	}
}
void cmd(char *command)
{
	if(command == NULL)
	{
		cout << "\n>>";
		cin >> command;
	}
	if(strcmp(command, "knockout") == 0){
		HP = 0;
	}
	else if(strcmp(command, "alexset") == 0){
		weapon[extra] = iPepperSpray;
	}
	else if(strcmp(command, "geekset") == 0){
		weapon[ranged2] = iBottleGun;
		weapon[thrown] = iDirtyBottle;
	}
	else if(strcmp(command, "doomerset") == 0){
		weapon[close] = iBat;
		//weapon[close] = iSmokeBomb.number;
	}
	else if(strcmp(command, "zoomerset") == 0){
		weapon[ranged2] = iWaterGun;
	}
	else if(strcmp(command, "offnicset") == 0){
		weapon[close] = iBottle;
		weapon[thrown] = iFireCracker;
	}
}
void DetailsBehaviour(int density)
{
	for(int i = 0; i < density; i++)
	{
		if(weather == 0 || indoor)
			particles[i][2] = 0;
		else if(weather == rain)
			particles[i][2] = '*';
		else if(weather == snow)
			particles[i][2] = '.';
		else if(weather == leaffall){
			if(rand()%2 == 1)
				particles[i][2] = '`';
			else
				particles[i][2] = '\'';
		}
	}
	for(int i = 0; i < density; i++)
	{
		if(weather == rain)
			particles[i][0] = rand()%sizeY*2+1,
			particles[i][1] = rand()%sizeX*2+1;
		else if(weather == snow){
			if(particles[i][0] == 0 || particles[i][1] == 0 ||
			particles[i][0] >= sizeY*2 || particles[i][1] >= sizeX*2)
				particles[i][0] = rand()%sizeY*2+1,
				particles[i][1] = rand()%sizeX*2+1;
			else
				particles[i][0]++, particles[i][1]++;
		}
		else if(weather == leaffall){
			if(particles[i][0] == 0 || particles[i][1] == 0 ||
			particles[i][0] >= sizeY*2 || particles[i][1] >= sizeX*2)
				particles[i][0] = rand()%sizeY*2+1,
				particles[i][1] = rand()%sizeX*2+1;
			else{
				if(rand()%2 == 1)
					particles[i][0]++, particles[i][1]++;
				else
					particles[i][0]++, particles[i][1]--;
			}
		}
	}
	p_onscreen += density;
}
void Credits()
{
	fstream file("translate/credits.txt");
	file.close();
}
void Shop(int catalog[32])
{
	int pointer = 1;
	int cart[10] = {}, goodsamount = 0, cost = 0;
	while (1)
	{
		COORD cursor;
		cursor.X = 0, cursor.Y = 0;
		SetConsoleCursorPosition(hConsole, cursor);
		Color(0, 15);
		char UI[64][64] = {
		"                                       ",
		"                [Q]<-|Equipment|->[E]  ",
		"                                       ",
		" [ ][ ][ ]  [ ] ---------- < 0 > -- p  ",
		" [ ][ ][ ]  [ ] ---------- < 0 > -- p  ",
		" [ ][ ][ ]  [ ] ---------- < 0 > -- p  ",
		" [ ][ ][ ]  [ ] ---------- < 0 > -- p  ",
		"            [ ] ---------- < 0 > -- p  ",
		"            [ ] ---------- < 0 > -- p  ", };
		for (int j = 0; j < 64; j++)
			for (int i = 0; i < 64; i++) {
				colorback[j][i] = colorback[j][i];
				if (UI[j][i] == ' ' || UI[j][i] == 0)
					UI[j][i] = screen[j][i],
					colorfront[j][i] = colorfront[j][i];
				else
					colorfront[j][i] = 15;
			}
		DrawWindow(UI);
		//Input
		if(GetAsyncKeyState(Esc)){
			system("cls");
			return;
		}
		else if(GetAsyncKeyState('W'))
			pointer--;
		else if(GetAsyncKeyState('S'))
			pointer++;
		else if(GetAsyncKeyState(VK_UP))
			pointer--;
		else if(GetAsyncKeyState(VK_DOWN))
			pointer++;
		else if(GetAsyncKeyState(Enter))
			cart[goodsamount] = catalog[pointer],
			goodsamount++;
			//cost += item[catalog[pointer]].price;
		else if(GetAsyncKeyState(Back))
		{
			if(goodsamount > 0){
				goodsamount--,
				cart[goodsamount] = 0;
			}
		}
		else if(GetAsyncKeyState(VK_SPACE)){
			if(money >= cost)
				for(int j = 0; j < goodsamount; j++)
					for(int i = 0; i < 8; i++)
						if(inventory[i] == 0)
						{
							inventory[i] = cart[j];
							//money -= item[cart[j]].price;
						}
		}
	}
	
}
void ItemBoxScreen()
{
	int arr = 0, pointerY = 0, pointerX = 0;
	enum type
	{
		arr_inventory,
		arr_itembox,
	};
	int chosenitem[3] = {0,0,0};//item, where is it, which element 
	while(1)
	{
		COORD cursor;
		cursor.X = 0, cursor.Y = 0;
		SetConsoleCursorPosition(hConsole, cursor);

		char UI[64][64];
		for(int j = 0; j < 64; j++)
			for(int i = 0; i < 64; i++)
				UI[j][i] = screen[j][i];

		TextOutput(UI, "INVENTORY", 4,sizeX-11, 0,15, sizeX*2);
		TextOutput(UI, "ITEM BOX", 4,sizeX+2, 0,15, sizeX*2);

		for(int i = 0; i < 3; i++){
			TextOutput(UI, "[ ][ ][ ]", 6+i,sizeX-11, 0,15, sizeX*2);
			TextOutput(UI, "[ ][ ][ ]", 6+i,sizeX+2, 0,15, sizeX*2);
		}
		for(int i = 0; i < 10; i++)
		{
			if(inventory[i] != iNone)
				UI[6+i/3][sizeX-10+i%3*3] = objectmodel[113+inventory[i]][1],
				colorfront[6+i/3][sizeX-10+i%3*3] = objectmodel[113+inventory[i]][3];
		}
		for(int i = 0; i < 10; i++)
		{
			if(itembox[i] != iNone)
				UI[6+i/3][sizeX+3+i%3*3] = objectmodel[113+itembox[i]][1],
				colorfront[6+i/3][sizeX+3+i%3*3] = objectmodel[113+itembox[i]][3];
		}
		if(arr == arr_inventory)
			colorfront[6+pointerY][sizeX-10+pointerX*3-1] = 14, colorfront[6+pointerY][sizeX-10+pointerX*3+1] = 14;
		else
			colorfront[6+pointerY][sizeX+3+pointerX*3-1] = 14, colorfront[6+pointerY][sizeX+3+pointerX*3+1] = 14;
		if(chosenitem[0] != 0){
			if(chosenitem[1] == arr_inventory)
				colorfront[6+(chosenitem[2]/3)][sizeX-10+(chosenitem[2]%3)*3-1] = 10, colorfront[6+(chosenitem[2]/3)][sizeX-10+(chosenitem[2]%3)*3+1] = 10;
			else if(chosenitem[1] == arr_itembox)
				colorfront[6+(chosenitem[2]/3)][sizeX+3+(chosenitem[2]%3)*3-1] = 10, colorfront[6+(chosenitem[2]/3)][sizeX+3+(chosenitem[2]%3)*3+1] = 10;
		}
		if(arr == arr_itembox){
			TextOutput(UI, item[itembox[pointerY*3+pointerX]].name, 10,4, 0,15, sizeX*2-4);
			TextOutput(UI, item[itembox[pointerY*3+pointerX]].description, 12,4, 0,15, sizeX*2-4);
		}
		else{
			TextOutput(UI, item[inventory[pointerY*3+pointerX]].name, 10,4, 0,15, sizeX*2-4);
			TextOutput(UI, item[inventory[pointerY*3+pointerX]].description, 12,4, 0,15, sizeX*2-4);
		}
		DrawWindow(UI);
		
		if(GetAsyncKeyState(Esc))
			return;
		else if(GetAsyncKeyState('W') && pointerY > 0)
			pointerY--;
		else if(GetAsyncKeyState('S') && pointerY < 2)
			pointerY++;
		else if(GetAsyncKeyState('A'))
		{
			if(pointerX > 0)
				pointerX--;
			else if(pointerX == 0 && arr == arr_itembox)
				arr = arr_inventory, pointerX = 2;
		}
		else if(GetAsyncKeyState('D'))
		{
			if(pointerX < 2)
				pointerX++;
			else if(pointerX == 2 && arr == arr_inventory)
				arr = arr_itembox, pointerX = 0;
		}
		else if(GetAsyncKeyState(Enter))
		{
			if(chosenitem[0] == 0)
			{
				chosenitem[1] = arr, chosenitem[2] = pointerY*3+pointerX;
				if(arr == arr_inventory)
					chosenitem[0] = inventory[pointerY*3+pointerX];
				else
					chosenitem[0] = itembox[pointerY*3+pointerX];
			}
			else
			{
				if(arr == arr_inventory){
					if(chosenitem[1] == arr_inventory)
						inventory[chosenitem[2]] = inventory[pointerY*3+pointerX];
					else
						itembox[chosenitem[2]] = inventory[pointerY*3+pointerX];
					inventory[pointerY*3+pointerX] = chosenitem[0];
				}
				else{
					if(chosenitem[1] == arr_inventory)
						inventory[chosenitem[2]] = itembox[pointerY*3+pointerX];
					else
						itembox[chosenitem[2]] = itembox[pointerY*3+pointerX];
					itembox[pointerY*3+pointerX] = chosenitem[0];
				}
				chosenitem[0] = 0, chosenitem[1] = 0, chosenitem[2] = 0;
			}
		}
	}
}
void InventoryScreen()
{
	int pointerX = 0, pointerY = 0;
	while(1)
	{
		COORD cursor;
		cursor.X = 0, cursor.Y = 0;
		SetConsoleCursorPosition(hConsole, cursor);
		Color(0,0);

		char UI[64][64];
		for (int j = 0; j < 14; j++)
			for (int i = 0; menupattern[j][i] != 0; i++)
				UI[j][i] = menupattern[j][i];
		TextOutput(UI, "[ ][ ][ ]", 2, 2, 16, 0, 17);
		for(int j = 0; j < 3; j++)
			for(int i = 0; i < 3; i++)
				UI[4+j][3 + i * 3 - 1] = '[', UI[4+j][3 + i * 3 + 1] = ']',
	
		TextOutput(UI, item[inventory[pointerY*3+pointerX]].name, 7,2, 16,0, 17);
		UI[4+pointerY][3+pointerX*3-1] = '(', UI[4+pointerY][3+pointerX*3+1] = ')';
		int pointer = pointerY*3+pointerX;
		TextOutput(UI, item[inventory[pointer]].description, 2,20, 16,0, 14);
		
		for(int j = 0; j < 64; j++)
			for(int i = 0; i < 64; i++)
				colorback[j][i] = 15, colorfront[j][i] = 0;
		for(int i = 2+pointerX*3; i < 5+pointerX*3; i++)
			colorfront[4+pointerY][i] = 6;
		for(int j = 0; j < 3; j++)
			for(int i = 0; i < 3; i++){
				if(inventory[j*3+i] != iNone)
					UI[4+j][3+i*3] = objectmodel[113+inventory[j*3+i]][1];
				if(objectmodel[113+inventory[j*3+i]][2] != 16)
					colorback[4+j][3+i*3] = objectmodel[113+inventory[j*3+i]][2];
				if(objectmodel[113+inventory[j*3+i]][3] != 16)
					colorfront[4+j][3+i*3] = objectmodel[113+inventory[j*3+i]][3];
			}
		//Still looking for output for money
		char *Health, *Stamina, *HUD;
		int l = (int)max(FullHP, stamina);
		Health = new char [(int)HP+1];
		Stamina = new char [(int)energy+1];
		HUD = new char [l+3];

		HUD[0] = '[', HUD[l+1] = ']', HUD[l+2] = 0;
		Health[(int)HP] = 0;
		Stamina[(int)energy] = 0;
		for(int i = 1; i < l; i++)
			HUD[i] = ' ';
		for(int i = 0; i < HP; i++)
			Health[i] = '#';
		for(int i = 0; i < energy; i++)
			Stamina[i] = '_';

		TextOutput(UI, "INVENTORY:", 1,2, 16,0, 30);
		TextOutput(UI, "INFO:", 1,20, 16,0, 30);
		//TextOutput(UI, HUD, 9,2, 0,15, 30);
		TextOutput(UI, Health, 9,3, 2,15, int(HP));
		TextOutput(UI, Stamina, 9,3, 16,14, int(energy));
		TextOutput(UI, "[Esc]", 11,2, 7,0, 30);
		TextOutput(UI, "back", 11,8, 16,0, 30);
		//TextOutput(UI, "[Enter] - use", 12,1, 16,0, 30);
		//TextOutput(UI, "[C] - discard", 11,20, 16,0, 30);

		GetCursorPos(&p);
		MouseY = p.y / SensivityY, MouseX = p.x / SensivityX;
		UI[MouseY][MouseX] = '+';
		colorfront[MouseY][MouseX] = 12;

		DrawWindow(UI);
		cout << HUD << Health << Stamina;
		if ((MouseY >= 4 && MouseY <= 6) && (MouseX >= 2 && MouseX <= 11)) {
			pointerY = MouseY - 4, pointerX = (MouseX - 2) / 3;
		}
		if(GetAsyncKeyState(Esc))
			return;
		else if(GetAsyncKeyState('W') && pointerY > 0)
			pointerY--;
		else if(GetAsyncKeyState('S') && pointerY < 2)
			pointerY++;
		else if(GetAsyncKeyState('A') && pointerX > 0)
			pointerX--;
		else if(GetAsyncKeyState('D') && pointerX < 2)
			pointerX++;
		else if(GetAsyncKeyState(VK_UP) && pointerY > 0)
			pointerY--;
		else if(GetAsyncKeyState(VK_DOWN) && pointerY < 2)
			pointerY++;
		else if(GetAsyncKeyState(Enter) || GetAsyncKeyState(VK_LBUTTON)){
			if(inventory[pointer] != 0){
				printf("\t\tUsed %s ([Any key] - OK)", item[inventory[pointer]].name);
				Use(pointer);
				_getch();
				cout << "\r\t\t\t\t";
			}
		}
		else if(GetAsyncKeyState('Q') || GetAsyncKeyState(VK_RBUTTON)){
			if(inventory[pointer])
				quickaccessitem = pointer;
		}
		else if(GetAsyncKeyState('C'))
			inventory[pointer] = 0;
		
		delete HUD;
		delete Health;
		delete Stamina;
	}
}
void DataScreen(int option)//0 is for saving; 1 is for loading
{
	char SaveLoadTitle[128];
	char AutosaveLabel[128];
	char DateLabel[128];
	char TotalLabel[128];
	if(option == 0)
		Localize(SaveLoadTitle, 16, "/menu.txt");
	else
		Localize(SaveLoadTitle, 17, "/menu.txt");
	Localize(AutosaveLabel, 18, "/menu.txt");
	Localize(DateLabel, 19, "/menu.txt");
	Localize(TotalLabel, 20, "/menu.txt");

	int save = 0, load = 1;
	int pointer;
	if(option == save)	pointer = 1;
	else				pointer = 0;
	ifstream file;
	while(1)
	{
		COORD cursor;
		cursor.X = 0, cursor.Y = 0;
		SetConsoleCursorPosition(hConsole, cursor);
		Color(15,0);

		char UI[64][64];
		for (int j = 0; j < 14; j++)
			for (int i = 0; menupattern[j][i] != 0; i++)
				UI[j][i] = menupattern[j][i];
		for(int i = 0; i < 5; i++)
			TextOutput(UI, ".--------------", 2+i, 2, 16, 0, 30);

		for(int j = 0; j < 64; j++)
			for(int i = 0; i < 64; i++)
				colorback[j][i] = 15, colorfront[j][i] = 0;
		TextOutput(UI, SaveLoadTitle, 1, 2, 16, 0, 30);

		TextOutput(UI, DateLabel, 8, 20, 16, 0, 30);
		TextOutput(UI, "--.--.----", 8, 26, 16, 0, 30);
		TextOutput(UI, TotalLabel, 9, 20, 16, 0, 30);
		
		TextOutput(UI, "_________________", 10, 1, 16, 0, 30);
		TextOutput(UI, "_________________", 10, 19, 16, 0, 30);

		TextOutput(UI, backhint, 11,10, 16,0, 30);
		TextOutput(UI, KeyName(Esc), 11,2, 7,0, 30);
		TextOutput(UI, selecthint, 12,10, 16,0, 30);
		TextOutput(UI, KeyName(Enter), 12,2, 7,0, 30);
		
		char buf[3];
		for (int i = 0; i < 5; i++) {
			_itoa_s(i, buf, 10);
			TextOutput(UI, buf, 2 + i, 1, 16, 0, 30);
		}
		//TextOutput(UI, navigatehint,	12,28, 16,0, 30);

		char buffer[64];
		if(pointer == 0)
			file.open("saves/autosave.txt");
		else if(pointer == 1)
			file.open("saves/savedata1.txt");
		else if(pointer == 2)
			file.open("saves/savedata2.txt");
		
		file.getline(buffer, 64);
		file.getline(buffer, 10, ' ');
		file.getline(buffer, 4, '.');
		TextOutput(UI, buffer, 8,26, 16,0, 30);
		file.getline(buffer, 4, '.');
		TextOutput(UI, buffer, 8,29, 16,0, 30);
		file.getline(buffer, 5);
		TextOutput(UI, buffer, 8,32, 16,0, 30);
		bool nodata = true;
		for(int j = 0; j < 5; j++){
			for(int i = 0; i < 7; i++){
				file.getline(buffer, 4, ' ');
				UI[3+j][20+i] = objectmodel[atoi(buffer)][1];
				colorback[3+j][20+i] = objectmodel[atoi(buffer)][2];
				colorfront[3+j][20+i] = objectmodel[atoi(buffer)][3];
				if(atoi(buffer) != 0)
					nodata = false;
			}
		}
		if(nodata)
			TextOutput(UI, "No Data", 5,20, 16,15, 30);
		file.close();
		for(int i = 0; i < 3; i++)
		{
			if(i == 0) file.open("saves/autosave.txt");
			if(i == 1) file.open("saves/savedata1.txt");
			if(i == 2) file.open("saves/savedata2.txt");
			file.getline(buffer, 64);
			TextOutput(UI, buffer, 2+i,3, 16,0, 30);
			file.close();
		}

		int autosavecolor = 0;
		if(option == save)
			autosavecolor = 7;
		TextOutput(UI, AutosaveLabel, 2,3, 16,autosavecolor, 30);

		int j = 2+pointer;
		for(int i = 3; i < 17; i++)
			colorback[j][i] = 0, colorfront[j][i] = 15;

		GetCursorPos(&p);
		MouseY = p.y / SensivityY, MouseX = p.x / SensivityX;
		UI[MouseY][MouseX] = '+';
		colorfront[MouseY][MouseX] = 12;

		DrawWindow(UI);

		if (MouseX < 20 && MouseY >= 2 && MouseY <= 6)
			pointer = MouseY - 2;
		if(GetAsyncKeyState(Esc))
			return;
		else if(GetAsyncKeyState('W') && pointer > 0)
			pointer--;
		else if(GetAsyncKeyState('S') && pointer < 5)
			pointer++;
		else if(GetAsyncKeyState(VK_UP) && pointer > 0)
			pointer--;
		else if(GetAsyncKeyState(VK_DOWN) && pointer < 6)
			pointer++;
		else if(GetAsyncKeyState(Enter) || GetAsyncKeyState(VK_LBUTTON))
		{
			if(option == save && pointer != 0)
				SaveData(pointer);
			else if(option == load){
				LoadData(pointer);
				return;
			}
		}
	}
	system("cls");
}
void pause()
{
	system("cls");
	paused = false;
	int pointer = 1;
	char InventoryButton[128];
	char DiaryButton[128];
	char LoadGameButton[128];
	char SettingsButton[128];
	char QuitGameButton[128];
	Localize(InventoryButton, 1, "/pause.txt");
	Localize(DiaryButton, 2, "/pause.txt");
	Localize(LoadGameButton, 3, "/pause.txt");
	Localize(SettingsButton, 4, "/pause.txt");
	Localize(QuitGameButton, 5, "/pause.txt");

	while(1)
	{
		COORD cursor;
		cursor.X = 0, cursor.Y = 0;
		SetConsoleCursorPosition(hConsole, cursor);
		Color(0,0);
		char UI[64][64];
		for (int j = 0; j < 14; j++)
			for (int i = 0; menupattern[j][i] != 0; i++)
				UI[j][i] = menupattern[j][i];

		for(int j = 0; j < 64; j++)
			for(int i = 0; i < 64; i++)
				colorback[j][i] = 15, colorfront[j][i] = 0;

		TextOutput(UI, "PAUSE", 1, 2, 16, 0, 100);
		for(int i = 0; i < 5; i++)
			TextOutput(UI, "...............", 2+i, 2, 16, 0, 100);

		TextOutput(UI, InventoryButton, 2,2, 16,0, 100);
		TextOutput(UI, DiaryButton, 3,2, 16,0, 100);
		TextOutput(UI, LoadGameButton, 4,2, 16,0, 100);
		TextOutput(UI, SettingsButton, 5,2, 16,0, 100);
		TextOutput(UI, QuitGameButton, 6,2, 16,0, 100);

		for(int i = 2; i < 17; i++)
			colorback[1+pointer][i] = 0, colorfront[1+pointer][i] = 15;

		GetCursorPos(&p);
		MouseY = p.y / SensivityY, MouseX = p.x / SensivityX;
		UI[MouseY][MouseX] = '+';
		colorfront[MouseY][MouseX] = 12;

		DrawWindow(UI);

		if (MouseX < 20 && MouseY >= 2 && MouseY <= 6)
			pointer = MouseY - 1;
		if(GetAsyncKeyState(Esc))
			return;
		else if(GetAsyncKeyState('W') && pointer > 1)
			pointer--;
		else if(GetAsyncKeyState('S') && pointer < 5)
			pointer++;
		if(GetAsyncKeyState(VK_UP) && pointer > 1)
			pointer--;
		if(GetAsyncKeyState(VK_DOWN) && pointer < 5)
			pointer++;
		else if(GetAsyncKeyState(Enter) || GetAsyncKeyState(VK_LBUTTON))
		{
			if(pointer == 1)
				InventoryScreen();
			//else if(pointer == 2)
			//	Diary();
			else if(pointer == 3)
				DataScreen(1);
			else if(pointer == 4)
				Settings();
			else if(pointer == 5)
				exit(1);
		}
	}
	system("cls");
}
void Phone()
{
	system("cls");
	phone = false;
	//Menu
	char SearchLabel[128];
	char MessageLabel[128];
	char MusicLabel[128];
	char WeatherLabel[128];
	char MapLabel[128];
	char SubLabel1[128];
	char SubLabel2[128];
	// char SubLabel3[128];
	// char SubLabel4[128];
	// char SubLabel5[128];
	Localize(SearchLabel, 1, "/phone.txt");
	Localize(MessageLabel, 2, "/phone.txt");
	Localize(MusicLabel, 3, "/phone.txt");
	Localize(WeatherLabel, 4, "/phone.txt");
	Localize(MapLabel, 5, "/phone.txt");
	int app = 0;
	int pointer = 1;
	int j, i;
	enum apps
	{
		desktop = 0,
		message = 1,
		walkman = 2,
		weather = 3,
		map     = 4,
	};
	//Data for Map app
	int BorderY = 0, BorderX = 0;
	bool SpPressed = false, EPressed = false, QPressed = false;
	char map_phone[16][64] = {
			"     ## |,,,,~,,,,,,,,,,,,,,,,,,,",
			"        |,,,,,~~~~~~~~~~~~~~~~~~~",
			" #    # |,,,,,,,,,,,,,,,,,,,,,,,,",
			" #    # |,,,,,,,,,,,,,,,,,,,,,,,,",
			"________|,,,,_________ __________",
			"        |,,,,         | ##       ",
			"        |,,,,         | ##       ",
			"        |             |          ",
			"        |_____________|          ",
			"        |##### # #####|          ",
			"________|_____ # _____|__________",
			"        |                        ",
			"________|________________________",};
			int names[8][3] = {
				{foreststreet, 1, 3},
				{park_alley, 7,10},
				{parkstreet, 10,15},};
			/*char *helpscreen[64] = {
			"CONTROLS:      ",
			"[E] - center   ",
			"[Q] - set names",
			"[Space] - hide ",
			"[Esc] - quit   ",
			"LEGEND:        ",
			"H - safehouse  ",
			"S - store      ",
			"X - objective  ",};*/
	while(1)
	{
		//Setup
		COORD cursor;
		cursor.X = 0, cursor.Y = 0;
		SetConsoleCursorPosition(hConsole, cursor);
		Color(0,0);
		char UI[64][64] = {
		" #################",
		"#--:--      4G 75%#",
		"#[              q]#",
		"#                 #",
		"#                 #",
		"#                 #",
		"#                 #",
		"#                 #",
		"#                 #",
		"#                 #",
		"#                 #",
		"#                 #",
		"#-----------------#",
		"#  V  |  O  |  X  #",
		" ################# ",};

		for(j = 0; j < 64; j++){
			for(i = 0; i < 64; i++){
				if(UI[j][i] == '#')
					colorback[j][i] = 9, colorfront[j][i] = 9;
				else if(UI[j][i] == 'V')
					colorback[j][i] = 8, colorfront[j][i] = 10;
				else if(UI[j][i] == 'X')
					colorback[j][i] = 8, colorfront[j][i] = 12;
				else
					colorback[j][i] = 0, colorfront[j][i] = 15;
			}
		}

		if(app == desktop){
			TextOutput(UI, SearchLabel, 2,2, 16,15, 100);
			TextOutput(UI, MessageLabel, 3,1, 16,14, 100);
			TextOutput(UI, MusicLabel, 4,1, 16,13, 100);
			TextOutput(UI, WeatherLabel, 5,1, 16,11, 100);
			TextOutput(UI, MapLabel, 6,1, 16,10, 100);
		}
		else if(app == message){
			Localize(SubLabel1, 7, "/phone.txt");
			Localize(SubLabel2, 7, "/phone.txt");
			TextOutput(UI, SubLabel1, 3,1, 16,15, 100);
			TextOutput(UI, "[--:--]", 4,1, 16,15, 100);
			TextOutput(UI, SubLabel2, 5,1, 16,15, 100);
		}
		else if(app == walkman){
			Localize(SubLabel1, 10, "/phone.txt");
			Localize(SubLabel2, 11, "/phone.txt");
			TextOutput(UI, SubLabel1, 3,1, 16,15, 100);
			TextOutput(UI, SubLabel2, 4,1, 16,7, 100);
			TextOutput(UI, " Prev|Pause|Next", 7,1, 16,15, 100);
			TextOutput(UI, "  [A][Space][D]", 8,1, 16,15, 100);
		}
		else if(app == weather){
			int bgcolor = 0, frcolor = 15;
			for(i = 0; i < 6; i++){

				if(weatherforecast[hr+i] == 0)
					bgcolor = 12, frcolor = 14;
				else if(weatherforecast[hr+i] == rain)
					bgcolor = 1, frcolor = 15;
				else if(weatherforecast[hr+i] == snow)
					bgcolor = 15, frcolor = 7;

				TextOutput(UI, WeatherAt(hr+i), 2+i,1, bgcolor,frcolor, 100);
				TextOutput(UI, "12:00", 2+i,10, bgcolor,frcolor, 100);
			}
		}
		else if(app == map){
			/*for(j = 0; j < 7; j++){
				for(i = 0; i < 15; i++){
					map_phone[j][i] = loadedmap[32*j][16*i];
				}
			}*/
			
			for(j = 0; j < 8; j++){
				for(i = 0; i < 17; i++){
					UI[j+2][i+1] = map_phone[BorderY+j][BorderX+i];
					switch(UI[j+2][i+1])
					{
					case '#':
						colorback[j+2][i+1] = 15, colorfront[j+2][i+1] = 15;
						break;
					case '|':
						colorback[j+2][i+1] = 14, colorfront[j+2][i+1] = 14;
						break;
					case '-':
						colorback[j+2][i+1] = 14, colorfront[j+2][i+1] = 14;
						break;
					case ',':
						colorback[j+2][i+1] = 2, colorfront[j+2][i+1] = 2;
						break;
					case '~':
						colorback[j+2][i+1] = 11, colorfront[j+2][i+1] = 11;
						break;
					default:
						colorback[j+2][i+1] = 7, colorfront[j+2][i+1] = 7;
						break;
					}
					if(QPressed == 1){
						for(int k = 0; k < 8; k++)
							if(BorderY+j == names[k][1] && BorderX+i == names[k][2])
								TextOutput(UI, LocationName[names[k][0]],
								j+2, i+1, 0, 15, 6);
					}
				}
			}
			TextOutput(UI, "[Space] - help", 11,1, 16,15, 16);
			TextOutput(UI, LocationName[location], 10,1, 16,15, 16);
		}
		if(SpPressed == 1)
		{
			/*"LEGEND:        ",
			"H - safehouse  ",
			"S - store      ",
			"X - objective  ";*/
			TextOutput(UI, "CONTROLS:      ", 2,2, 0,15, 16);
			TextOutput(UI, "[E] - center   ", 3,2, 0,15, 16);
			TextOutput(UI, "[Q] - set names", 4,2, 0,15, 16);
			TextOutput(UI, "[Space] - hide ", 5,2, 0,15, 16);
			TextOutput(UI, "[Esc] - quit   ", 6,2, 0,15, 16);
			TextOutput(UI, "SIGNS:         ", 7,2, 0,15, 16);
		}

		//Output
		j = pointer+2;
		for(i = 0; i < 64; i++)
			if(UI[j][i] != '#' && app == desktop)
				colorback[j][i] = 15, colorfront[j][i] = 0;

		DrawWindow(UI);

		//Input
		if(app == 0)
		{
			if(GetAsyncKeyState(Esc))
				return;
			else if(GetAsyncKeyState(Enter))
				app = pointer;
			else if(GetAsyncKeyState('W') && pointer > 1)
				pointer--;
			else if(GetAsyncKeyState('S') && pointer < 4)
				pointer++;
			if(GetAsyncKeyState(VK_UP))
				pointer--;
			if(GetAsyncKeyState(VK_DOWN))
				pointer++;
		}
		if(app == message)
		{
			if(GetAsyncKeyState(Esc))
				app = 0;
			else if(GetAsyncKeyState('W'))
				pointer--;
			else if(GetAsyncKeyState('S'))
				pointer++;
			if(GetAsyncKeyState(VK_UP))
				pointer--;
			if(GetAsyncKeyState(VK_DOWN))
				pointer++;
		}
		if(app == walkman)
		{
			if(GetAsyncKeyState(Esc))
				app = 0;
			else if(GetAsyncKeyState('W'))
				pointer--;
			else if(GetAsyncKeyState('S'))
				pointer++;
			if(GetAsyncKeyState(VK_UP))
				pointer--;
			if(GetAsyncKeyState(VK_DOWN))
				pointer++;
		}
		if(app == weather)
		{
			if(GetAsyncKeyState(Esc))
				app = 0;
		}
		if(app == map){
			if(GetAsyncKeyState(Esc))
				app = 0;
			else if(GetAsyncKeyState('W') && BorderY > 0)
				BorderY--;
			else if(GetAsyncKeyState('S') && map_phone[BorderY+9][BorderX] != 0)
				BorderY++;
			else if(GetAsyncKeyState('A') && BorderX > 0)
				BorderX--;
			else if(GetAsyncKeyState('D') && map_phone[BorderY][BorderX+17] != 0)
				BorderX++;
			else if(GetAsyncKeyState(VK_SPACE))
				SpPressed = !SpPressed;
			else if(GetAsyncKeyState('Q'))
				QPressed = !QPressed;
			else if(GetAsyncKeyState('E'))
				EPressed = !EPressed;
		}
		else
		{
			if(GetAsyncKeyState(Esc))
				app = 0;
		}
	}
	_getch();
}
void LoadLightSource(int i, int power, int Y, int X, int R)
{
	lightsource[i][0] = power,
	lightsource[i][1] = Y,
	lightsource[i][2] = X,
	lightsource[i][3] = R;
}
void LightPrep()
{
	if(hr >= 20 || hr <= 5)
	{
		if(location == safehouse1)
		{
			LoadLightSource(0, 1, 9,10, 7);
		}
		else if(location == foreststreet)
		{
			LoadLightSource(0,	1, 30,17, 3);
			LoadLightSource(1,	1, 14,70, 5);
			LoadLightSource(2,	1, 14,70, 2);
		}
		else if(location == cyclelane)
		{
			LoadLightSource(0,	0,0,0,0);
			LoadLightSource(1,	0,0,0,0);
			LoadLightSource(2,	0,0,0,0);
		}
		else if(location == park_backentrance)
		{
			LoadLightSource(0,	0,0,0,0);
			LoadLightSource(1,	0,0,0,0);
			LoadLightSource(2,	0,0,0,0);
		}
		else if(location == park_front)
		{
			LoadLightSource(0,	0,0,0,0);
			LoadLightSource(1,	0,0,0,0);
			LoadLightSource(2,	0,0,0,0);
		}
		else if(location == park_alley)
		{
			LoadLightSource(0, 0,0,0,0);
			LoadLightSource(1, 0,0,0,0);
			LoadLightSource(2, 0,0,0,0);
		}
		else if(location == fleamarket)
		{
			LoadLightSource(0, 0,0,0,0);
			LoadLightSource(1, 0,0,0,0);
			LoadLightSource(2, 0,0,0,0);
		}
		else if(location == mall1f)
		{
			LoadLightSource(0, 0,0,0,0);
			LoadLightSource(1, 0,0,0,0);
			LoadLightSource(2, 0,0,0,0);
		}
		else if(location == mall2f)
		{
			LoadLightSource(0, 0,0,0,0);
			LoadLightSource(1, 0,0,0,0);
			LoadLightSource(2, 0,0,0,0);
		}
		else
		{
			LoadLightSource(0,	0,0,0,0);
			LoadLightSource(1,	0,0,0,0);
			LoadLightSource(2,	0,0,0,0);
		}
	}
	else {
		for (int i = 0; i < 32; i++) {
			lightsource[i][0] = 0;
			lightsource[i][1] = 0;
			lightsource[i][2] = 0;
			lightsource[i][3] = 0;
		}
	}
	
}
void ObjectsPrep(){
	if(location == safehouse1){
		LoadObject(0, iBurger, 9,5);
	}
}
void LocationPrep()
{
	LoadMap();//Load new map
	SetupNPC();//NPC load
	LightPrep();//Light sources load
	ObjectsPrep();//Load items and other interactive objects
}
void LogicWorld()
{
	//Mission
	if(mission > 0)
		Mission();
	else
		MissionTrigger();
	
	//Time
	sc++;
	if(sc >= 60)	sc = 0, mn++;
	if(mn >= 60)	mn = 0, hr++;
	if(hr >= 24)	hr = 0;

	//Lightning
	LightPrep();

	if(hr >= 20 || hr <= 5)
		light = -1;
	else
		light = 0;

	//Weather
	if(hr%6 == 0 && mn == 0 && sc == 0)
		weather = rand()%3;
	DetailsBehaviour(10);

	//Interaction
	if(interaction){
		if(loadedmap[y][x+1] == 11){
			DataScreen(0);
			hr += 8, energy = stamina;
			if(hr >= 24)
				hr -= 24;
		}
		else if(loadedmap[y][x+1] == 18){
			ItemBoxScreen();
		}
		else if(y == 40)
			Shop(inventory);
		interaction = false;
	}
}
void LogicPlayer()
{
	//Health
	if(HP < FullHP && energy == stamina)
		HP += 0.05;
	if(kissed)
		HP += FullHP * 0.25;
	if(cold)
		energy -= 0.02;
	if(hr == 0)
		energy = 0, tired = true;

	//Chase
	if(!recognized && wantedlevel > 0)
		wantedlevel -= 0.01;
	if(wantedlevel > 3)
		wantedlevel = 3;

	//Stamina
	if(energy < stamina)
		energy += 0.01;

	//Fight
	currentmove = 0;
	if(knocked && HP > 0 && energy > 1)
		knocked = false;
	if(gotdamage)
		gotdamage = false;
	if(weather == rain && water < 50)
		water++;

	//Pick up items
	for(int i = 0; i < 32; i++)
		if(actionobject[i][1] == y && actionobject[i][2] == x && actionobject[i][0] != iNone){
			int j;
			for(j = 1; j < 10; j++)
				if(inventory[j] == iNone){
					cout << "<+ " << item[actionobject[i][0]].name << ">" << endl;
					Sleep(500);
					inventory[j] = actionobject[i][0];
					actionobject[i][0] = 0;
					break;
				}
			if(j == 10){
				Color(0,12);
				cout << "<Full inventory>" << endl;
				Color(0,15);
			}
		}
	//Role play
	if(kissed)
		kissed = false;

	//Game Over
	if(hr == 2 && tired)
		hr += 9,
		gameover = true;
	if(HP <= 0)
		gameover = true;
}
void Logic()
{
	int prevlocation = location;
	if(paused)
		pause();
	if(phone)
		Phone();
	LogicWorld();
	LogicPlayer();
	LocationSwitch();
	if(location != prevlocation)
		LocationPrep();
}
void UpdateMap()
{
	for(int j = 0; j < MapSizeY; j++)
		for(int i = 0; i < MapSizeX; i++){
			loadedmap[j][i] = currentmap[j][i];
			op++;
		}
}

void Briefing()
{
	/*if(mission == newworld)
		cout << "...���� ���� � ����� ������!..." << endl;
	else if(mission == geeksquad)
		cout << "...�...� �����..." << endl;
	else if(mission == nightbrawl)
		cout << "...�� �������, �����..." << endl;
	else if(mission == spit)
		cout << "...�� � ���� �������..." << endl;
	else if(mission == sunrise)
		cout << "...������� �����?..." << endl;*/
	Sleep(450);
}
void game()
{
	Color(0,15);
	system("cls");
	Briefing();
	//PlaySound(L"audio/ost/test.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	while(1)
	{
		system("cls");

		//LoadObjects(0);
		gameover = false;

		if(skill[StaminaLvl1].ismastered)
			stamina = stamina*1.25;
		if(skill[StaminaLvl2].ismastered)
			stamina = stamina*1.5;

		HP = FullHP, energy = stamina;
		HandX = x+1;
		weather = leaffall;
		LocationPrep();
		while(1)
		{
			op = 0;
			UpdateMap();//Setting up
			LightMapLoad();
			Update();

			Video(loadedmap);//Output
			Audio();

			Logic();//Game actions and logic
			AI();
			Physics();

			if(gameover){
				Sleep(1500);
				GameOverScreen();
				break;
			}
			else if(restart || mainmenu)
				break;

			Input();//Input
		}
	}
}
void menu()
{
	char Title[64];
	char LoadGameButton[32];
	char NewGameButton[32];
	char SettingsButton[32];
	char QuitGameButton[32];
	int j, i;
	int pointer = 1;
	Localize(Title, 6, "/menu.txt");
	Localize(LoadGameButton, 7, "/menu.txt");
	Localize(NewGameButton, 8, "/menu.txt");
	Localize(SettingsButton, 9, "/menu.txt");
	Localize(QuitGameButton, 10, "/menu.txt");
	system("cls");
	CONSOLE_CURSOR_INFO cursorinfo;
	cursorinfo.bVisible = 0;
	SetConsoleCursorInfo(hConsole, &cursorinfo);

	while(1)
	{
		COORD cursor;
		cursor.X = 0, cursor.Y = 0;
		SetConsoleCursorPosition(hConsole, cursor);
		Color(15,0);

		char UI[64][64];
		for (j = 0; j < 14; j++)
			for (i = 0; menupattern[j][i] != 0; i++)
				UI[j][i] = menupattern[j][i];

		for(j = 0; j < 64; j++)
			for(i = 0; i < 64; i++)
				colorback[j][i] = 15, colorfront[j][i] = 0;
		
		TextOutput(UI, "TEEN'S RISE", 5,2, 16,0, 14);
		for(i = 0; i < 4; i++)
			TextOutput(UI, "..............", 2+i,20, 16,0, 14);
		TextOutput(UI, "_________________", 10,19, 16,0, 17);

		TextOutput(UI, Title, 2,2, 16,0, 12);
		TextOutput(UI, LoadGameButton, 2,20, 16,0, 30);
		TextOutput(UI, NewGameButton, 3,20, 16,0, 30);
		TextOutput(UI, SettingsButton, 4,20, 16,0, 30);
		TextOutput(UI, QuitGameButton, 5,20, 16,0, 30);
		TextOutput(UI, backhint, 11,26, 16,0, 30);
		TextOutput(UI, selecthint, 12,28, 16,0, 30);
		TextOutput(UI, KeyName(Esc), 11,20, 7,0, 30);
		TextOutput(UI, KeyName(Enter), 12,20, 7,0, 30);

		j = 1+pointer;
		for(i = 20; i < 35; i++)
			colorback[j][i] = 0, colorfront[j][i] = 15;

		GetCursorPos(&p);
		MouseY = p.y / SensivityY, MouseX = p.x / SensivityX;
		UI[MouseY][MouseX] = '+';
		colorfront[MouseY][MouseX] = 12;

		DrawWindow(UI);

		if (MouseX >= 20 && MouseY >= 2 && MouseY <= 5)
			pointer = MouseY - 1;
		if(GetAsyncKeyState('W') && pointer > 1)
			pointer--;
		else if(GetAsyncKeyState('S') && pointer < 4)
			pointer++;
		if(GetAsyncKeyState(VK_UP) && pointer > 1)
			pointer--;
		if(GetAsyncKeyState(VK_DOWN) && pointer < 4)
			pointer++;
		else if(GetAsyncKeyState(Enter) || GetAsyncKeyState(VK_LBUTTON))
		{
			if(pointer == 1){
				DataScreen(1);
				if(y != 0 && x != 0)//If data are loaded: end main menu loop and start the game
					return;
			}
			else if(pointer == 2){
				Intro();
				return;
			}
			else if(pointer == 3)
				Settings();
			else if(pointer == 4)
				exit(1);
		}
	}
}
void Startup()
{
	system("cls");
	char text[128];
	ifstream file;
	if(strcmp(language, "english") == 0)
		file.open("translate/english/disclaimer.txt");
	else if(strcmp(language, "russian") == 0)
		file.open("translate/russian/disclaimer.txt");
	if(!file.is_open())
	{
		cout << "Error: can't load disclaimer text file!" << endl;
		Sleep(2000);
		return;
	}
	for(int i = 1; !file.eof(); i++){
		file.getline(text, 128);
		cout << text << endl;
	}
	file.close();
	Sleep(3000);
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t\t  ");
	Color(9,15);
	printf("****************************\n");
	Color(0,15);
	printf("\t\t\t ");
	Color(9,15);
	printf("*       Bluscreendez       *\n");
	Color(0,15);
	printf("\t\t\t");
	Color(9,15);
	printf("****************************\n");
	Color(0,15);
	TCHAR name[UNLEN + 1];
	DWORD size = UNLEN + 1;
	if (GetUserName((TCHAR*)name, &size))
		wcout << L"\n\t\t\tHello, " << name << L"!\n";
	else
		cout << "\n\t\t\tHello, noname!\n";
	Sleep(2000);
}
void GlobalLocalize()
{
	int j, i;
	for(i = 0, j = 0; i < 42; i+=3, j++)
		Localize(weaponID[j].name, 1+i, "/weapons_items.txt");
	for(i = 0, j = 0; i < 75; i+=3, j++)
		Localize(item[j].name, 1+i, "/weapons_items.txt");
	for(i = 1, j = 0; i < 75; i+=3, j++)
		Localize(item[j].description, 1+i, "/weapons_items.txt");

	for(i = 1; i < 16; i++)
		Localize(line[player][i-1], i, "/ingame/lines_alex.txt");
	for(i = 1; i < 16; i++)
		Localize(line[npc_geek][i-1], i, "/ingame/lines_geek.txt");
	for(i = 1; i < 16; i++)
		Localize(line[npc_doomer][i-1], i, "/ingame/lines_doomer.txt");
	for(i = 1; i < 16; i++)
		Localize(line[npc_zoomer][i-1], i, "/ingame/lines_zoomer.txt");
	for(i = 1; i < 16; i++)
		Localize(line[npc_gopnic][i-1], i, "/ingame/lines_gopnic.txt");

	Localize(selecthint, 1, "/menu.txt");
	Localize(backhint, 2, "/menu.txt");
	Localize(navigatehint, 3, "/menu.txt");

	Localize(SavingLabel, 21, "/menu.txt");
	Localize(SavingDoneLabel, 22, "/menu.txt");
	Localize(SavingFailedLabel, 23, "/menu.txt");
	Localize(LoadingLabel, 24, "/menu.txt");

	Localize(NextButton, 2, "/ingame.txt");
	Localize(SkipButton, 3, "/ingame.txt");

	Localize(HoldLabel, 6, "/ingame.txt");
	Localize(RapidlyPressLabel, 7, "/ingame.txt");

	for(i = 1; i < 32; i++)
		Localize(LocationName[i-1], i, "/locationnames.txt");//Location names
}
void main()
{
	// HANDLE hCon = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleTitle("Teen's Rise");//Teen's Rise title
	setlocale(LC_ALL, "rus");
	system("color f");//white font
	
	/*CONSOLE_FONT_INFOEX cfi;
    ZeroMemory(&cfi, sizeof(CONSOLE_FONT_INFOEX));
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    cfi.nFont = 6;
    cfi.dwFontSize.X = 16;
    cfi.dwFontSize.Y = 12;
    cfi.FontFamily = 54; //Lucida Console
    cfi.FontWeight = 400;
    lstrcpyW(cfi.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);*/

	//LPPOINT pPnt;
	//pPnt = static_cast<LPPOINT>(malloc(sizeof(*pPnt)));

	cout << 
		"LANGUAGE:" << endl <<
		"English - 1" << endl <<
		"Russian - 2" << endl;

	while(1)
	{
		if(GetKeyState('1')){
			language = "english";
			break;
		}
		else if(GetKeyState('2')){
			language = "russian";
			break;
		}
	}
	system("cls");
	cout << ". . .";
	GlobalLocalize();
	//Localize constant data's in game: weapons/items names and descriptions
	Startup(); //Disclaimer and (c) Bluscreendez logo
	while(1){ //Main loop
		menu();
		game();
	}
}