
#include <string>
#include "menutext.h"

const string MenuText::ERROR_FILE_NAME = "BAd file!";
const string MenuText::ERROR_NO_INVENTORY_SPACE = "You don't have any more room in your inventory!";
const string MenuText::ERROR_NO_ITEMS = "You don't have any items to drop!";
const string MenuText::ERROR_NO_ROOM = "There's no more space in this room!";
const string MenuText::ERROR_NO_ROOM_ITEMS = "There's no items in this room!";

const string MenuText::INVALID_MENU_CHOICE = "Invalid choice, try again.";

const string MenuText::MENU_ITEM_DISPLAY_INVENTORY = "Your inventory: ";
const string MenuText::MENU_ITEM_SELECT = PLAYER_INVENTORY_SLOTS + "\n"+
	"Select which item to drop (1/2/3) or 4 to abort: ";

const string MenuText::PLAYER_INVENTORY_EMPTY = ":_   _:_   _:_   _:";
const string MenuText::PLAYER_INVENTORY_KEY_1 = ":_ K _:_   _:_   _:";
const string MenuText::PLAYER_INVENTORY_KEY_2 = ":_ K _:_ K _:_   _:";
const string MenuText::PLAYER_INVENTORY_KEY_3 = ":_ K _:_ K _:_ K _:";
const string MenuText::PLAYER_INVENTORY_SLOTS = "   1     2     3   ";
