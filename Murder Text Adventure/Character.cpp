#include "Character.h"



Character::Character(string charName, string charLocation)
	{
		name = charName;
		location = charLocation;
	};

string Character::getName()
	{
		return name;
	};

void Character::setLocation(string newLocation)
	{
		location = newLocation;
	};

string Character::getLocation()
	{
		return location;
	};

void Character::setAlibi(string newAlibi)
	{
		alibi = newAlibi;
	};

string Character::getAlibi()
	{
		return alibi;
	};

void Character::setMurderer(bool newStatus)
	{
		isMurderer = newStatus;
	};

bool Character::checkMurderer()
	{
		return isMurderer;
	};

void Character::setVictim(bool newStatus)
	{
		isVictim = newStatus;
	};

bool Character::checkVictim()
	{
		return isVictim;
	};

Character::~Character()
	{
	};