#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Item.h"

using namespace std;

class Player
	{
		private:
		string location = "YOUR ROOM";
		vector<Item*> inventory;

		public:
		Player();
		void setLocation(string newLocation);
		string getLocation();
		string viewInventory();
		bool itemInInventory(string itemName);
		void addItem(Item* object);
		void dropItem(Item* object);
		string examine(Item* object);
		~Player();
	};

