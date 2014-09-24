/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Steve Suh
	h_suh@u.pacific.edu
	Constant value initializer class
*/

#include <string>
#include "room.h"
#include "player.h"
#include "menutext.h"
#include "game.h"

/*
	Player constants
	@author Andre Allan Ponce
*/
const int Player::INVENTORY_MAX = 40; // amount in inventory

/* 
	Error for menu choice 
	@author Andre Allan Ponce

const string MenuText::INVALID_MENU_CHOICE = "\nInvalid choice.\n";

/* 
	Menu Text 
	@author Andre Allan Ponce

const string MenuText::MENU_ONE = "\n"
						"1) New File\n"
						"2) Open File\n"
						"3) Quit\n";
const string MenuText::MENU_TWO = "\n"
						"1) Print all Players\n"
						"2) Create a new Player\n"
						"3) Randomly generate a new Player\n"
						"4) Modify a Player\n"
						"5) Save Player list\n"
						"6) Close File\n";

/* 
	Prompt text
	@author Andre Allan Ponce

const string MenuText::PROMPT_FILE_NAME = "\nEnter a filename: ";
const string MenuText::PROMPT_PLAYER_NAME = "\nEnter a player's name: ";

/* 
	Error Messages
	@author Andre Allan Ponce
*/

//item descriptions
//steve suh
const string MenuText::ERROR_FILE_NAME = "\nCannot read game data\n";
const string MenuText::ERROR_FILE_CONTENTS = "\nGame data corrupted\n";
const string MenuText::ERROR_UNKNOWN = "\nUnknown error occured\n";
const string ROOMITEM_JUNK = "it's some sort of a junk.";
const string ROOMITEM_VASE = "it's an empty vase.";
const string ROOMITEM_TABLE = "it's an old table.";
const string ROOMITEM_CHAIR = "it's a chair with squeaking legs. shouldn't sit down on this chair.";
const string ROOMITEM_LAMP = "it's a lamp. light seems to be dim and flickering.";
const string ROOMITEM_BED = "it's a bed. doesn't look very comfortable.";
const string ROOMITEM_CANDLE = "it's an antique candlestick. smells like burnt cheese.";
const string ROOMITEM_DISH = "it's a dish. seems to have some ketchup on it.";
const string ROOMITEM_DUST = "I thought it was something, but it was just a dust.";
const string ROOMITEM_FORK = "it's a crooked fork. smells like hardboiled icecream.";
const string ROOMITEM_TOILET = "it's a toilet. I don't want to open it";
const string ROOMITEM_BATHTUB = "it's a bathtub. I don't feel like taking bath now";
const string ROOMITEM_MIRROR = "it's me...no it's a mirror";
const string ROOMITEM_BLOOD = "unpleasant red spots on the groun. smells like iron.";
const string ROOMITEM_CD = "it's an old album from 90s rockband. smells like teen spirit.";

//*/