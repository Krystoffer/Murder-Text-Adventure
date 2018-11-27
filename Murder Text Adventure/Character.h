#pragma once
#include <string>

using namespace std;

class Character
	{
		private:
		string name;
		string location = "LOBBY";
		string alibi;
		bool isMurderer = false;
		bool isVictim = false;

		public:
		Character(string charName, string charLocation);
		string getName();
		void setLocation(string newLocation);
		string getLocation();
		void setAlibi(string newAlibi);
		string getAlibi();
		void setMurderer(bool newStatus);
		bool checkMurderer();
		void setVictim(bool newStatus);
		bool checkVictim();
		~Character();
	};

