/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Constant value initializer class
*/

#include <string>
#include "menutext.h"

/* 
	Error for menu choice 
	@author Andre Allan Ponce
*/
const string MenuText::INVALID_MENU_CHOICE = "\nInvalid choice.\n";

/* 
	Menu Text 
	@author Andre Allan Ponce
*/
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
const string MenuText::MENU_CHOICE = "Select option: ";

/* 
	Prompt text
	@author Andre Allan Ponce
*/
const string MenuText::PROMPT_FILE_NAME = "\nEnter a filename: ";
const string MenuText::PROMPT_PLAYER_NAME = "\nEnter a player's name: ";

/* 
	Error Messages
	@author Andre Allan Ponce
*/
const string MenuText::ERROR_FILE_NAME = "\nCannot read file\n";
const string MenuText::ERROR_FILE_CONTENTS = "\nFile corrupted\n";
const string MenuText::ERROR_UNKNOWN = "\nUnknown error occured\n";

/*
	Other menu text
	@author Andre Allan Ponce
*/
const string MenuText::SAVING = "\nSaving existing File\n";
const string MenuText::SAVING_SUCCESS = "\nFile saved successfully!\n";