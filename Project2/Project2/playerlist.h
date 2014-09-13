/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	no longer static class wrapper for an array of Player
	Steve Suh
*/
class Player; // foward declaration: http://www.cplusplus.com/forum/articles/10627/#msg49679

#include <memory>

using namespace std;

class PlayerList
{
private:
	int numberOfPlayers; // now it can go above 20
	string fileName; 
	unique_ptr<Player[]> players; // unique_ptr allows for resetting/replacing exisitng pointer[] with new pointer[]. it has its own delete call.

public:
	PlayerList();
	PlayerList(int playerCount, string fName); // unused right now

	void addPlayerToExistingList(Player *pl); // this one handles an already initalized array
	void addPlayerToNewList(Player *pl);
	void createArray(int size);
	void deleteArray();
	bool doesFileExist();
	int findPlayer(string name);

	string getFileName();
	int getNumberOfPlayers();
	Player* getPlayer(int num);

	string printPlayers(); // return string, so we dont have include iostream everywhere				

	void setFileName(string name);
};