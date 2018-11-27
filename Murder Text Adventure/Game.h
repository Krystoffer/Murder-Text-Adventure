#pragma once

// Declare libraries used
#include <fstream>
#include <map>
#include <sstream>
#include <cstdlib>
#include <ctime>

// Declare classes used
#include "Character.h"
#include "Item.h"
#include "Room.h"
#include "Player.h"

using namespace std;

// Function declarations
void inGameInput();
void playerCommand(string command, string target);
void titleScreen();
void helpScreen();
void showMap();
void printFile(string filename);
void loadRoom();
void loadAdjMatrix();
void loadSuspect();
void loadItem();
void go(string roomName);
void find(string charName);
void suspectsMove();
void examine(string itemName);
void get(string itemName);
void drop(string itemName);
void search();
void question(string suspectName);
void gather();
void accuse(string suspectName);
void printCPL();

class Game
	{
		private:


		public:
		Game();
		void gameStart();
		~Game();
	};
