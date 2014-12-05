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

// File names
const string MenuText::FILENAME_PLAYERS = "players";
const string MenuText::FILENAME_TILES = "tiles";

// floor messages
const string MenuText::FLOOR_BASEMENT_PREFIX = "B";
const string MenuText::FLOOR_GROUND = "You are now on the ground floor.";
const string MenuText::FLOOR_NUMBER_PREFIX = "You are now on Floor ";
const string MenuText::FLOOR_NUMBER_SUFFIX = ".";

// Game messages
const string MenuText::GAME_QUIT = "Quitting game.";
const string MenuText::GAME_WINNER = "You won!";

// invalids
const string MenuText::INVALID_MENU_CHOICE = "Invalid choice, try again.";
const string MenuText::INVALID_MOVE_EDGE = "You can't move there, that's the edge!";
const string MenuText::INVALID_MOVE_FAKE_DOOR = "You can't move there, that's a fake door!";
const string MenuText::INVALID_MOVE_WALL = "You can't move there, there's a wall!";


// map strings
const string MenuText::MAP_EDGE_BOTTOM = "____________________________________"; // 35 chars long
const string MenuText::MAP_EXPLORE = "Explore the world!";
const string MenuText::MAP_FIND_KEYS = "Drop 3 keys into the exit to win!";

// menus
const string MenuText::MENU_CHOOSE_PLAYER_NAME = "Enter a name for the new player: ";
const string MenuText::MENU_CREATE_NEW_PLAYER = "0) Create a new player";
const string MenuText::MENU_HELP = 
	"Explore the map!\n"
	"Drop 3 keys into unlocked rooms and lock them to score points.\n"
	"WASD - move.\n"
	"E - examine Room\n"
	"I - show inventory\n"
	"Z - pick up item\n"
	"C - drop item\n"
	"H - show this screen.\n"
	"ESC - Quit game (Saves your progress).\n\n"
	"Legend:\n"
	"'O' is your position on the map.\n"
	"'k' is a key.\n"
	"'/' is a stair that leads up. Examine to take the stairs.\n"
	"'\\' is a stair that leads down. Examine to take the stairs.\n"
	"'U' is an unlocked room. Examine the room when 3 keys are in it\n"
	"to lock the room! There is only one unlocked room per floor.\n\n"
	"What's new:\n"
	"+ Added stairs: Now you can move up and down the floors when you\n"
	"examine stair rooms.\n"
	"+ Randomly generated rooms: Now rooms may have different door\n"
	"layouts, resulting in some sneaky, twisted pathways.\n"
	"+ Dropping keys into an unlocked room and examining the room can\n"
	"score you points.\n"
	"+ Your score and name is saved when the game exists, but the \n"
	"layout is not.\n";
const string MenuText::MENU_HELP_CURRENT_PLAYER = "Current player: ";
const string MenuText::MENU_ITEM_DISPLAY_INVENTORY = "Your inventory: ";
const string MenuText::MENU_ITEM_SELECT = PLAYER_INVENTORY_SLOTS + "\n"+
	"Select which item to drop (1/2/3) or 4 to abort: ";
const string MenuText::MENU_PLAYER_PICK = 
	"Loaded Players:\n"
	"#) name score";
const string MenuText::MENU_PLAYER_PICK_BAR = 
	"=====================";
const string MenuText::MENU_PLAYER_PICK_CHOICE_PREFIX = "Choose a player to load (0";
const string MenuText::MENU_PLAYER_PICK_CHOICE_MID = "-";
const string MenuText::MENU_PLAYER_PICK_CHOICE_SUFFIX = "): ";

// messages (unuseD)
const string MenuText::MESSAGE_LOADING_SAVE = "Loading player saving";
const string MenuText::MESSAGE_LOAD_SUCCESSFUL = "Load successful";

// player text
const string MenuText::PLAYER_INVENTORY_EMPTY = ":_   _:_   _:_   _:";
const string MenuText::PLAYER_INVENTORY_KEY_1 = ":_ K _:_   _:_   _:";
const string MenuText::PLAYER_INVENTORY_KEY_2 = ":_ K _:_ K _:_   _:";
const string MenuText::PLAYER_INVENTORY_KEY_3 = ":_ K _:_ K _:_ K _:";
const string MenuText::PLAYER_INVENTORY_PREFIX = "You have ";
const string MenuText::PLAYER_INVENTORY_SUFFIX = " keys.";
const string MenuText::PLAYER_INVENTORY_SLOTS = "   1     2     3   ";
const string MenuText::PLAYER_MESSAGE_BLANK = "";
const string MenuText::PLAYER_MESSAGE_INVALID_SLOT = "No slot for this message";
const string MenuText::PLAYER_SCORE_PREFIX = "You have ";
const string MenuText::PLAYER_SCORE_SUFFIX = " points.";

// tile text
const string MenuText::TILE_EXIT_ACTION = "You've found an unlocked room!";
const string MenuText::TILE_EXIT_EXAMINE_LOCK = "This room is already locked!";
const string MenuText::TILE_EXIT_LOCKING = "Locking this room!";
const string MenuText::TILE_EXIT_NOT_ENOUGH_KEYS = "You don't have enough keys to lock this room!";
const string MenuText::TILE_EXIT_SCORE_PREFIX = "You gained ";
const string MenuText::TILE_EXIT_SCORE_SUFFIX = " points!";
const string MenuText::TILE_KEY_ACTION = "You've found a key!";
const string MenuText::TILE_KEY_EXAMINE = "There's a key in this room!";
const string MenuText::TILE_NO_ACTION = "";
const string MenuText::TILE_NOTHING_TO_EXAMINE = "There's nothing to examine in this room!";
const string MenuText::TILE_STAIRS_ACTION = "You've found some stairs!";
const string MenuText::TILE_STAIRS_MOVE = "You took the stairs!";
