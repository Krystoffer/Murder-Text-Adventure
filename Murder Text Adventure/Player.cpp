#include "Player.h"



Player::Player()
	{
	};

void Player::setLocation(string newLocation)
	{
		location = newLocation;
	};

string Player::getLocation()
	{
		return location;
	};

string Player::viewInventory()
	{
		stringstream output;

		if (inventory.size() > 0)
			{
				output << "Your inventory:" << endl;
				for (int i = 0; i < inventory.size(); i++)
					{
						output << "- " << inventory[i] -> getName() << endl;
					};
			}
		else
			{
				output << "There is nothing here in your inventory" << endl;
			};

		return output.str();
	};

bool Player::itemInInventory(string itemName)
	{
		bool inInventory = false;

		for (int i = 0; i < inventory.size(); i++)
			{
				if(inventory[i] -> getName() == itemName)
					{
						inInventory = true;
					};
			};

		return inInventory;
	};

void Player::addItem(Item* object)
	{
		inventory.push_back(object);
	};

void Player::dropItem(Item* object)
	{
		for (unsigned int i = 0; i < inventory.size(); i++)
			{
				if (inventory[i] == object)
					{
						inventory.erase(inventory.begin() + i);
					};
			};
	};

string Player::examine(Item* object)
	{
		if(inventory.size() > 0)
			{
				for (int i = 0; i < inventory.size(); i++)
					{
						if (inventory[i] == object)
							{
								return inventory[i] -> getDescription();
							};
					};
				return "There is no item with that name in my inventory or in this room";
			}
		else
			{
				return "There is no item with that name in my inventory or in this room";
			};
	};

Player::~Player()
	{
	}
