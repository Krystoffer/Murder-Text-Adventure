#include "Room.h"



Room::Room(string roomName, int newLocation)
	{
		name = roomName;
		location = newLocation;
	};

string Room::getName()
	{
		return name;
	};

int Room::getLocation()
	{
		return location;
	};

void Room::setDescription(string newDescription)
	{
		description = newDescription;
	};

string Room::getDescription()
	{
		return description;
	};

void Room::addPeople(Character* suspect)
	{
		people.push_back(suspect);
	};

void Room::removePeople(Character* suspect)
	{
		for (unsigned int i = 0; i < people.size(); i++)
			{
				if (people[i] == suspect)
					{
						people.erase(people.begin() + i);
					};
			};
	};

void Room::printPeople()
	{
		if (people.size() == 0)
			{
				cout << "There is no one else in this room" << endl;
			}
		else if (people.size() == 1)
			{
				cout << "There is " << people[0] -> getName() << " in this room" << endl;
			}
		else
			{
				cout << "There are " << people[0] -> getName();

				for (int i = 1; i < people.size(); i++)
					{
						cout << " and " << people[i] -> getName();
					}

				cout << " in this room" << endl;
			}
	};

int Room::noOfPeople()
	{
		return people.size();
	};

void Room::addItem(Item* object)
	{
		objects.push_back(object);
	};

bool Room::itemInRoom(string itemName)
	{
		bool inRoom = false;

		for (int i = 0; i < objects.size(); i++)
			{
				if(objects[i] -> getName() == itemName)
					{
						inRoom = true;
					};
			};

		return inRoom;
	};

bool Room::suspectInRoom(string suspectName)
	{
		bool inRoom = false;

		for (int i = 0; i < people.size(); i++)
			{
				if(people[i] -> getName() == suspectName)
					{
						inRoom = true;
					};
			};

		return inRoom;
	};

void Room::removeItem(Item* object)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
			{
				if (objects[i] == object)
					{
						objects.erase(objects.begin() + i);
					};
			};
	};

string Room::searchRoom()
	{
		stringstream output;

		if (objects.size() > 0)
			{
				output << "You found:" << endl;
				for (int i = 0; i < objects.size(); i++)
					{
						output << "- " << objects[i] -> getName() << endl;
					};
			}
		else
			{
				output << "There is nothing here in this room" << endl;
			};

		return output.str();
	};

string Room::examine(Item* object)
	{
		if(objects.size() > 0)
			{
				for (int i = 0; i < objects.size(); i++)
					{
						if (objects[i] == object)
							{
								return objects[i] -> getDescription();
							};
					};
				return "-1";
			}
		else
			{
				return "-1";
			};
	};

Room::~Room()
	{
	};