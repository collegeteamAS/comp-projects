/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	
*/
#include <string>
#include "menutext.h"

// Error texts
const string MenuText::ERROR_FAILED_INITIALIZE = "Not everything was initialized";
const string MenuText::ERROR_FILE_CANNOT_READ = "Cannot read input file: "+FILE_NAME_LAYOUT;
const string MenuText::ERROR_FILE_NAME = "BAd file!";
const string MenuText::ERROR_INVALID_INPUT = "Invalid input";
const string MenuText::ERROR_INVALID_MOVE = "You can't move there, that's the edge!";
//const string MenuText::ERROR_NO_INVENTORY_SPACE = "You don't have any more room in your inventory!";
//const string MenuText::ERROR_NO_ITEMS = "You don't have any items to drop!";
//const string MenuText::ERROR_NO_ROOM = "There's no more space in this room!";
//const string MenuText::ERROR_NO_ROOM_ITEMS = "There's no items in this room!";

// Game messages
const string MenuText::GAME_DOOR_FOUND = "You found the door!";
const string MenuText::GAME_KEY_FOUND = "You found a key!";
//const string MenuText::GAME_QUIT = "Quitting game.";
//const string MenuText::GAME_WINNER = "You won!";

// File stuff
const string MenuText::FILE_NAME_IMAGE_DOOR = "images//door.bmp";
const string MenuText::FILE_NAME_IMAGE_KEY = "images//key.bmp";
const string MenuText::FILE_NAME_IMAGE_PLAYER = "images//player.bmp";
const string MenuText::FILE_NAME_LAYOUT = "maze.txt";

// invalids
//const string MenuText::INVALID_MENU_CHOICE = "Invalid choice, try again.";

// map strings
//const string MenuText::MAP_EDGE_BOTTOM = "____________________________________"; // 35 chars long
//const string MenuText::MAP_EXPLORE = "Explore the world!";
//const string MenuText::MAP_FIND_KEYS = "Drop 3 keys into the exit to win!";

// menus
const string MenuText::MENU_ASK_DIRECTION = "What direction do you want to move (u,d,l,r)? ";
const string MenuText::MENU_HELP = 
	"Explore the map to find keys and a door.\n"
	"WASD - move.\n"
	//"E - pick up item.\n"
	//"Q - drop item.\n"
	//"I - display inventory.\n"
	//"H - show this screen.\n\n"
	//"Legend:\n"
	//"'O' is your position on the map.\n"
	//"'k' is a key.\n"
	//"'E' is the exit room. Drop the keys off in this room to win.\n";
	;
const string MenuText::MENU_HELP_SHORT = "Use WASD to move";
//const string MenuText::MENU_ITEM_DISPLAY_INVENTORY = "Your inventory: ";
//const string MenuText::MENU_ITEM_SELECT = PLAYER_INVENTORY_SLOTS + "\n"+
//	"Select which item to drop (1/2/3) or 4 to abort: ";

// player inventory
//const string MenuText::PLAYER_INVENTORY_EMPTY = ":_   _:_   _:_   _:";
//const string MenuText::PLAYER_INVENTORY_KEY_1 = ":_ K _:_   _:_   _:";
//const string MenuText::PLAYER_INVENTORY_KEY_2 = ":_ K _:_ K _:_   _:";
//const string MenuText::PLAYER_INVENTORY_KEY_3 = ":_ K _:_ K _:_ K _:";
//const string MenuText::PLAYER_INVENTORY_SLOTS = "   1     2     3   ";
