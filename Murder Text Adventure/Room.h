#pragma once

// Declare libraries used
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Declare classes used
#include "Item.h"
#include "Character.h"

using namespace std;

class Room
	{
		private:
		string name;
		int location;			// This will be used later on for the room index in the adjacency matrix
		string description;
		vector<Character*> people;
		vector<Item*> objects;

		public:
		Room(string roomName, int newLocation);
		string getName();
		int getLocation();
		void setDescription(string newDescription);
		string getDescription();
		void addPeople(Character* suspect);
		void removePeople(Character* suspect);
		void printPeople();
		int noOfPeople();
		bool itemInRoom(string itemName);
		bool suspectInRoom(string suspectName);
		void addItem(Item* object);
		void removeItem(Item* object);
		string searchRoom();
		string examine(Item* object);
		~Room();
	};

