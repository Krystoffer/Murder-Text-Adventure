#include "Item.h"



Item::Item(string itemName, string itemLocation, string itemDescription)
	{
		name = itemName;
		location = itemLocation;
		description = itemDescription;
	}

string Item::getName()
	{
		return name;
	};

string Item::getLocation()
	{
		return location;
	};

string Item::getDescription()
	{
		return description;
	};

void Item::setWeapon(bool newStatus)
	{
		isWeapon = newStatus;
	};

bool Item::checkWeapon()
	{
		return isWeapon;
	}

Item::~Item()
	{
	}
