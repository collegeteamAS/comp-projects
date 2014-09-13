/*
	Andre Allan Ponce
	Steve Suh
	a_ponce1@u.pacific.edu
	h_suh@u.pacific.edu
	Project2 main. Should be interactive with TWO menus
*/


#include <string>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <random>
#include "player.h"
#include "playerlist.h"
#include "menutext.h"

using namespace std;

Player createNewPlayer(int loc);
int convertStringToNum(string num);  
int menuChoice(string displayText);
void menuOne();
void menuTwo(PlayerList* pList);
void modifyPlayer(PlayerList* pList, string playerName);
int promptAge(string loc);
string promptName(string prompt);
bool readInFile(PlayerList* pList);
void saveFile(PlayerList* pList);

int main(){
	menuOne(); // efficiency!
	return 0;
}

/*
	converts a string to an int
	@author Andre Allan Ponce
	@param num - the string to convert
	@returns the number as an int (NOTE, if NaN is before num, returns 0. if num is before NaN, returns num before NaN)
*/
int convertStringToNum(string num){
	int playerNum = atoi(num.c_str()); // so much easier to type than Integer.parseInt(String)
	return playerNum;
}

// Steve suh
Player createNewPlayer(){
	Player pl;
	pl.setName(promptName("Name: "));
	pl.setAge(promptAge("Age: "));
	cout << "\n";
	return pl;
}

Player createRandomPlayer()
{
	string playerNames[20] ={"Jason",
							"Jack",
							"John",
							"Joseph",
							"Job",

							"Jonathan",
							"James",
							"Jim",
							"Josh",
							"Jay",

							"Jose",
							"Johnson",
							"Jimmy",
							"Jake",
							"Jeff",

							"Jorge",
							"Joy",
							"JiaLingXu",
							"Jeremy",
							"Joshua"};

		random_device rd; //a random, large number like 32248906489
		Player rdpl;
		int ranNum = rd()%20;	// a random number between 0~19
		rdpl.setName(playerNames[ranNum]);//setting the name randomly picked from an arbitrary list
		rdpl.setAge(10 + ranNum);//setting age randomly between 10~29
		cout<<"Generated a player."
			<<"\nName: " << playerNames[ranNum]
			<<"\nAge  : " << 10+ranNum 
			<<"\n";
		return rdpl;
}

/*
	feed it menu text, it will prompt for option
	@author Andre Allan Ponce
	@param displayText - the text to display (should be one of the MenuText MENUs)
	@returns the choice the user made, which should be an int.
*/
int menuChoice(string displayText){
	cout << displayText << MenuText::MENU_CHOICE;
	string choice; 
	cin >> choice;
	return convertStringToNum(choice); // by doing this, we can say invalid input is 0! (if user puts in NaN...)
}

/*
	this is the first menu's interface
	runs forever until user enters 3, manually closes program, or presses the power button.
	@author Andre Allan Ponce
*/
void menuOne(){
	while(true){
		int choice = menuChoice(MenuText::MENU_ONE);
		switch(choice){
		case 1 : { // New File
			PlayerList *pList = &PlayerList();
			pList->createArray(20);
			menuTwo(pList);
			break;
		}
		case 2 : { // Open File
			PlayerList *pList = &PlayerList();
			if(readInFile(pList)){
				menuTwo(pList);
			}
			break;
		}
		case 3 : { // Exit
			exit(0);
			break;
		}
		default : { // Bad Menu choice
			cout << MenuText::INVALID_MENU_CHOICE;
			break;
		}
		}
	}
}

/*
	this is the second menu's interface
	@author Andre Allan Ponce
	Steve Suh
*/
void menuTwo(PlayerList* pList){
	bool isMenuTwo = true;
	while(isMenuTwo){
		int choice = menuChoice(MenuText::MENU_TWO);
		// cout << pList->getNumberOfPlayers();
		switch(choice){
		case 1 : { // Print all players
			cout << pList->printPlayers();
			break;
		}
		case 2 : { // Create a new player!
			pList->addPlayerToExistingList(&createNewPlayer()); 
			break;
		}
		case 3 : { // Generate a random player and add.
			pList->addPlayerToExistingList(&createRandomPlayer());  
			break;
		}
		case 4 : { // Modify a player's name/Age!
			modifyPlayer(pList,promptName(MenuText::PROMPT_PLAYER_NAME)); 
			break; 
		}
		case 5 : { // Save the data into a file
			saveFile(pList);
			break;
		}
		case 6 : { // Close File
			pList->deleteArray();
			isMenuTwo = false;
			break;
		}
		default : { // bad menu choice
			cout << MenuText::INVALID_MENU_CHOICE;
			break;
		}
		}
	}
}

// Steve suh
void modifyPlayer(PlayerList* pList, string playerName)
{

	if (pList->findPlayer(playerName)!=-1)
	{
			int x= pList->findPlayer(playerName);
			pList->getPlayer(x)->print();

			cout<< "Modify this player's name if necessary:";
			string newName;
			cin >> newName;
			pList->getPlayer(x)->setName(newName);

			cout<< "\nModify this player's age if necessary:";
			int newAge;
			cin >> newAge;
			pList->getPlayer(x)->setAge(newAge);

	}
	else
		cout << "Invalid player name";
}

// Steve suh
int promptAge(string loc){
	cout << loc;
	int age;
	cin >> age;
	return age;
}

/*
	Because we can prompt for filename or playername
	@author Andre Allan Ponce
	@param prompt - the prompt text
	@returns the response from user
*/
string promptName(string prompt){
	cout << prompt;
	string name;
	cin >> name;
	return name;
}

/*
	Reads in file by prompting user for filename, opening file, 
	getting the firstline (which should be number of players) and 
	reading until file ends or we have reached number of players

	NOTES:
		- I swear, it seems that this block is rather lengthy and should be simplified, but I'm not sure how.

	@author Andre Allan Ponce
	@returns true if file was read perfectly, false if some error occured
*/
bool readInFile(PlayerList* pList){
	ifstream inFile;
	try{
		string fileName = promptName(MenuText::PROMPT_FILE_NAME);
		inFile.open(fileName.c_str()); // the book said to use cstrings for open() function
		if(!inFile.good()){ 
			throw MenuText::ERROR_FILE_NAME; // any starting I/O errors will be taken care of
		}
		// cout << "filenamecheckgood\n"; // debug
		string line;
		getline(inFile, line); 
		int playerNum = convertStringToNum(line);
		if(playerNum <= 0 || playerNum >= 20){ // 0 or less should be impossible; we are to assume that 20 is max players
			throw MenuText::ERROR_FILE_CONTENTS; // we can differientiate between I/O errors or bad file formatting
		}
		pList->createArray(playerNum);
		// cout << "filecontentsgood\n"; // debug
		while(!inFile.eof()){ // changed to eof because serious I/O errors should throw automatically
			getline(inFile, line);
			string name = line;
			getline(inFile, line);
			int age = convertStringToNum(line);
			pList->addPlayerToNewList(&Player(name, age)); // pointers, yo 
			// cout << "addingplayers\n"; // debug
		}
		pList->setFileName(fileName);
		inFile.close();
		return true;
	}
	catch(string text){
		cout << text; // will display custom error message text
	}
	catch(...){ // ... catches everything else, just in case
		cout << MenuText::ERROR_UNKNOWN; // we dont know what happened, yo
	}
	inFile.close();
	return false;
}

//Steve Suh
void saveFile(PlayerList* pList)
{
	ostringstream tempor;
	tempor << pList -> getNumberOfPlayers();
	string resultString = tempor.str();
		for(int i=0;i<pList -> getNumberOfPlayers();i++)
		{
			ostringstream tem;
			tem << pList->getPlayer(i)->getAge();
			resultString += "\n"+pList->getPlayer(i)->getName()+"\n" + tem.str() ;
		}
		string fileName;
		if(pList->doesFileExist()){
			fileName = pList->getFileName();
			cout << MenuText::SAVING;
		}
		else{
			fileName = promptName(MenuText::PROMPT_FILE_NAME);
		}
		ofstream outFile (fileName.c_str(), ofstream::out);
		outFile << resultString;
		outFile.close();
		cout << MenuText::SAVING_SUCCESS;
}
