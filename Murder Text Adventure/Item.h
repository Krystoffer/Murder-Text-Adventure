#pragma once
#include <string>

using namespace std;

class Item
	{
		private:
		string name;
		string location;
		string description;
		bool isWeapon = false;

		public:
		Item(string itemName, string itemLocation, string itemDescription);
		string getName();
		string getLocation();
		string getDescription();
		void setWeapon(bool newStatus);
		bool checkWeapon();
		~Item();
	};

