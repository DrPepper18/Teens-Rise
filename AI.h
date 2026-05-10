#pragma once
#include "Physics.h"
enum NPCInfo
{
	npc_y = 0,		//Coord Y
	npc_x,			//Coord X
	npc_attitude,	//Attitude to the player
	npc_fraction,	//Fracion of character
	npc_HP,			//Current health
	npc_energy,		//Current energy
	npc_maxHP,		//Maximum health
	npc_stamina,	//Maximum stamina
	npc_weapon,		//Current weapon
	npc_item,		//Current item
	npc_move,		//Action
	npc_damage,		//
	npc_enemy,		//Enemy for character: NPC's id, 0 if player or -1 if there isn't anyone
	npc_follower,	//For spawning with player when location is changing: 0 or 1
};
enum status
{
	ai_off	= -1,
	neutral = 0,
	ally	= 1,
	angry	= 2,
	scared	= 3,
};
enum Fractions
{
	fraction_none = 1,
	fraction_geek,
	fraction_doomer,
	fraction_zoomer,
	fraction_gopnic,
	fraction_boomer,
	fraction_biker,
	fraction_offnic,
	fraction_introvert,
	fraction_police,
};
enum Characters
{
	player = 0,
	npc_citizen,
	npc_geek,
	npc_doomer,
	npc_zoomer,
	npc_gopnic,
	npc_boomer,
	npc_biker,
	npc_offnic,
	npc_introvert,
	npc_police,
};
enum lines
{
	name,
	compliment,
	taunt,
	yes,
	no,
	hello,
	goodbye,
	help,
	gettingrevived,
	anger
};
char line[32][16][64];
struct Crime
{
	char *name;
	float wantedlevel;
};
Crime stronglanguage    = {"", 0.5};//�����������
Crime weaponusing       = {"", 0.5};//������ � �����
Crime usingenergydrink  = {"", 1};	//����������
Crime truancy           = {"", 1};	//������
Crime curfew            = {"", 1};	//������������� ���
Crime violence          = {"", 1};	//�������
Crime resistance        = {"", 2};	//�������������
Crime theft             = {"", 2};	//�����
Crime vandalism         = {"", 2};	//���������
Crime trespassing       = {"", 2};	//��������� ����
Crime violenceauthority = {"", 3};	//������� - ������ �������
//Crime kill              = {"��������", 3};

//Actions
enum Moveset
{
	noaction = 0,
	lightstrike,
	block,
	grapple,
	dodge,
	uppercut,
	counterattack,
	knockdown,
	disarm,
};

void LoadNPC(int i, 
	int y_pos, int x_pos, int fraction, int alignment,
	int weapon, int item,
	int MaxHP, int Stamina){

	npc[i][npc_y] = y_pos;//X and Y coordinates
	npc[i][npc_x] = x_pos;

	npc[i][npc_fraction] = fraction;//Character info
	npc[i][npc_attitude] = alignment;

	npc[i][npc_weapon] = weapon;//Inventory
	npc[i][npc_item] = item;

	if(MaxHP == 'd'){//Max health
		switch(fraction)
		{
		case fraction_geek:
			npc[i][npc_maxHP] = 5;
			break;
		case fraction_doomer:
			npc[i][npc_maxHP] = 7;
			break;
		case fraction_gopnic:
			npc[i][npc_maxHP] = 10;
			break;
		}
	}
	else
		npc[i][npc_maxHP] = MaxHP;
	
	if(Stamina == 'd'){//Stamina
		switch(fraction)
		{
		case fraction_geek:
			npc[i][npc_stamina] = 5;
			break;
		case fraction_doomer:
			npc[i][npc_stamina] = 7;
			break;
		case fraction_gopnic:
			npc[i][npc_stamina] = 10;
			break;
		}
	}
	else
		npc[i][npc_stamina] = Stamina;

	//Current health and energy
	npc[i][npc_HP] = npc[i][npc_maxHP];
	npc[i][npc_energy] = npc[i][npc_stamina];
}
void SetupNPC(){
	if(location == safehouse1){
		LoadNPC(1,0,0,0,0,0,0,0,0);
		LoadNPC(2,0,0,0,0,0,0,0,0);
		LoadNPC(3,0,0,0,0,0,0,0,0);
	}
	else if(location == foreststreet){
		LoadNPC(1, 12,15, fraction_none, ai_off, 0,0, 5,5);
		LoadNPC(2, 12,17, fraction_zoomer, ai_off, 0,0, 5,5);
		LoadNPC(3, 12,16, fraction_gopnic, ai_off, 0,0, 5,5);
		LoadNPC(4, 12,45, fraction_none, neutral, 0,0, 5,5);
	}
	else if(location == cyclelane){
		LoadNPC(1,0,0,0,0,0,0,0,0);
		LoadNPC(2,0,0,0,0,0,0,0,0);
		LoadNPC(3,0,0,0,0,0,0,0,0);
	}
	else if(location == park_backentrance){
		LoadNPC(1,0,0,0,0,0,0,0,0);
		LoadNPC(2,0,0,0,0,0,0,0,0);
		LoadNPC(3,0,0,0,0,0,0,0,0);
	}
	else if(location == park_front){
		LoadNPC(1,0,0,0,0,0,0,0,0);
		LoadNPC(2,0,0,0,0,0,0,0,0);
		LoadNPC(3,0,0,0,0,0,0,0,0);
	}
}
void Move(int host, int move)
{
	if(host == player)
	{
		switch(move)
		{
		case lightstrike:
			currentmove = lightstrike;
		break;
		case block:
			currentmove = block;
		break;
		case grapple:
			currentmove = grapple;
		break;
		case dodge:
			if(skill[Dodge].ismastered && energy >= 0.5){
				if(GetAsyncKeyState('W'))
					y -= 2;
				if(GetAsyncKeyState('S'))
					y += 2;
				if(GetAsyncKeyState('A'))
					x -= 2;
				if(GetAsyncKeyState('D'))
					x += 2;
				energy -= 0.5;
			}
		break;
		case uppercut:
			if(skill[Uppercut].ismastered)
				currentmove = uppercut;
		break;
		case counterattack:
			currentmove = counterattack;
		break;
		case knockdown:
			currentmove = counterattack;
		break;
		case disarm:
			if(skill[Disarm].ismastered){
				currentmove = disarm;
				weapon[pickedup] = npc[0][npc_weapon];
				npc[0][weaponslot] = 0;
			}
		break;
		}
	}
	else {
		switch(move)
		{
		case lightstrike:
			npc[host][npc_move] = lightstrike;
			break;
		case block:
			npc[host][npc_move] = block;
			break;
		case grapple:
			npc[host][npc_move] = grapple;
			break;
		case dodge:
			npc[host][npc_x] += 2;
			npc[host][npc_stamina] -= 0.5;
			break;
		case uppercut:
			npc[host][npc_move] = uppercut;
			npc[host][npc_damage] *= 2;
			break;
		case counterattack:
			npc[host][npc_move] = counterattack;
			break;
		case knockdown:
			1;
			break;
		case disarm:
			npc[host][npc_move] = disarm;
			npc[host][npc_weapon] = weapon[weaponslot];
			weapon[weaponslot] = 0;
			break;
		}
	}
}
void Attack(int curweapon)
{
	for(int i = 0; i < sizeof(physicalbody)/sizeof(physicalbody[0]); i++){
		if(physicalbody[i][Texture] == 0){
			if(curweapon == iSlingshot){
				BodyPrep(i, 23, y+1, x+1, 0,0);
			}
			if(curweapon == iRubberGun){
				BodyPrep(i, 23, y, x, 
				(AimX-x == 0 ? (AimY-y > 0 ? 1 : -1) : (double)(AimY-y)/abs(AimX-x))*4, //(AimY-y < 0 ? -1 : (AimY-y == 0 ? 0 : 1))*4,
				(AimX-x < 0 ? -1 : (AimX-x == 0 ? 0 : 1))*4);
			//(AimY-y)/abs(AimY-y)*4,(AimX-x)/abs(AimX-x)*4);//AimY-y, AimX-x);
			}
			if(curweapon == iWaterGun && water > 0){
				BodyPrep(i, 63, y, x, 
				(AimX-x == 0 ? (AimY-y > 0 ? 1 : -1) : (AimY-y)/abs(AimX-x))*2,
				(AimX-x < 0 ? -1 : (AimX-x == 0 ? 0 : 1))*2);
				water--;
			//(AimY-y)/abs(AimY-y)*2, (AimX-x)/abs(AimX-x)*2);//AimY-y, AimX-x);
			}
			if(curweapon == iBottleGun){
				BodyPrep(i, 23, y, HandX, 0,10);
			}
			if(curweapon == iFireCracker){
				BodyPrep(i, 125, y-1, HandX, 0,3);//AimY-y, AimX-x);
			}
			if(curweapon == iPaintSpray){
				if(objectmodel[currentmap[y][HandX]][4] != 1)
					currentmap[y][HandX] = 84+rand()%15;
			}
			if(curweapon == iPepperSpray){

			}
			break;
		}
	}
}
void Roam(int i)
{
	int step = rand()%5;
	if(step == 1 
		&& objectmodel[loadedmap[npc[i][npc_y]-1][npc[i][npc_x]]][4] != 1 && npc[i][npc_y] > 1)
		npc[i][npc_y]--;
	if(step == 2 
		&& objectmodel[loadedmap[npc[i][npc_y]+1][npc[i][npc_x]]][4] != 1)
		npc[i][npc_y]++;
	if(step == 3 
		&& objectmodel[loadedmap[npc[i][npc_y]][npc[i][npc_x]-1]][4] != 1 && npc[i][npc_x] > 1)
		npc[i][npc_x]--;
	if(step == 4 
		&& objectmodel[loadedmap[npc[i][npc_y]][npc[i][npc_x]+1]][4] != 1)
		npc[i][npc_x]++;
}
void GoTo(int i, int spotY, int spotX)
{
	if(npc[i][npc_y] > spotY
		&& objectmodel[loadedmap[npc[i][npc_y]-1][npc[i][npc_x]]][4] != 1)
		npc[i][npc_y]--;
	if(npc[i][npc_y] < spotY 
		&& objectmodel[loadedmap[npc[i][npc_y]+1][npc[i][npc_x]]][4] != 1)
		npc[i][npc_y]++;
	if(npc[i][npc_x] > spotX 
		&& objectmodel[loadedmap[npc[i][npc_y]][npc[i][npc_x]-1]][4] != 1)
		npc[i][npc_x]--;
	if(npc[i][npc_x] < spotX 
		&& objectmodel[loadedmap[npc[i][npc_y]][npc[i][npc_x]+1]][4] != 1)
		npc[i][npc_x]++;
}
void Follow(int i, int speed, int spotY, int spotX)
{
	if(npc[i][npc_y] > spotY
		&& objectmodel[loadedmap[npc[i][npc_y]-1][npc[i][npc_x]]][4] != 1)
		npc[i][npc_y]--;
	if(npc[i][npc_y] < spotY 
		&& objectmodel[loadedmap[npc[i][npc_y]+1][npc[i][npc_x]]][4] != 1)
		npc[i][npc_y]++;
	if(npc[i][npc_x] > spotX 
		&& objectmodel[loadedmap[npc[i][npc_y]][npc[i][npc_x]-1]][4] != 1)
		npc[i][npc_x]--;
	if(npc[i][npc_x] < spotX 
		&& objectmodel[loadedmap[npc[i][npc_y]][npc[i][npc_x]+1]][4] != 1)
		npc[i][npc_x]++;
}
void GoAway(int i, int speed, int spotY, int spotX)
{
	if(npc[i][npc_y] > spotY 
		&& objectmodel[loadedmap[npc[i][npc_y]+1][npc[i][npc_x]]][4] != 1)
		npc[i][npc_y]++;
	if(npc[i][npc_y] < spotY
		&& objectmodel[loadedmap[npc[i][npc_y]-1][npc[i][npc_x]]][4] != 1)
		npc[i][npc_y]--;
	if(npc[i][npc_x] > spotX
		&& objectmodel[loadedmap[npc[i][npc_y]][npc[i][npc_x]+1]][4] != 1)
		npc[i][npc_x]++;
	if(npc[i][npc_x] < spotX
		&& objectmodel[loadedmap[npc[i][npc_y]][npc[i][npc_x]-1]][4] != 1)
		npc[i][npc_x]--;
}
//AI
void AIDoomer(int i)
{
	if(doomerrespect < 0.5)
	{
		if(npc[i][npc_attitude] == neutral)
			Roam(i);
		if(npc[i][npc_attitude] == angry)
		{
			if(doomerheat == 1)
				Follow(i,2,y,x);
			else if(doomerheat == 2)
				Follow(i,2,y,x);
			else if(doomerheat == 3)
				Follow(i,2,y,x);
		}
	}
	else 1;
}
void AIZoomer(int i)
{
	if(npc[i][npc_HP] < 1)
		npc[i][npc_attitude] = scared;
	if(zoomerrespect < 0.5){
		if(npc[i][npc_attitude] == scared)
			GoAway(i,2,1,1);
	}
	else
		Roam(i);
}
void AIGeek(int i)
{
	if(npc[i][npc_HP] < 1)
		npc[i][npc_attitude] = scared;
	if(geekrespect < 0.5)
	{
		if(npc[i][npc_attitude] == neutral)
			Roam(i);
		if(npc[i][npc_attitude] == angry)
			Follow(i,2,1,1);
		if(npc[i][npc_attitude] == scared)
			GoAway(i,1,1,1);
	}
	else	
		Roam(i);
}
void AIGopnic(int i)
{
	if(gopnicrespect < 0.5)
	{
		if(npc[i][npc_attitude] == neutral)
		{
			if(npc[i][npc_item] != iSeeds)
				Follow(i,1,y,x);
			else
				1;
		}
		if(npc[i][npc_attitude] == angry)
		{
			Follow(i,2,y,x);
			if(abs(npc[i][npc_y] - y) > 5){
				if(npc[i][npc_weapon] == iFireCracker)
					Attack(iFireCracker);
			}
			if(abs(npc[i][npc_y] - y) <= 1)
			{
				if(abs(npc[i][npc_x] - x) <= 1)
					HP--;
				//if(currentmove == block)
				//	Move(i, grapple);
				//else
				//	Move(i, uppercut);
			}
		}
	}
	else
	{
		if(npc[i][npc_attitude] == ally)
			Follow(i,1,y,x);
		else
			Roam(i);
	}
}
void AIBoomer(int i)
{
	if(boomerrespect < 0.5){
		if(npc[i][npc_attitude] == angry)
			Follow(i,2,1,1);
	}
	else{
		if(npc[i][npc_attitude] == neutral)
			Roam(i);
		else if(npc[i][npc_attitude] == ally)
			Follow(i,2,1,1);
	}
}
void AIPolice(int i)
{
	if(hr >= 22 || hr <= 4)
		wantedlevel += curfew.wantedlevel;
	if(weapon[weaponslot] != 0)
		wantedlevel += weaponusing.wantedlevel;
	//if(hr >= 8 && hr <= 14)
		//wantedlevel += truancy.wantedlevel;
	if(wantedlevel > 0 && wantedlevel < 1)
		Follow(i,1,y,x);
	if(wantedlevel >= 1)
	{
		Follow(i,2,y,x);
		if(npc[i][npc_y] == y && npc[i][npc_x] == x) 1;
			//knocked = true, gameover = true, 
			//failreason = "��������";
	}
	else
		Roam(i);
}
void AICitizen(int i)
{
	if(npc[i][npc_attitude] == neutral){
		Roam(i);
	}
	else if(npc[i][npc_attitude] == angry){
		Follow(i,1,y,x);
	}
	else if(npc[i][npc_attitude] == scared){
		GoAway(i,2,y,x);
	}
}
void AI()
{
	for(int i = 0; i < 32; i++)
	{
		if(npc[i][npc_y] == 0 || npc[i][npc_x] == 0)
			continue;
		if(npc[i][npc_HP] > 0 && npc[i][npc_attitude] != ai_off)
		{
		//Interaction with player in mid-fight
		
		//Character damage and move
			if(npc[i][npc_weapon] == 0)
				npc[i][npc_damage] = weaponID[iNone].damage;
			if(npc[i][npc_move] != 0)
				npc[i][npc_move] = 0;
		//AI
			if(npc[i][npc_fraction] == fraction_doomer)
				AIDoomer(i);
			else if(npc[i][npc_fraction] == fraction_zoomer)
				AIZoomer(i);
			else if(npc[i][npc_fraction] == fraction_geek)
				AIGeek(i);
			else if(npc[i][npc_fraction] == fraction_gopnic)
				AIGopnic(i);
			else
				AICitizen(i);
		}
	}
}
void UpdateNPC(int map[256][256])
{
	for(int i = 0; i < 32; i++)
	{
		op++;
		if(npc[i][npc_y] == 0 || npc[i][npc_x] == 0)
			continue;
		if(npc[i][npc_HP] > 0)
		{
			if(npc[i][npc_fraction] == fraction_geek)
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[102][0];
			else if(npc[i][npc_fraction] == fraction_doomer)
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[103][0];
			else if(npc[i][npc_fraction] == fraction_zoomer)
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[104][0];
			else if(npc[i][npc_fraction] == fraction_gopnic)
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[105][0];
			else if(npc[i][npc_fraction] == fraction_biker)
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[106][0];
			else if(npc[i][npc_fraction] == fraction_police)
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[107][0];
			else
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[104][0];
		}
		else
		{
			if(npc[i][npc_fraction] == fraction_geek)
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[109][0];
			else if(npc[i][npc_fraction] == fraction_doomer)
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[110][0];
			else if(npc[i][npc_fraction] == fraction_zoomer)
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[111][0];
			else if(npc[i][npc_fraction] == fraction_gopnic)
				map[npc[i][npc_y]][npc[i][npc_x]] = objectmodel[112][0];
		}
		//map[npc[i][npc_y]][npc[i][npc_x]+1] = objectmodel[npc[i][npc_weapon]][1];
	}
}
void Update(int map[256][256])
{
	UpdatePlayer(map);
	UpdateNPC(map);
	UpdateObjects();
}