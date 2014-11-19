/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	
*/
#include <string>
#include "menutext.h"

// Error texts
const string MenuText::ERROR_FILE_NAME = "BAd file!";
const string MenuText::ERROR_NO_INVENTORY_SPACE = "You don't have any more room in your inventory!";
const string MenuText::ERROR_NO_ITEMS = "You don't have any items to drop!";
const string MenuText::ERROR_NO_ROOM = "There's no more space in this room!";
const string MenuText::ERROR_NO_ROOM_ITEMS = "There's no items in this room!";

// Game messages
const string MenuText::GAME_QUIT = "Quitting game.";
const string MenuText::GAME_WINNER = "You won!";

// invalids
const string MenuText::INVALID_MENU_CHOICE = "Invalid choice, try again.";
const string MenuText::INVALID_MOVE = "You can't move there, that's the edge!";

// map strings
const string MenuText::MAP_EDGE_BOTTOM = "____________________________________"; // 35 chars long
const string MenuText::MAP_EXPLORE = "Explore the world!";
const string MenuText::MAP_FIND_KEYS = "Drop 3 keys into the exit to win!";

// menus
const string MenuText::MENU_HELP = 
	"Explore the map to find the keys and exit to get out.\n"
	"WASD - move.\n"
	"E - pick up item.\n"
	"Q - drop item.\n"
	"I - display inventory.\n"
	"H - show this screen.\n\n"
	"Legend:\n"
	"'O' is your position on the map.\n"
	"'k' is a key.\n"
	"'E' is the exit room. Drop the keys off in this room to win.\n";
const string MenuText::MENU_ITEM_DISPLAY_INVENTORY = "Your inventory: ";
const string MenuText::MENU_ITEM_SELECT = PLAYER_INVENTORY_SLOTS + "\n"+
	"Select which item to drop (1/2/3) or 4 to abort: ";

// player inventory
const string MenuText::PLAYER_INVENTORY_EMPTY = ":_   _:_   _:_   _:";
const string MenuText::PLAYER_INVENTORY_KEY_1 = ":_ K _:_   _:_   _:";
const string MenuText::PLAYER_INVENTORY_KEY_2 = ":_ K _:_ K _:_   _:";
const string MenuText::PLAYER_INVENTORY_KEY_3 = ":_ K _:_ K _:_ K _:";
const string MenuText::PLAYER_INVENTORY_SLOTS = "   1     2     3   ";
