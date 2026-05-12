#pragma once
#include <iostream>
#include <conio.h>
#include "ai.h"
using namespace std;

const char *missionname;
char objective[128];
const char *failreason;
int obj;
int script[8] = {1,0,1,}; //Mainscript, extra, cutscene script
char captions[128];
char NextButton[128];
char SkipButton[128];

enum scriptmeanings
{
	mainscript = 0,
	subscript = 1,
	cutscene = 2,
};
bool scriptresume = false;
bool gameover = false;
bool mainmenu = false;
bool restart = false;
int subtitletime = 0;
enum CameraTypes
{
	actor = 0,
	point = 1,
	camposY = 0,
	camposX = 1,
};
int cameracenter[2], cameratype = actor;
enum Missions
{
	//Free roam
	freeroam = 0,
	//Prologue
	newworld,
	//Geek chapter
	geeksquad,
	bottleshooter,
	nightbrawl,
	//Doomer chapter
	cuttingarms,
	batduel,
	blindkaraoke,
	//Zoomer chapter
	artofvandalism,
	pubertyyazva,
	hermitness,
	//Offnic chapter
	spit,			//Denial
	revengeance,	//Anger
	deal,			//Bargaining
	m_20,			//Depression
	realizing,		//Acceptance
	//Final
	sunrise,
};

int missionstart[32][3] = {//location,y,x
	{0,0,0},//Free roam
	{0,0,0},//Prologue
	{park_front,25,48},//Geek
	{safehouse2,0,0},
	{},
	{},
	{foreststreet,},
	{park_alley,0,0},//Doomer
	{park_front,0,0},
	{},
	{},
	{park_front,0,0},
	{},//Zoomer
	{},
	{},
	{},
	{},
	{},//Offnic
	{},
	{},
	{},
	{},
	{},//Final
	{},};

void Subtitle(char text[128], int timelimit)
{
	if(subtitletime < timelimit){
		cout << "\t\t" << text;
		subtitletime++;
	}
	else
		subtitletime = 0;
}
void Caption(char text[128])
{
	//TextOutput(screen, colorback, colorfront, text, sizeY*2-3,3, 0,15, 32);
	//subtitle = text;
	cout << "\n\t\t" << text << endl;
	cout << "\t\t(" << KeyName(Enter) << ". " << HoldLabel << " " << SkipButton << ")";
	Sleep(200);
	while(1){
		if(GetAsyncKeyState(Enter) || GetAsyncKeyState(VK_LBUTTON))
			break;
	}
	system("cls");
}
void Intro()
{
	system("cls");
	y = 16, x = 15, location = safehouse1;
	hr = 9, mn = 0;
	ifstream file;
	if(strcmp(language, "english") == 0)
		file.open("translate/english/story/intro.txt");
	else if(strcmp(language, "russian") == 0)
		file.open("translate/russian/story/intro.txt");

	for(int i = 0; i < 6; i++){
		file.getline(captions, 128);
		Caption(captions);
	}
	file.close();
	mission = 1;
}
void Ending()
{
	int i;
	ifstream file("translate/english/story/m_1.txt");
	for(i = 0; !file.eof(); i++){
		file.getline(captions, 128);
		Caption(captions);
	}
	file.close();
}
void TotalResults()
{
	int likes = 0;
	char heart = 3;
	cout << "[TOTAL RESULTS]" << endl;
	cout << "Play time: " << totalplaytime/3600 << " ingame hours" << endl;
	cout << "Continues: " << knockedout+arrested+failed << endl;
	cout << "Sleeps: " << endl;
	cout << "Taken damage: " << 0 << endl;
	cout << "Skills got: " << 0 << endl;
	cout << "Money remains: " << money << endl;
	if(totalplaytime/3600 < 336) 
		likes += (336 - totalplaytime/3600);
	if(knockedout+arrested+failed < 100)
		likes += 100 - (knockedout+arrested+failed);
	likes += int(money/100);
	Color(0,12);
	cout << heart << " " << likes << endl;
	_getch();
}
void m_1newworld()
{
	if(script[mainscript] == 1){
		Localize(captions, script[cutscene], "/story/m_1.txt");
		Caption(captions);
		if(script[cutscene] == 2){
			script[cutscene] = 1, script[mainscript]++;}
		script[cutscene]++;
	}
	else if(script[mainscript] == 2){
		Localize(captions, 3, "/story/m_1.txt");
		Caption(captions);
		//Localize(objective, 4, "/story/m_1.txt");
		script[0]++;
	}
	else if(script[mainscript] == 3 && location != safehouse1){
		Localize(captions, 5, "/story/m_1.txt");
		Caption(captions);
		script[0]++;
	}
	else if(script[mainscript] == 4){
		if(location == park_front){
			LoadNPC(0, 26, 48, fraction_geek, ai_off, 0, 0, 5, 5);
			script[3] = 1;
		}
		if(location == park_front && y == 25 && x == 45)
			script[0]++;
	}
	else if(script[0] == 5){
		Localize(captions, 4+script[cutscene], "/story/m_1.txt");
		Caption(captions);
		script[cutscene]++;
		if(script[cutscene] == 17)
			script[cutscene] = 1, script[mainscript]++,
			//objective = "[���� � ������� �� ������ �����]",
			hr = 19, mn = 48;
	}
	else if(script[0] == 6){
		if(21+script[cutscene] == 22){
			LoadNPC(3, 26, 52, fraction_gopnic, neutral, 0, iSeeds, 5, 5);
			LoadNPC(4, 28, 52, fraction_gopnic, neutral, 0, iSeeds, 5, 5);
		}
		else if(21+script[cutscene] == 32){
			//Punk goes to Anton
			GoTo(3, npc[0][npc_y],npc[0][npc_x]+1);
			if(npc[3][npc_y] == npc[0][npc_y] && npc[3][npc_x] == npc[0][npc_x]+1){}
			else	script[cutscene]--;
		}
		else if(21+script[cutscene] == 33){
			npc[0][npc_HP] = 0;//Anton falls
		}
		else if(21+script[cutscene] == 38)
		{
			GoTo(3, y,x);
			if(npc[3][npc_y] == y && npc[3][npc_x] == x+3){}
			else	script[cutscene]--;//Punk goes to Alex
		}
		else{
			Localize(captions, 21+script[cutscene], "/story/m_1.txt");
			Caption(captions);
		}
		script[cutscene]++;
		if(21+script[cutscene] == 40)
			npc[3][npc_attitude] = angry,
			npc[4][npc_attitude] = angry,
			script[cutscene] = 1, script[mainscript]++;
			//objective = "[������ �����]";
	}
	else if(script[0] == 7){
		if(location == safehouse1)
			script[0]++;
	}
	else if(script[0] == 8){
		if(script[cutscene] == 1)
			x = 12;
		if(script[cutscene] == 3){
			LoadNPC(3, 16, 25, fraction_gopnic, angry, 0, iSeeds, 5, 5);
			LoadNPC(4, 18, 25, fraction_gopnic, angry, 0, iSeeds, 5, 5);
		}
		Localize(captions, 40+script[cutscene], "/story/m_1.txt");
		Caption(captions);
		script[cutscene]++;
		if(script[cutscene] == 7)
			script[cutscene] = 1, script[0]++;
	}
	else if(script[mainscript] == 9){
		//objective == "[������������]";
		if(location == safehouse1 && hr >= 20)
			script[mainscript]++;
	}
	else if(script[mainscript] == 10)
	{
		Localize(captions, 50+script[cutscene], "/story/m_1.txt");
		Caption(captions);
		script[cutscene]++;
		if(script[cutscene] == 6)
			script[cutscene] = 1, script[mainscript]++;
	}
	else if(script[0] == 11){
		Localize(captions, 56+script[cutscene], "/story/m_1.txt");
		if(script[cutscene] == 1){
			cameratype = point, cameracenter[camposY] = 12, cameracenter[camposX] = 15;
			Caption(captions);
		}
		else if(script[cutscene] == 6){
			cameratype = actor;
			Caption(captions);
		}
		else
			Caption(captions);
		
		script[cutscene]++;
		if(script[cutscene] == 7)
			script[cutscene] = 1, script[mainscript]++;
	}
	else if(script[0] == 12){
		y = 8, x = 15;
		Localize(captions, 63+script[cutscene], "/story/m_1.txt");
		Caption(captions);
		script[cutscene]++;
		if(script[cutscene] == 6)
			script[cutscene] = 1, script[0]++;
	}
	if(script[mainscript] == 13){
		mission = 0, script[0] = 1, m_cleared++;
		hr = 9, mn = 0, sc = 0;
		SaveData(0);
	}
}
void m_2finding()
{
	if(script[0] == 1){
		Localize(captions, script[cutscene], "/story/m_2.txt");
		Caption(captions);
		script[cutscene]++;
		if(script[cutscene] == 5)
			script[cutscene] = 1, script[0]++;
	}
	if(script[0] == 2){
		if(location == 0 && y == 0 && x == 0)
			script[0]++;
	}
	else if(script[0] == 3){
		Localize(captions, script[cutscene], "/story/m_2.txt");
		script[cutscene]++;
		if(script[cutscene] == 9)
			script[cutscene] = 1, script[0]++;
			//objective = "����� �� ���";
	}
	else if(script[0] == 4 && location == parkstreet){
		//Localize("/story/m_2.txt");
		Caption("");
		script[cutscene]++;
		if(script[cutscene] == 3)
			script[cutscene] = 1, script[0]++;
	}
	else if(script[0] == 5){
		Caption("");
		script[0]++;
	}
	else if(script[0] == 6){
		mission = 0, m_cleared++, script[0] = 1;
		SaveData(0);
	}
}
void m_3bottleshooter()
{
	if(script[0] == 1)
	{
		Localize(captions, script[cutscene], "/story/m_3.txt");
		Caption(captions);
		if(script[cutscene] == 1)
			script[0]++;
	}
	else if(script[0] == 2)
	{
		if(script[1] == 1){
			weapon[ranged1] = iRubberGun;
		}
		else if(script[1] == 2){
			Localize(captions, 2, "/story/m_3.txt");
			Caption(captions);
			if(weaponslot == ranged1)
				script[1]++;
		}
		else if(script[1] == 3){
			Localize(captions, 3, "/story/m_3.txt");
			Caption(captions);
			script[1]++;
		}
		else if(script[1] == 4){
			Localize(captions, 4, "/story/m_3.txt");
			Caption(captions);
			script[1]++;
		}
		else if(script[1] == 5){
			Localize(captions, 5, "/story/m_3.txt");
			Caption(captions);
			script[1]++;
		}
		//Training with rubber gun
	}
	else if(script[0] == 3)
	{
		weapon[ranged2] = iBottleGun;
		//Bottle gun
	}
	else if(script[0] == 4)
	{
		//Mission clear
		weapon[ranged1] = 0;
		weapon[ranged2] = 0;
		mission = 0, m_cleared++, script[0] = 1;
		SaveData(0);
	}
}
void m_4nightbrawl()
{
	if(hr < 22 || hr > 05){
		Caption("Come back later at 22:00-05:00");
		mission = 0;
	}
	if(script[0] == 1){
		Localize(captions, script[cutscene], "/story/m_5.txt");
		Caption(captions);
		script[0]++;
	}
	else if(script[0] == 2){
		//objective = "������� � ������ ����";
		if(y == 30 && x == 42)
			script[0]++;
	}
	else if(script[0] == 3){
		//objective = "���� � ������ � ���������� ���";
		if(y == 30 && x == 42)
			script[0]++;
	}
	else if(script[0] == 4){
		//objective = "�������� ������ � �������� ��� �� ��������� �����";
		if(y == 30 && x == 42)
			script[0]++;
	}
	else if(script[0] == 5){
		Localize(captions, script[cutscene], "/story/m_5.txt");
		Caption(captions);
		script[0]++;
	}
	else if(script[0] == 6){
		mission = 0, m_cleared++, script[0] = 1;
		SaveData(0);
	}
}
void m_cuttingarms()
{
	if(npc[0][npc_HP] > 0)
		npc[0][npc_HP] -= 0.01;
	if(script[0] == 1)
	{
		
		Localize(captions, script[cutscene], "/story/m_6.txt");
		Caption(captions);
		script[cutscene]++;
	}
	if(script[0] == 2){
		//objective = "���������� ������, ���� �� ���";
		if(y == 30 && x == 42)
			script[0]++;
	}
	else if(script[0] == 3){
		if(script[cutscene] == 3){
			if(npc[0][npc_HP] <= 0){
				Caption("");
				gameover = true;
			}
			else
				Caption("");
		}
		script[cutscene]++;
	}
	else if(script[0] == 4){
		//objective = "���������� � �������� ������";
		if(y == 30 && x == 42)
			script[0]++;
	}
	else if(script[0] == 5){
		Caption("");
		script[0]++;
	}
	else if(script[0] == 6){
		//objective = "�������������� ������";
		if(npc[0][npc_HP] <= 2)
			script[0]++;
	}
	else if(script[0] == 7){
		//objective = "������� ������ � ��������";
		if(y == 30 && x == 42)
			script[0]++;
	}
	else if(script[0] == 8){
		Caption("");
		script[0]++;
	}
}
void m_batduel()
{
	if(script[0] == 1)
	{
		if(skill[ApologizeTeens].ismastered == true)
			Caption("");
		script[0]++;
	}
	if(script[0] == 2)
	{
		//objective = "����������� ������";
		if(npc[0][npc_HP] <= 0 || npc[0][npc_attitude] != angry)
			script[0]++;
	}
	if(script[0] == 3)
	{
		Localize(captions, script[cutscene], "/story/m_2.txt");
		Caption(captions);
		script[cutscene]++;
	}
	if(script[0] == 4)
	{
		if(script[1] == 0){
			doomerrespect += 0.2;
			Caption("<�������� ������� +20%>");\
		}
		if(script[1] == 1){
			doomerrespect += 0.1;
			Caption("<�������� ������� +10%>");
		}
		if(script[1] == 2){
			doomerrespect += 0.25;
			Caption("<�������� ������� +25%>");
		}
		script[0] = 0, script[1] = 0, mission = 0;
		SaveData(0);
	}
}
void m_blindkaraoke()
{
	if(script[0] == 1)
	{
		Localize(captions, script[cutscene], "/story/m_2.txt");
		Caption(captions);
	}
	else if(script[0] == 2)
	{
		
	}
	else if(script[0] == 3)
	{
		script[0] = 0, script[1] = 0, mission = 0;
	}
}
void m_videoclip()
{

}
void m_artofvandalism()
{
	if(script[0] == 1)
	{
		//objective = "���� � ����";
		weapon[5] = iPaintSpray;
		script[0]++;
	}
	else if(script[0] == 2)
	{
		//objective = "���������� ������ � ����";
		script[0]++;
	}
	else if(script[0] == 3)
	{
		//objective = "������� ������ �� ������";
		script[0]++;
	}
	else if(script[0] == 4)
	{
		Caption("<+1000 ������>");
		money += 1000;
		mission = 0, script[0] = 0;
		SaveData(0);
	}
}
void m_spit()
{
	if(script[0] == 1){
		if(script[cutscene] == 1){
			HP -= 4,
			weapon[1] = 0, weapon[2] = 0, 
			weapon[3] = 0, weapon[4] = 0;
			inventory[1] = 0, inventory[2] = 0,
			inventory[3] = 0, inventory[4] = 0;
			if(money >= 500)
				money -= 200;
		}
		Localize(captions, script[cutscene], "/story/m_20.txt");
		Caption(captions);
		script[cutscene]++;
	}
	else if(script[0] == 2){
		//objective = "��������� �� ����������� ������";
		script[0]++;
	}
	else if(script[0] == 3){
		//objective = "���������� � ����";
		if(location != mountaintop)
			script[0]++;
	}
	else if(script[0] == 4){
		//objective = "�������� ����";
		if(location == mountainstreet_playgrounds)
			script[0]++;
	}
	else if(script[0] == 5){
		mission = 0, script[0] = 0;
		SaveData(0);
	}
}
void m_sunrise()
{
	if(script[0] == 1){
		if(location == mountainbase)
			script[0]++;
	}
	else if(script[0] == 2){
		if(npc[0][npc_HP] <= 0)
			script[0]++;
	}
	else if(script[0] == 3){

	}
	else if(script[0] == 4){
		//Credits();
		Ending();
		script[0]++;
	}
	else if(script[0] == 5){
		money += 5000;
		//Caption("<+5000 ������>");
		doomerrespect += 0.75, geekrespect += 0.75,
		zoomerrespect += 0.75, gopnicrespect += 0.75;
		//Caption("<��������� ���� �� +75%>");
		//Caption("");
		TotalResults();
		//Caption("");
		mission = 0, script[0] = 1;
		SaveData(0);
	}
}
void Mission()
{
	if(mission == newworld)				{m_1newworld();			}
	else if(mission == 2)				{m_2finding();			}
	else if(mission == bottleshooter)	{m_3bottleshooter();	}
	else if(mission == nightbrawl)		{m_4nightbrawl();		}
	else if(mission == cuttingarms)		{m_cuttingarms();		}
	else if(mission == batduel)			{m_batduel();			}
	else if(mission == blindkaraoke)	{m_blindkaraoke();		}
	else if(mission == artofvandalism)	{m_artofvandalism();	}
	else if(mission == spit)			{m_spit();				}
	else if(mission == sunrise)			{m_sunrise();			}
}
void MissionTrigger()
{
	if(location == missionstart[m_cleared+1][0] && 
	y == missionstart[m_cleared+1][1] && x == missionstart[m_cleared+1][2])
		mission = m_cleared+1;
}