
#include <string>
#include <vector>
#include <locale>
#include <fstream>
#include <iostream>
//#include <Windows.h> // keyboard input!
//#include <wincon.h> // more keyboard input
#include <time.h>
//#include <sstream>
//#include "location.h"
//#include "room.h" // debug
#include "game.h"

// debug test methods:
void fillArrays(std::string fileName);

// real methods:
int convertStringToNum(std::string numStr);

int main(){
	// antohter debug
	// now with roomdata and game
	Game game = Game();
	game.readInFile("rooms");
	game.readInItemFile("items");
	game.runGame();

	/* proof of concept
	these methods load up a file and display it.
	actual file loading will use RoomData class.
	
	std::string file = "rooms";
	fillArrays(file);
	//*/

	//int state = 0;
	//clock_t currTime;

	// testing the input!:  http://www.cplusplus.com/forum/beginner/75529/
	// lets see this.
	/*
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD NumInputs = 0;
    DWORD InputsRead = 0;
    bool running = true;
    INPUT_RECORD* irInput = new INPUT_RECORD;
    GetNumberOfConsoleInputEvents(hInput, &NumInputs);
    while(running)
    {
		//currTime = clock();
        ReadConsoleInput(hInput, irInput, 1, &InputsRead);
        //std::cout << irInput.Event.KeyEvent.wVirtualKeyCode << std::endl;
		// irInput.Event.KeyEvent.wVirtualKeyCode;

		
        switch(irInput->Event.KeyEvent.wVirtualKeyCode)
        {
            case VK_ESCAPE:{
                running = false;
                //Quit The Running Loop
				break;
			}
            case VK_LEFT:
			case VK_NUMPAD4:{
				std::cout << "left!\n";
				break;
			}
			case VK_UP:
			case VK_NUMPAD8:{
				std::cout << "up!\n";
				break;
			}
			case VK_RIGHT:
			case VK_NUMPAD6:{
				std::cout << "right!\n";
				break;
			}
			case VK_DOWN:
			case VK_NUMPAD2:{
				std::cout << "down!\n";
				break;
			}
        } 
		
        
    }
	//*/
	return 0;
}

/*
	converts a string to an int
	@author Andre Allan Ponce
*/
int convertStringToNum(std::string numStr){
	int num = atoi(numStr.c_str());
	return num;
}

/*
void fillArrays(std::string fileName){
	std::ifstream inFile;
	inFile.open(fileName.c_str());
	if(inFile.good()){
		std::string line;
		int id, rows, cols;
		inFile >> id;
		inFile >> rows;
		inFile >> cols;
		inFile.ignore();
		std::cout << "ID: " << id << "\n";
		std::cout << "height: " << rows << "\n";
		std::cout << "width: " << cols << "\n";
		Room *romPtr = &Room(id,0,0,rows,cols,false,false);
		romPtr->createArray();
		//std::stringstream in;
		//std::getline(inFile, line);
		std::string test = "";
		for(int i = 0; i < rows; i++){
			std::getline(inFile, line);
			std::cout << i << " " << line << "\n" << test;
			romPtr->fillArrayRow(line,i);
			//in << line;
			
			//in.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // apparently getline has been overloaded by sstream, so we have to do this to enter next line.
		}
		//in << test;
		//romPtr->fillArray(in);
		inFile.close();
		std::cout << romPtr->doesRoomHaveCloset() << "\n";
		std::cout << "ID: "<<romPtr->getRoomID() << "\n";
		std::cout << "heigh: " << romPtr->getHeight() << "\n";
		std::cout << "wid: " << romPtr->getWidth() << "\n";
		std::cout << "x: " << romPtr->getX() << "\n";
		std::cout << "y: " << romPtr->getY() << "\n";
		std::cout << "room:\n";
		std::cout << romPtr->draw();
	}
}//*/