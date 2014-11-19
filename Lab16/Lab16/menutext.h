/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	header for menu text
*/

#ifndef _MENUTEXT_H_INCLUDED_
#define _MENUTEXT_H_INCLUDED_

using namespace std;

class MenuText{
public:

	static const string ERROR_FAILED_INITIALIZE;
	static const string ERROR_FILE_CANNOT_READ;
	static const string ERROR_FILE_NAME;
	static const string ERROR_INVALID_INPUT;
	static const string ERROR_INVALID_MOVE;
	//static const string ERROR_NO_INVENTORY_SPACE;
	//static const string ERROR_NO_ITEMS;
	//static const string ERROR_NO_ROOM;
	//static const string ERROR_NO_ROOM_ITEMS;

	static const string GAME_DOOR_FOUND;
	static const string GAME_KEY_FOUND;
	//static const string GAME_QUIT;
	//static const string GAME_WINNER;

	static const string FILE_NAME_IMAGE_DOOR;
	static const string FILE_NAME_IMAGE_KEY;
	static const string FILE_NAME_IMAGE_PLAYER;
	static const string FILE_NAME_LAYOUT;

	//static const string INVALID_MENU_CHOICE;

	//static const string MAP_EDGE_BOTTOM;
	//static const string MAP_EXPLORE;
	//static const string MAP_FIND_KEYS;

	static const string MENU_ASK_DIRECTION;
	static const string MENU_HELP;
	static const string MENU_HELP_SHORT;
	//static const string MENU_ITEM_DISPLAY_INVENTORY;
	//static const string MENU_ITEM_SELECT;

	//static const string PLAYER_INVENTORY_EMPTY;
	//static const string PLAYER_INVENTORY_KEY_1;
	//static const string PLAYER_INVENTORY_KEY_2;
	//static const string PLAYER_INVENTORY_KEY_3;
	//static const string PLAYER_INVENTORY_SLOTS;
};

#endif