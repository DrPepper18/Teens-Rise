#pragma once
#include <winuser.h>
#include <conio.h>
#include <xinput.h>
#include <math.h>
#include "GameMechanics.h"

enum ControllerType {
	keyboard = 1,
	Xbox_gamepad,
	DualShock,
};
int InputDevice = keyboard;
enum XY {
	xPos = 0, yPos = 1,
};

enum Controls
{
	Up = 0,
	Down,
	Left,
	Right,
	Sprint,
	Crawl,
	Action,
	Punch,
	Aim,
	Weapon,
	Slot1,
	Slot2,
	Slot3,
	Slot4,
	UseItem,
}; 
int KeyboardControlsType[2][16] = {
	//Default
	{'W','S','A','D',VK_LSHIFT,VK_CONTROL,'E','F',VK_SPACE,VK_LBUTTON,'1','2','3','4','Q'},
	//Keyboard Only
	{'W','S','A','D',VK_SPACE,'C','E','F','L','J','1','2','3','4','Q'}
};
int XboxControlsType[4][16] = {
	{//Default
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		XINPUT_GAMEPAD_A,
		XINPUT_GAMEPAD_B,
		XINPUT_GAMEPAD_Y,
		XINPUT_GAMEPAD_X,
		XINPUT_GAMEPAD_LEFT_SHOULDER,
		XINPUT_GAMEPAD_RIGHT_SHOULDER,
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT
	},
	{//Alternative
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		XINPUT_GAMEPAD_A,
		XINPUT_GAMEPAD_B,
		XINPUT_GAMEPAD_Y,
		XINPUT_GAMEPAD_X,
		XINPUT_GAMEPAD_LEFT_SHOULDER,
		XINPUT_GAMEPAD_RIGHT_SHOULDER,
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT
	},
};

int Keyboard[16] = 
{
	KeyboardControlsType[0][Up],
	KeyboardControlsType[0][Down],
	KeyboardControlsType[0][Left],
	KeyboardControlsType[0][Right], 

	KeyboardControlsType[0][Sprint],
	KeyboardControlsType[0][Crawl], 
	KeyboardControlsType[0][Action], 
	KeyboardControlsType[0][Punch], 
	KeyboardControlsType[0][Aim],
	KeyboardControlsType[0][Weapon],
	
	KeyboardControlsType[0][Slot1],
	KeyboardControlsType[0][Slot2],
	KeyboardControlsType[0][Slot3],
	KeyboardControlsType[0][Slot4],
	KeyboardControlsType[0][UseItem]
};

int X360gamepad[16] = {
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
};
int KeyboardType = 0, XboxType = 0, DualShockType = 0;

int inputstory[16] = {0,0,0,0,0,0,0,0,0,0};

void XboxControllerInput()
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	bool IsPressed = state.Gamepad.wButtons;
	float LT = state.Gamepad.bLeftTrigger;
	float RT = state.Gamepad.bRightTrigger;
	int X = 0, Y = 1;
	float LS[2] = {state.Gamepad.sThumbLX, state.Gamepad.sThumbLY};
	float RS[2] = {state.Gamepad.sThumbRX, state.Gamepad.sThumbRY};

	if((IsPressed & XINPUT_GAMEPAD_START) || GetAsyncKeyState(Esc)) 
		paused = true;
	if(IsPressed & XINPUT_GAMEPAD_BACK) 
		phone = true;
	if(IsPressed & XINPUT_GAMEPAD_A) 
		cout << "(A) " << endl;
	if(IsPressed & XINPUT_GAMEPAD_B) 
		cout << "(B) " << endl;
	if(IsPressed & XINPUT_GAMEPAD_X) 
		cout << "(X) " << endl;
	if(IsPressed & XINPUT_GAMEPAD_Y) 
		cout << "(Y) " << endl;
	if(IsPressed & XINPUT_GAMEPAD_LEFT_SHOULDER) 
		cout << "[LB] " << endl;
	if(IsPressed & XINPUT_GAMEPAD_RIGHT_SHOULDER) 
		cout << "[RB] " << endl;
	if(IsPressed & XINPUT_GAMEPAD_LEFT_THUMB) 
		cout << "(LS) " << endl;
	if(IsPressed & XINPUT_GAMEPAD_RIGHT_THUMB) 
		cout << "(RS) " << endl;

}
void KeyboardInput()
{
	LockOn = 0;
	if(GetAsyncKeyState(VK_ESCAPE) && framemodulus % 2 == 0)
		paused = true;
	if(GetAsyncKeyState(Tab))
		phone = true;
	if(GetAsyncKeyState(Keyboard[Up])){
		if(y > 0 && objectmodel[loadedmap[y-1][x]][4] == 0)
			y--;
		if(GetAsyncKeyState(Keyboard[Sprint]))
			if(y > 0 && objectmodel[loadedmap[y-1][x]][4] == 0 && energy > 0 && !crawling)
				y--, energy -= 0.07;
	}
	if(GetAsyncKeyState(Keyboard[Down])){
		if(objectmodel[loadedmap[y+1][x]][4] == 0 && y < MapSizeY-1)
			y++;
		if(GetAsyncKeyState(Keyboard[Sprint]))
			if(objectmodel[loadedmap[y+1][x]][4] == 0 && y < MapSizeY-1 && energy > 0 && !crawling)
				y++, energy -= 0.07;
	}
	if(GetAsyncKeyState(Keyboard[Left])){
		if(x > 0 && objectmodel[loadedmap[y][x-1]][4] == 0)
			x--, HandX = x-1;
		if(GetAsyncKeyState(Keyboard[Sprint]))
			if(x > 0 && objectmodel[loadedmap[y][x-1]][4] == 0 && energy > 0 && !crawling)
				x--, energy -= 0.07, HandX = x-1;
	}
	if(GetAsyncKeyState(Keyboard[Right])){
		if(x < MapSizeX && objectmodel[loadedmap[y][x+1]][4] == 0)
			x++, HandX = x+1;
		if(GetAsyncKeyState(Keyboard[Sprint]))
			if(x < MapSizeX && objectmodel[loadedmap[y][x+1]][4] == 0 && energy > 0 && !crawling)
				x++, energy -= 0.07, HandX = x+1;
	}
	if(GetAsyncKeyState(Keyboard[Crawl])){
		crawling = !crawling;
	}
	if(GetAsyncKeyState(Keyboard[Weapon])){
		if(weapon[weaponslot] == 0)
			Move(player, grapple);
		else
			Attack(weapon[weaponslot]);
	}
	if(GetAsyncKeyState(Keyboard[Aim]) || GetAsyncKeyState(VK_RBUTTON)){
		LockingOn();
		if(GetAsyncKeyState(Keyboard[Sprint]))
			if(GetAsyncKeyState(Keyboard[Up]) || GetAsyncKeyState(Keyboard[Down]) || 
				GetAsyncKeyState(Keyboard[Left]) || GetAsyncKeyState(Keyboard[Right]))
				Move(player, dodge);
	}
	if(GetAsyncKeyState('Q')) {
		Use(inventory[quickaccessitem]);
	}
	if(GetAsyncKeyState(Keyboard[Action])){
		interaction = true;
	}
	if(LockOn != 0 && GetAsyncKeyState('E'))
	{
		Caption(line[player][compliment]);
		if(skill[ApologizeTeens].ismastered)
			geekheat = 0, doomerheat = 0, gopnicheat = 0;
		else if(skill[ApologizePolice].ismastered)
			wantedlevel = 0;
	}
	if(LockOn != 0 && GetAsyncKeyState('C'))
	{
		Caption(line[player][taunt]);
		Caption(line[npc[LockOn][npc_fraction]][anger]);
		npc[LockOn][npc_attitude] = angry;
		wantedlevel += stronglanguage.wantedlevel;
		if(wantedlevel > 3)
			wantedlevel = 3;
	}
	if(GetAsyncKeyState('R') || GetAsyncKeyState('0'))
		weaponslot = 0;
	if(GetAsyncKeyState(Keyboard[Slot1]))	weaponslot = 1;
	if(GetAsyncKeyState(Keyboard[Slot2]))	weaponslot = 2;
	if(GetAsyncKeyState(Keyboard[Slot3]))	weaponslot = 3;
	if(GetAsyncKeyState(Keyboard[Slot4]))	weaponslot = 4;
	if(GetAsyncKeyState('5'))	weaponslot = 5;
	if(GetAsyncKeyState('`'))	1;//cmd(NULL);
	if(GetAsyncKeyState(VK_F5))	SaveData(2);
	if(GetAsyncKeyState(VK_F6))	HP = -1;
	if(GetAsyncKeyState(VK_F7))	mn = 59, sc = 59;
	if (GetAsyncKeyState(VK_F8)) cameratype = !cameratype;
}
void Input()
{
	if(InputDevice == keyboard)
		KeyboardInput();
	else if(InputDevice == Xbox_gamepad)
		XboxControllerInput();
}