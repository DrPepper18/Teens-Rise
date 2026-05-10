#pragma once
#include <string>
#include "Physics.h"
#define Back 8
#define Tab 9
#define Enter 13
#define Esc 27

using namespace std;

//INTERFACE
char menupattern[64][64] = {
" ----------------------------------- \0",
"|                 =                 |\0",
"|                 =                 |\0",
"|                 =                 |\0",
"|                 =                 |\0",
"|                 =                 |\0",
"|                 =                 |\0",
"|                 =                 |\0",
"|                 =                 |\0",
"|                 =                 |\0",
"|                 =                 |\0",
"|                 =                 |\0",
"|                 =                 |\0",
" ----------------------------------- \0"
};
char selecthint[128];
char backhint[128];
char navigatehint[128];

char SavingLabel[128];
char SavingDoneLabel[128];
char SavingFailedLabel[128];
char LoadingLabel[128];

char HoldLabel[128];
char RapidlyPressLabel[128];

//Save Data
//Slot 0 is for autosave, other are for manual saves
enum filedata
{
	row_savename = 1,	//Save title
	row_savedate,		//HH:MM then DD:MM:YYYY
	//Current walkthrough
	row_lastmission = 7,//number of last mission
	row_ingametime,		//hour, minute
	row_position,		//location, x, y
	row_physstats,		//health and stamina gauges
	row_money,			//money
	row_weapons,		//close, ranged-1, ranged-2, thrown
	row_inventory,		//9 items, 0st is key item
	row_skills,			//skills
	row_ammo,			//ammo for 5 weapons, -1 will mean infinite
	//Stats
	row_walkthroughnumber = 18,
	row_timeplaying,	//HH:MM:SS
	row_continues,		//knocks, arrests, fails
	row_moving,			//walking, running
	row_damage,			//Taken damage
};
//Progress
int mission = 0, m_cleared = 0;
int completes = 0;
//File Manage
char gamepath[128] = "C:\\Program Files\\Teen's rise\\";
char *language = "english";
//Time
bool day = false;
int hr, mn, sc;
enum seasons
{
	winter,
	spring,
	summer,
	autumn,
};
int season;

//Logic
bool paused = false;
bool phone = false;

struct Weapon
{
	int type;
	char name[128];
	int damage;
	int distance;
	int reloadspeed;
	int capacity[2];
	int price;
};
Weapon weaponID[32]	= {
//Brass
	{0,"", 1, 1, 1, {0,0}, 0},
//Melee
	{1,"", 2, 1, 0, {0,0}, 1},//, '\'', '\''},
	{1,"", 2, 2, 0, {0,0}, 0},
	{1,"", 3, 2, 2, {0,0}, 5},
	{1,"", 3, 1, 0, {0,0}, 2},
//Medium-ranged 1 (Slot 2)
	{2,"", 1, 8, 5, {1,16}, 2},
	{2,"", 0.5, 10, 3, {15,60}, 6},
//Medium-ranged 2
	{2,"", 0.1, 8, 0, {0,500}, 5},
	{2,"", 4, 16, 2, {1,8}, 5},
	//{2,"", 8, 30, 3, {15,30}, 200},
//Thrown (Slot 3)
	{3,"", 10, 12, 2, {1,10}, 10},
	{3,"", 0, 12, 2, {1,8}, 10},
	{3,"", 1, 15, 4, {1,4}, 2},
	{3,"", 4, 15, 4, {1,4}, 1},
//Extra (Slot 4)
	{4,"", 4, 2, 0, {1,300}, 3},
	{4,"", 2, 1, 0, {1,300}, 3},
//Environment (Slot 5)
	{5,"", 0.4, 5},
	{5,"", 2, 15},
	{5,"", 3, 15},
	{5,"", 0.7, 3},
	{5,"", 1.2, 2},};
enum Weapontype
{
	melee = 0,
	close = 1,
	ranged1 = 2,
	ranged2 = 3,
	thrown = 4,
	extra = 5,
	pickedup = 6,
};
enum ItemType
{
	type_None,
	type_Food,
	type_Drink,
	type_Weapon,
	type_Equipment,
};
char ItemTypeNames[8][32] = {
	//"Other",
	//"Food",
	//"Drink",
	//"Weapon",
	//"Equipment",
	//"Payment",
};
struct Item
{
	int type;
	char name[128];
	char description[128];
};
enum Items
{
	iNone = 0,
	//Close combat
	iPencil,
	iStick,
	iBat,
	iBottle,
	//Ranged combat
	iSlingshot,
	iRubberGun,
	iWaterGun,
	iBottleGun,
	//Thrown
	iFireCracker,
	iSmokeBomb,
	iDirtyBottle,
	iSodaBomb,
	//Extra
	iPaintSpray,
	iPepperSpray,
	//Food and drinks
	iInstantNoodles,
	iBurger,
	iSoda,
	iEnergyDrink,
	iShaurma,
	iLemonTea,
	//Gifts
	iCandies,
	iChocolate,
	iFlowers,
	iSeeds,
};
Item item[32] = {
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
};

int objectmodel[160][5] = {
	//0 - number\
	//1 - text symbol\
	//2 - background color\
	//3 - secondary color\
	//4 - obstacle or not\
//Landscape Texture
{0, ' ', 0, 0},			//Hole
{1, ',', 2, 10},		//Grass                                 
{2, '.', 14, 14},		//Sand
{3, '*', 15, 9},		//Snow
{4, '~', 9, 11},		//Water
{5, '#', 7, 7},			//Road
{6, '/', 6, 6},			//Floor
{7, 'x', 6, 2},			//Carpet
//Default
//Enviroment
{8, 'w', 2, 10},		//Bush
{9, 'Y', 6, 4},			//Tree
{10, '/', 3, 6},		//Branch
//Urban
{11, 'U', 15, 1},		//Bed
{12, '#', 8, 0, 1},		//Stone wall
{13, '#', 4, 0, 1},		//Brick wall
{14, 'I', 7, 8, 1},		//Fence
//Interact
{15, '#', 11, 11, 1},	//Glass
{16, '#', 7, 11, 1},	//Broken glass
{17, '{', 3, 15, 1},	//Dumpster
{18, 'x', 8, 0, 1},		//Item box
{19, '=', 7, 8, 1},		//Door locked hor
{20, ';', 7, 8, 1},		//Door locked ver
{21, '-', 7, 8},		//Door hor
{22, '|', 7, 8},		//Door ver
{23, '~', 16, 13},		//Rubber
{24, '$', 16, 10},		//Money
//Characters
{25, 'A', 0, 15},		//A
{26, 'B', 0, 15},		//B
{27, 'C', 0, 15},		//C
{28, 'D', 0, 15},		//D
{29, 'E', 0, 15},		//E
{30, 'F', 0, 15},		//F
{31, 'G', 0, 15},		//G
{32, 'H', 0, 15},		//H
{33, 'I', 0, 15},		//I
{34, 'J', 0, 15},		//J
{35, 'K', 0, 15},		//K
{36, 'L', 0, 15},		//L
{37, 'M', 0, 15},		//M
{38, 'N', 0, 15},		//N
{39, 'O', 0, 15},		//O
{40, 'P', 0, 15},		//P
{41, 'Q', 0, 15},   
{42, 'R', 0, 15},
{43, 'S', 0, 15},
{44, 'T', 0, 15},
{45, 'U', 0, 15},
{46, 'V', 0, 15},
{47, 'X', 0, 15},  
{48, 'Y', 0, 15},
{49, 'Z', 0, 15},
{50, '0', 0, 15},
{51, '1', 0, 15},
{52, '2', 0, 15}, 
{53, '3', 0, 15},
{54, '4', 0, 15}, 
{55, '5', 0, 15},
{56, '6', 0, 15},
{57, '7', 0, 15},
{58, '8', 0, 15},
{59, '9', 0, 15}, 
{60, '+', 0, 15},
{61, '-', 0, 15},
//Post-Effects
{62, '~', 16, 8},		//Smoke
{63, '*', 16, 9},		//Water
{64, '*', 16, 4},		//Soda
{65, '*', 16, 12},		//Pepper cloud,
{66, '\'', 16, 14},		//Leaf
{67, '.', 16, 15},		//Snowflake
//Default blocks
{68, ' ', 0, 0, 1},	//Black
{69, ' ', 1, 0, 1},
{70, ' ', 2, 0, 1},
{71, ' ', 3, 0, 1},
{72, ' ', 4, 0, 1},
{73, ' ', 5, 0, 1},
{74, ' ', 6, 0, 1},
{75, ' ', 7, 0, 1},
{76, ' ', 8, 0, 1},
{77, ' ', 9, 0, 1},
{78, ' ', 10,0, 1},
{79, ' ', 11,0, 1},
{80, ' ', 12,0, 1},
{81, ' ', 13,0, 1},
{82, ' ', 14,0, 1},
{83, ' ', 15,0, 1},
{84, ' ', 0, 0, 0},	//Black
{85, ' ', 1, 0, 0},
{86, ' ', 2, 0, 0},
{87, ' ', 3, 0, 0},
{88, ' ', 4, 0, 0},
{89, ' ', 5, 0, 0},
{90, ' ', 6, 0, 0},
{91, ' ', 7, 0, 0},
{92, ' ', 8, 0, 0},
{93, ' ', 9, 0, 0},
{94, ' ', 10,0, 0},
{95, ' ', 11,0, 0},
{96, ' ', 12,0, 0},
{97, ' ', 13,0, 0},
{98, ' ', 14,0, 0},
{99, ' ', 15,0, 0},
{100, 'x', 0,12, 1},//Map limit
//Characters
{101, 2, 16, 15},	//Player
{102, '0', 16, 10},	//Geek
{103, '0', 16, 0},	//Doomer
{104, '0', 16, 5},	//Zoomer
{105, '0', 16, 6, 1},//Gopnic
{106, '0', 16, 9},	//Biker
{107, '0', 16, 1, 1},//Cop
{108, '_', 16, 15},	//Laying player
{109, '_', 16, 10},	//Laying geek
{110, '_', 16, 0},	//Laying doomer
{111, '_', 16, 5},	//Laying zoomer
{112, '_', 16, 6},	//Laying gopnic
{113, '_', 16, 9},	//Laying cop
//Weapons
{114, '-', 16, 15},	//Fist left
{115, '\\', 16, 4},	//Stick
{116, '!', 16, 6},	//Bat
{117, 'q', 16, 3},	//Bottle
{118, 'y', 16, 4},	//Slingshot
{119, '-', 16, 4},	//Rubber gun
{120, '-', 16, 14},	//Water gun
{121, '=', 16, 3},	//Bottle gun
{122, },//Pistol gun
{123, 'i', 16, 12},	//Cola bomb
{124, '*', 16, 3},	//Dirty bottle
{125, 'i', 16, 12},	//Fire Cracker
{126, 3, 16, 5},	//Paint spray
{127, 3, 16, 0},	//Pepper spray
//Inventory
{128, '#', 16, 14},	//Instant noodles
{129, '=', 16, 6},	//Burger
{130, 'i', 16, 2},	//Soda
{131, 'n', 16, 12},	//Energy drink
{132, 'U', 16, 15},	//Shaurma
{133, '@', 16, 13},	//Candies
{134, '#', 16, 4},	//Chocolate
{135, 'Y', 16, 10},	//Flowers
{136, '\'', 12, 0},	//Seeds
{137, '@', 16, 1},	//Bag
//Weapons right texture
{138, '-', 16, 15},	//Fist right
{139, '/', 16, 4},	//Stick right
{140, '!', 16, 6},
{141, 'p', 16, 3},
{142, 'y', 16, 4},
{143, '-', 16, 4},
{144, '-', 16, 14},
{145, '=', 16, 3},
{146, },
{147, 'i', 16, 12},
{148, '*', 16, 3},
{149, 'i', 16, 12},
{150, 3, 16, 5},
{151, 3, 16, 0},
};

enum weathertype {
	clear,
	rain,
	snow,
	leaffall,
};
int weather;
int weatherforecast[24];
//Environment info
int actionobject[32][4];
int particles[32][4], p_onscreen;
//NPC Info
int npc[32][16] = {};
int npc_traffic = 0;//How many NPC's will you see on your screen

/********Player Info*********/
int x,y, location;
bool indoor = false;
//Stats
int totalplaytime = 0;
int knockedout = 0;
int arrested = 0;
int failed = 0;
int takendamage = 0;
int knocks = 0;
//
char *crime;
bool crawling = false;
bool knocked = false;
bool tired = false;
bool recognized = false;
bool kissed = false;
bool gotdamage = false;
bool sickness = false;
bool cold = false;
bool interaction = false;
int currentmove = 0;
float wantedlevel = 0,
	geekheat = 0, doomerheat = 0, zoomerheat = 0,
	gopnicheat = 0, boomerheat = 0;
float geekrespect = 0.5, doomerrespect = 0.5, zoomerrespect = 0.25,
	gopnicrespect = 0.25, boomerrespect = 0.5;
float FullHP = 5.00;
int speed = 2;
float stamina = 5.00;
int respect = 50;

enum skills
{
	none = 0,
	ApologizeTeens,
	ApologizeAdults,
	ApologizePolice,
	StaminaAnalysis,
	HealthAnalysis,
	ItemAnalysis,
	Reviving,
	StaminaLvl1,
	StaminaLvl2,
	Dodge,
	Uppercut,
	CounterAttack,
	Overthrow,
	Disarm,
};
struct Skill
{
	bool ismastered;
	char *name;
	char *description;
	char *input;
};
Skill skill[32] = {
	{false,},
	{false,},
	{false,},
	{false,},
	{false,},
	{false,},
	{true,},
	{false,},
	{false,},
	{false,},
	{false,},
	{false,},
	{false,},
	{false,},
};

float HP = FullHP;
float energy = stamina;
//Weapon Info
int ColorWeapon;
int DistanceWeapon = 0;
int DamageWeapon = 0;
bool leftside = true;
int SkinWeapon;
int HandX, HandY;
int AimY = 0, AimX = 0, LockOn = 0;

//Player's Inventory and Weapons
int weapon[7] = {0,	//0 is for Melee
	iBat,			//Close
	iRubberGun,		//Ranged-1
	iWaterGun,		//Ranged-2
	iFireCracker,	//Thrown
	iPaintSpray,	//Extra
}, weaponslot = 0;
int inventory[11] = {0,//Cell "0" is only for key items
	iNone, 
	iBurger,iSoda,iSmokeBomb,
	iNone,iNone,iNone,
	iNone,iNone,iNone};
int itembox[128] = {iPepperSpray};
int quickaccessitem = 0;
float money = 0.00;
//Ammos
int currentreloading[4][1];
int water = 20;
/**************************/
//Cheats
char cheatcode[32][16] = {
"healme",		//Full HP
"overhealme",	//Overheal
"knockout",		//Suicide
"money200",		//+200$
"geekset",		//geek weapon set
"doomerset",	//doomer weapon set
"zoomerset",	//zoomer weapon set
"gopnicset",	//doomer weapon set
"wanted3",		//Max wanted level
"1hr",			//1 hour later
"hotcoffee",	//Waking up
"boxskills",
"karateskills",
"streetskills",
"carmaoff",		//carma doesn't work
"aioff",		//AI turns off
};
bool carmaoff = false;
bool aidisabled = false;

int foodcatalog[16] = {0,
	iSoda, iInstantNoodles, iCandies, iChocolate};
//Map
char LocationName[32][64];
enum locations
{
	unknown = 0,
	//--------Indoor locations--------
	safehouse1,
	safehouse2,
	school_base,
	school_canteen,
	school_gym,
	store,
	mall1f,
	mall2f,
	mall3f,
	mallcarparking,
	discoclub1f,
	discoclubb1,
	martialartsgym,
	police_station,
	hospital,
	//-------Outdoor locations-------
	foreststreet,
	cyclelane,
	park_backentrance,
	park_front,
	park_alley,
	fleamarket,
	parkstreet,
	mountainstreet_nearthehighway,
	mountainstreet_playgrounds,
	mountainstreet_waytothemountain,
	mountainbase,
	mountaintop,
};
int loadedmap[256][256];
int currentmap[256][256];
int MapSizeY = 256, MapSizeX = 256;
char* subtitle;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HWND hwnd = GetConsoleWindow();
POINT p;
int MouseX, MouseY;
int SensivityY = 65, SensivityX = 42;
int op = 0;
int framemodulus = 0;

void Color(int a, int b)
{
	SetConsoleTextAttribute(hConsole, (WORD) ((a << 4)| b));
}
char *Localize(char *text, int row, char *filename)
{
	ifstream file;
	char filepath[128] = "C:\\Program Files\\Teen's rise\\game\\translate\\";
	strcat(filepath, language);
	strcat(filepath, filename);
	file.open(filepath);
	for(int i = 0; i < row; i++)
		file.getline(text, 1000, '\n');
	file.close();
	return text;
}
char numbertotext(int j, int count){
	int number = j/1000;
	return number;
}
char *KeyName(int vKey)
{
	if(vKey == 'A')				return "[A]";
	else if(vKey == 'B')		return "[B]";
	else if(vKey == 'C')		return "[C]";
	else if(vKey == 'D')		return "[D]";
	else if(vKey == 'E')		return "[E]";
	else if(vKey == 'F')		return "[F]";
	else if(vKey == 'G')		return "[G]";
	else if(vKey == 'H')		return "[H]";
	else if(vKey == 'I')		return "[I]";
	else if(vKey == 'J')		return "[J]";
	else if(vKey == 'K')		return "[K]";
	else if(vKey == 'L')		return "[L]";
	else if(vKey == 'M')		return "[M]";
	else if(vKey == 'N')		return "[N]";
	else if(vKey == 'O')		return "[O]";
	else if(vKey == 'P')		return "[P]";
	else if(vKey == 'Q')		return "[Q]";
	else if(vKey == 'R')		return "[R]";
	else if(vKey == 'S')		return "[S]";
	else if(vKey == 'T')		return "[T]";
	else if(vKey == 'U')		return "[U]";
	else if(vKey == 'V')		return "[V]";
	else if(vKey == 'W')		return "[W]";
	else if(vKey == 'X')		return "[X]";
	else if(vKey == 'Y')		return "[Y]";
	else if(vKey == 'Z')		return "[Z]";
	else if(vKey == '0')		return "[0]";
	else if(vKey == '1')		return "[1]";
	else if(vKey == '2')		return "[2]";
	else if(vKey == '3')		return "[3]";
	else if(vKey == '4')		return "[4]";
	else if(vKey == '5')		return "[5]";
	else if(vKey == '6')		return "[6]";
	else if(vKey == '7')		return "[7]";
	else if(vKey == '8')		return "[8]";
	else if(vKey == '9')		return "[9]";
	else if(vKey == VK_UP)		return "[^]";
	else if(vKey == VK_DOWN)	return "[v]";
	else if(vKey == VK_LEFT)	return "[<]";
	else if(vKey == VK_RIGHT)	return "[>]";
	else if(vKey == VK_LSHIFT)	return "[LShift]";
	else if(vKey == VK_LCONTROL)return "[LCtrl]";
	else if(vKey == VK_LBUTTON)	return "[LMB]";
	else if(vKey == VK_MBUTTON) return "[WhlBtn]";
	else if(vKey == VK_RBUTTON)	return "[RMB]";
	else if(vKey == VK_LMENU)	return "[LAlt]";
	else if(vKey == VK_SPACE)	return "[Space]";
	else if(vKey == Enter)		return "[Enter]";
	else if(vKey == Tab)		return "[Tab]";
	else if(vKey == Back)		return "[BSpace]";
	else if(vKey == Esc)		return "[Esc]";
	else if(vKey == VK_F1)		return "[F1]";
	else if(vKey == VK_F2)		return "[F2]";
	else if(vKey == VK_F3)		return "[F3]";
	else if(vKey == VK_F4)		return "[F4]";
	else if(vKey == VK_F5)		return "[F5]";
	else if(vKey == VK_F6)		return "[F6]";
	else if(vKey == VK_F7)		return "[F7]";
	else if(vKey == VK_F8)		return "[F8]";
	else if(vKey == VK_F9)		return "[F9]";
	else if(vKey == VK_F10)		return "[F10]";
	else if(vKey == VK_F11)		return "[F11]";
	else if(vKey == VK_F12)		return "[F12]";
	else						return "[?]";
}
void LoadData(int slot)
{
	char ErrorText[128];
	Localize(ErrorText, 25, "\\menu.txt");
	char buffer[100];
	int pos = 1;
	ifstream file;
	if(slot == 0)	file.open("C:\\Program Files\\Teen's rise\\game\\saves\\autosave.txt");
	if(slot == 1)	file.open("C:\\Program Files\\Teen's rise\\game\\saves\\savedata1.txt");
	if(slot == 2)	file.open("C:\\Program Files\\Teen's rise\\game\\saves\\savedata2.txt");

	if(!file.is_open())
		cout << ErrorText << " ([Enter] - OK)";
	else
	{
		cout << LoadingLabel;
		for(int i = 0; i < 8; i++)
			file.getline(buffer, 40);
		file.getline(buffer, 4);
		m_cleared = atoi(buffer);
		file.getline(buffer, 3, ':');
		hr = atoi(buffer);
		file.getline(buffer, 3);
		mn = atoi(buffer);
		file.getline(buffer, 3, ' ');
		location = atoi(buffer);
		file.getline(buffer, 3, ';');
		x = atoi(buffer);
		file.getline(buffer, 3);
		y = atoi(buffer);
		file.getline(buffer, 3, ' ');
		FullHP = atoi(buffer);
		file.getline(buffer, 3);
		stamina = atoi(buffer);

		//New save block
		file.getline(buffer, 40);

		file.close();
		return;
	}
	_getch();
}
void SaveData(int slot)
{
	system("cls");
	char ErrorText[128];
	Localize(ErrorText, 25, "\\menu.txt");
	//Preparing save data
	time_t timer = time(NULL);
	struct tm* aTm = localtime(&timer);
	ofstream file;
	if(slot == 0)	file.open("C:\\Program Files\\Teen's rise\\game\\saves\\autosave.txt");
	if(slot == 1)	file.open("C:\\Program Files\\Teen's rise\\game\\saves\\savedata1.txt");
	if(slot == 2)	file.open("C:\\Program Files\\Teen's rise\\game\\saves\\savedata2.txt");

	if(!file.is_open())
		cout << ErrorText << " ([Enter] - OK)";
	else
	{
		cout << SavingLabel;
		file << "SAVE DATA" << endl;
		file << aTm->tm_hour<<":"<<aTm->tm_min<<" "<<
			aTm->tm_mday <<"."<<aTm->tm_mon+1<<"."<<aTm->tm_year+1900 << endl;
		for(int j = -2; j < 3; j++){
			for(int i = -3; i < 4; i++){
				if(loadedmap[y+j][x+i] < 10)
					file << "0";
				file << loadedmap[y+j][x+i] << " ";
			}
			file << endl;
		}
		file << "#" << endl;
		file << m_cleared << endl;
		file << hr<<":"<<mn << endl;
		file << location<<" "<<x<<";"<<y << endl;
		file << FullHP<<" "<<stamina << endl;
		file << "#" << endl;
		file << completes << endl;
		for(int i = 1; i < 6; i++)
			file << weapon[i] << " ";
		file << endl;

		cout << SavingDoneLabel;
		file.close();
	}
	Sleep(2000);
}
void QTE(bool success, int button[2], int type, int time)
{
	int simult = 0, round = 1;
	int level = 5;

	cout << button[0];
	if(button[1] != 0)
		cout << " + ";
	cout << button[1];

	if(GetAsyncKeyState(button[0]))
		level++;
	if(GetAsyncKeyState(button[1]))
		level++;
}

char *WeatherAt(int hour)
{
	if(weatherforecast[hour] == clear)
		return "Clear";
	if(weatherforecast[hour] == rain)
		return "Rain";
	if(weatherforecast[hour] == snow)
		return "Snow";
}
void Use(int item)
{
	int j, i;
	if(inventory[item] == iInstantNoodles){
		HP += min(2, FullHP - HP);
	}
	if(inventory[item] == iBurger){
		HP = FullHP;
	}
	else if(inventory[item] == iSoda){
		HP += min(4, FullHP - HP);
		energy = stamina;
	}
	else if(inventory[item] == iEnergyDrink){
		if((hr > 23 || hr < 05) && tired)
			tired = false;
		else
			HP += 6;
			energy = stamina + 100;
	}
	else if(inventory[item] == iLemonTea){
		cold = false;
		energy += 5;
	}
	inventory[item] = 0;
}
void LockingOn()
{
	int MinX = 20, MinY = 20, SY, SX; 
	int lockednpc = 0, npcid;
	for(npcid = 0; npcid < 32; npcid++)
	{
		SY = abs((y-npc[npcid][0])),
		SX = abs((x-npc[npcid][1]));
		if(SY + SX < MinY + MinX){
			MinY = SY, MinX = SX;
			lockednpc = npcid;
		}
	}
	LockOn = lockednpc;
}
void LoadObject(int i, int item, int y, int x)
{
	actionobject[i][0] = item,
	actionobject[i][1] = y,
	actionobject[i][2] = x;
}
void LoadMap()
{
	ifstream file;
	std::string path = "C://Program Files//Teen's rise//game//maps//";
	if(location == safehouse1)
		file.open(path+"Safehouse1.txt");
	else if(location == foreststreet)
		file.open(path+"ForestStreet.txt");
	else if(location == cyclelane)
		file.open(path+"CycleLane.txt");
	else if(location == park_backentrance)
		file.open(path+"ParkBack.txt");
	else if(location == park_front)
		file.open(path+"ParkFront.txt");
	else if(location == park_alley)
		file.open(path+"ParkAlley.txt");
	else if(location == fleamarket)
		file.open(path+"FleaMarket.txt");
	char buffer[5];
	if(file.is_open())
	{
		for(int j = 0; j < 256; j++)
		{
			if(file.eof()){
				MapSizeY = j;
				break;
			}
			for(int i = 0; i < 256; i++)
			{
				file.getline(buffer, 4, ',');
				if(buffer[0] == '\n'){
					file.seekg(-3,ios_base::cur);
					MapSizeX = i;
					break;
				}
				else
					currentmap[j][i] = atoi(buffer);
			}
		}
		
	}
	file.close();
}
void LocationSwitch()
{
	int prevlocation = location;
	bool change = false;
	if(location == safehouse1)
	{
		indoor = true;
		if(x >= 30){
			change = true;
			location = foreststreet;
			y = 30, x = 16;
		}
		//npc_traffic = 0;
	}
	else if(location == store)
	{
		/*if(y && x){
			location = foreststreet;
		}*/
	}
	else if(location == foreststreet)
	{
		indoor = false;
		if(y == 30 && x <= 15){
			change = true;
			location = safehouse1;
			y = 16, x = 29;
		}
		else if(x > 69){
			change = true;
			location = cyclelane;
			x = 16;
		}
		//npc_traffic = 3;
	}
	else if(location == cyclelane)
	{
		indoor = false;
		if(x < 16){
			change = true;
			location = foreststreet;
			x = 69;
		}
		else if(y > 44){
			change = true;
			location = park_backentrance;
			y = 7, x = 16;
		}
		//npc_traffic = 3;
	}
	else if(location == park_backentrance)
	{
		indoor = false;
		if(y < 7){
			change = true;
			location = cyclelane;
			y = 44, x = 68;
		}
		else if(y > 51){
			change = true;
			location = park_front;
			y = 7;
		}
		//npc_traffic = 5;
	}
	else if(location == park_front)
	{
		indoor = false;
		if(y < 8){
			change = true;
			location = park_backentrance;
			y = 51;
		}
		else if(y > 42){
			change = true;
			location = park_alley;
			y = 8;
		}
		//npc_traffic = 7;
	}
	else if(location == park_alley)
	{
		indoor = false;
		if(y < 8){
			change = true;
			location = park_front;
			y = 42;
		}
		else if(y > 40){
			change = true;
			location = fleamarket;
			y = 8, x = 20;
		}
		//npc_traffic = 5;
	}
	else if(location == fleamarket)
	{
		indoor = false;
		if(y < 8){
			change = true;
			location = park_alley;
			y = 40;
		}
		//npc_traffic = 12;
	}
	else if(location == mountainstreet_nearthehighway)
	{
		indoor = false;
		if(y == 0 && x == 0){
			change = true;
			location = mountainstreet_waytothemountain;
		}
	}
	else if(location == mountainstreet_waytothemountain)
	{
		indoor = false;
		if(y == 0 && x == 0){
			change = true;
			location = mountainbase;
		}
	}
	else if(location == mountainbase)
	{
		indoor = false;
		if(y == 0 && x == 0){
			change = true;
			location = mountainstreet_waytothemountain;
		}
	}
	else if(location == mountaintop)
	{
		indoor = false;
		if(y == 0 && x == 0){
			change = true;
			location = mountainbase;
		}
	}
	if(change)
		HandX = x+1;
}
void WeaponLoad()
{
	if(weapon[weaponslot] == iNone) {
		DamageWeapon = 0.5,
		DistanceWeapon = 1;
	}
	else {
		DamageWeapon = weaponID[weapon[weaponslot]].damage,
		DistanceWeapon = weaponID[weapon[weaponslot]].distance;
	}
}
void UpdateObjects()
{
	for(int i = 0; i < 32; i++) {
		if(actionobject[i][0] != 0)
			loadedmap[actionobject[i][1]][actionobject[i][2]] = 113+actionobject[i][0];
	}
}
void UpdatePlayer(int field[256][256])
{
	if(HP > 0)
	{
		if(crawling)
		{
			if(field[y-1][x-1] == 8 || field[y-1][x+1] == 8 || 
				field[y+1][x-1] == 8 || field[y+1][x+1] == 8)
				field[y][x] = 8;
			else
				field[y][x] = objectmodel[108][0];
		}
		else
			field[y][x] = objectmodel[101][0];
	}
	else
		field[y][x] = objectmodel[108][0];
	WeaponLoad();
	if(objectmodel[field[y][HandX]][4] == 0 && HandX >= 0 && HandX <= MapSizeX){
		if(weapon[weaponslot] != 0){
			if(HandX == x-1)
				SkinWeapon = objectmodel[113+weapon[weaponslot]][0];
			else if(HandX == x+1)
				SkinWeapon = objectmodel[113+weapon[weaponslot]+24][0];
			field[y][HandX] = SkinWeapon;
		}
	}
	//Lock-on
	if(LockOn != 0)
		AimY = npc[LockOn][0],
		AimX = npc[LockOn][1];
	else
		AimY = y,
		AimX = x+2;
}