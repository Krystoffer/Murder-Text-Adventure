#include "Game.h"

// Initialize the necessary game running variables
bool titleRunning = true;
bool gameRunning = false;
bool winGame = false;
bool freezeSuspects = false;
string corpseLocation;

// Initialize the player object
Player player;

// Create a map that contains a pointer to a Room
map<string, Room*> rooms;

// Create vectors that contains names for the purpose of validation
vector<string> roomList;
vector<string> suspectList;
vector<string> itemList;

// Create an adjacency matrix for all the rooms
int adjRoomMatrix[15][15];

// Create a vector of characters
vector<Character> suspects;

// Create a vector of items
vector<Item> items;

// Create output variable
stringstream output;

Game::Game()
	{
	};

void Game::gameStart()
	{
		// Set the current time as a RNG seed
		srand(time(NULL));

		// Display splash screen
		printFile("splash.txt");
		cout << endl;
		system("pause");

		// Display title screen
		while (titleRunning)
			{
				titleScreen();
			};

		// Initialize the necessary game data
		loadRoom();
		loadAdjMatrix();
		loadSuspect();
		loadItem();

		system("CLS");

		// Game Loop
		while (gameRunning)
			{
				if(!freezeSuspects) 
					{
						suspectsMove();
					};
				printCPL();
				cout << output.str();
				output.str("");
				inGameInput();
			};

		system("CLS");
		if (winGame)
			{
				cout << "Congratulations! You have solved the crime and the culprit is arrested." << endl << endl;
			}
		else
			{
				cout << "Shame on you... Your deduction is incorrect. Your reputation is now tarnished and the killer on the loose" << endl << endl;
			};
		system("pause");
	};

Game::~Game()
	{
	};

// This is a function that prompts the user to input a command while playing the game
void inGameInput()
	{	
		string action;
		
		cout << "What do you want to do?" << endl;
		getline(cin, action);
		for (unsigned int i = 0; i < action.length(); i++)	//
			{												// Make the user input into upper case to
				action[i] = toupper(action[i]);				// prevent code from not recognizing the command
			};												//

		string verb;
		string noun;
		int position;

		position = action.find(' ');				//
		verb = action.substr(0, position);			// Break the user input into VERB and NOUN
		noun = action.substr(position + 1);			//

		system("CLS");

		playerCommand(verb, noun);					// Call another function to further process the user input
	};

// This is a function that proccesses the command that is inputed by the user
//
// It takes 2 argument as an input which is the command and the target.
void playerCommand(string command, string target)
	{
		vector<string> commandList = {"QUIT", "HELP", "MAP", "GO", "FIND", "SEARCH", "QUESTION", "EXAMINE", "GET", "DROP", "INVENTORY", "GATHER", "ACCUSE"};
		// Use the index of the value from the array above and parse it in as an input for a switch case
		
		int commandIndex = 100;							// Initialize the value as 100 so that if the command doesn't exist it will go to default
		for (int i = 0; i < commandList.size(); i++)
			{
				if (command == commandList[i])
					{
						commandIndex = i;
					};
			};

		switch (commandIndex)
			{
				case 0:
					gameRunning = false;
					break;
				case 1:
					helpScreen();
					break;
				case 2:
					showMap();
					break;
				case 3:
					go(target);
					if(freezeSuspects == true) freezeSuspects = false;
					break;
				case 4:
					find(target);
					if(freezeSuspects == true) freezeSuspects = false;
					break;
				case 5:
					output << rooms[player.getLocation()] -> searchRoom() << endl;
					if(freezeSuspects == true) freezeSuspects = false;
					break;
				case 6:
					question(target);
					if(freezeSuspects == true) freezeSuspects = false;
					break;
				case 7:
					examine(target);
					if(freezeSuspects == true) freezeSuspects = false;
					break;
				case 8:
					get(target);
					if(freezeSuspects == true) freezeSuspects = false;
					break;
				case 9:
					drop(target);
					if(freezeSuspects == true) freezeSuspects = false;
					break;
				case 10:
					output << player.viewInventory() << endl;
					if(freezeSuspects == true) freezeSuspects = false;
					break;
				case 11:
					gather();
					if(freezeSuspects == false) freezeSuspects = true;
					break;
				case 12:
					accuse(target);
					if(freezeSuspects == true) freezeSuspects = false;
					break;
				default:
					output << "Command doens't exist" << endl << endl;
					break;
			}
	};

// This is a function to change the current location of the player
void go(string roomName)
	{
		bool roomExist = false;
		int currentLocation;	
		currentLocation = rooms[player.getLocation()] -> getLocation();			// Get the index of the room the player is currently in

		vector<string> adjRooms;										//
		for (int i = 0; i < 15; i++)									//
			{															// 
				if (adjRoomMatrix[currentLocation][i] == 1)				// List out all the rooms that are connected
					{													// or adjacent to the room that the player is in
						adjRooms.push_back(roomList[i]);				//
					};													//
			};															//

		for (int i = 0; i < adjRooms.size(); i++)		//
			{											//
				if (roomName == adjRooms[i])			//	Validate the existence of the room
					{									//	the user is trying to enter
						roomExist = true;				//
					};									//
			};											//

		if (roomExist)
			{
				
				player.setLocation(roomList[rooms[roomName] -> getLocation()]);				// Update the location of the user
			}
		else
			{
				output << "I don't think there's a room nearby with that name" << endl << endl;
			}
	};

// This is a function to display the location of a certain suspect
void find(string charName)
	{
		int suspectIndex;
		bool suspectExist = false;

		for (int i = 0; i < suspectList.size(); i++)
			{
				if (suspectList[i] == charName)
					{
						suspectExist = true;
						suspectIndex = i;
					};
			};

		if (suspectExist)
			{
				output << suspects[suspectIndex].getName() << " is in " << rooms[suspects[suspectIndex].getLocation()] -> getName() << endl << endl;
			}
		else
			{
				output << "There is no one with that name" << endl;
			}
	};

// This is a function to display the title screen
void titleScreen()
	{
		system("CLS");
		printFile("title.txt");

		string outGameInput;
		getline(cin,outGameInput);									// Prompt user for the next action
		for (unsigned int i = 0; i < outGameInput.length(); i++)
			{
				outGameInput[i] = toupper(outGameInput[i]);
			};

		if (outGameInput == "START")
			{
				titleRunning = false;
				gameRunning = true;
			}
		else if (outGameInput == "HELP")
			{
				helpScreen();
			}
		else if (outGameInput == "QUIT")
			{
				titleRunning = false;
			}
		else
			{
				system("CLS");
			}
	};

// This is a function to display the help screen
void helpScreen()
	{
		printFile("help.txt");

		if (!gameRunning)
			{
				cout << endl << endl << "Press any key to go back to the title screen" << endl;
				system("pause");
			}
		else
			{
				cout << endl << endl << "Press any key to back to the game" << endl;
				system("pause");
				system("CLS");
				printCPL();
			}
	};

// This is a function to display the map
void showMap()
	{
		printFile("map.txt");

		cout << endl << endl << "Press any key to go back to the game" << endl;
		system("pause");
		system("CLS");
		printCPL();
	};

// This is a function to print everything inside a single text file
//
// It takes 1 argument as an input which is the file name.
void printFile(string filename)
	{
		system("CLS");

		string line;
		ifstream file;
		file.open (filename);
		while(getline(file, line))
			{
				cout << line << endl;
			};
		file.close();
		
		cout << endl;
	}

// This is a function to load all the room data and store it into the map that has been created
void loadRoom()
	{
		string roomName;
		string line;
		ifstream file;

		file.open("roomData.txt");

		int index = 0;
		while (getline(file, line))
			{
				roomName = line;										//
				for (unsigned int i = 0; i < roomName.length(); i++)	//
					{													// Make all the room names in upper case for validation purpose
						roomName[i] = toupper(roomName[i]);				//
					};													//

				roomList.push_back(roomName);							// Push room name into the list

				rooms[roomName] = new Room(line, index);				// Create the key, value pair and initialize the room name and index
				getline(file, line);
				rooms[roomName] -> setDescription(line);				// Set the room description
				getline(file, line);									// Getline is used to skip the blank line in the txt file

				index++;
			}
	};

// This is a function to load the adjacency matrix for all the rooms
void loadAdjMatrix()
	{
		for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
					{
						adjRoomMatrix[i][j] = 0;
					};
			};

		string line;
		int index1;
		int index2;
		ifstream file;

		file.open("adjMatrix.txt");
		while (getline(file, line))
			{
				index1 = stoi(line);		// Convert string to int
				getline(file, line);
				index2 = stoi(line);		// Convert string to int

				adjRoomMatrix[index1][index2] = 1;
				adjRoomMatrix[index2][index1] = 1;
			}

	};

// This is a function to load the suspect names and initialize them as objects
void loadSuspect()
	{
		string line;
		ifstream file;

		int roomIndex;

		file.open("suspectData.txt");
		while (getline(file, line))
			{
				roomIndex = rand() % 15;										// Randomize starting room index
				suspects.push_back(Character(line, roomList[roomIndex]));		// Create the suspect

				for (int i = 0; i < line.length(); i++)
					{
						line[i] = toupper(line[i]);
					}
				suspectList.push_back(line);									// Push back suspect name in upper case for validation purpose
			};

		for (int i = 0; i < suspects.size(); i++)
			{
				rooms[suspects[i].getLocation()] -> addPeople(&suspects[i]);	// Add suspect inside the room
			};

		int victimIndex = rand() % suspects.size();
		suspects[victimIndex].setVictim(true);

		string description = rooms[suspects[victimIndex].getLocation()] -> getDescription();												//
		description = description + "\n" + suspects[victimIndex].getName() + "'s cold dead body laid down on the floor can be seen";		//	Change the description of the room which is the crime scene
		rooms[suspects[victimIndex].getLocation()] -> setDescription(description);															//

		corpseLocation = suspects[victimIndex].getLocation();				// Store the room for the corpse object later on

		rooms[suspects[victimIndex].getLocation()] -> removePeople(&suspects[victimIndex]);		//
		suspects.erase(suspects.begin() + victimIndex);											//	Erase the victim from the list of suspects
		suspectList.erase(suspectList.begin() + victimIndex);									//

		int murdererIndex = rand() % suspects.size();
		suspects[murdererIndex].setMurderer(true);

		int temp;
		int randomIndex;

		// Initialize vector to randomize alibi
		vector<int> alibiSwap;
		for (int i = 0; i < suspectList.size(); i++)
			{
				if (i != murdererIndex)
					{
						alibiSwap.push_back(i);
					};
			};

		// Shuffle the order of the suspects in the vector
		for (int i = 0; i < alibiSwap.size(); i++)
			{
				randomIndex = rand() % alibiSwap.size();
			
				temp = alibiSwap[i];
				alibiSwap[i] = alibiSwap[randomIndex];
				alibiSwap[randomIndex] = temp;

			};

		// Set the alibis of the suspects
		suspects[alibiSwap[0]].setAlibi("Eeeek..... A dead person! Plese save me from this hell \nI was together with " + suspects[alibiSwap[1]].getName() + " at that time \nPlease believe me... I just want to go home");
		suspects[alibiSwap[1]].setAlibi("Mommy.... I'm scared... \nPlase believe me \nI was together with " + suspects[alibiSwap[0]].getName() + " at that time \nI swear. I want to meet my mommy. Mommy... Where are you?");
		suspects[alibiSwap[2]].setAlibi("Someone died.... Maybe I will be the next one to die... \nI was together with " + suspects[alibiSwap[3]].getName() + " at that time \n Please help me... I don't want to die \nI'm too yound to die");
		suspects[alibiSwap[3]].setAlibi("We're cursed!! We have angered the gods and now we are to receive our punishment \nI was together with " + suspects[alibiSwap[2]].getName() + " at that time \nSave yourself... Don't let the curse befall you too!!");
		suspects[alibiSwap[4]].setAlibi("I was spacing out alone \nAnd now..... *sob* *sob* \nMommy... Please forgive me of me for disobeying you and coming here \nI'm so sorry..... *sob* I don't want to die yet... *cries louder*");
		suspects[murdererIndex].setAlibi("What did I do to deserve this.... \nI was together with " + suspects[alibiSwap[rand() % alibiSwap.size()]].getName() + " at that time \nAnd now we all have to die!? \nNooooo.... Please get me out of here alive! I beg of you!");

	};

// This is a function to load the items and weapons and also the corpse object
void loadItem()
	{
		string line;
		ifstream file;
		string description;

		int roomIndex;

		file.open("itemData.txt");
		while (getline(file, line))
			{
				getline(file, description);
				roomIndex = rand() % 15;											// Randomize item location index
				items.push_back(Item(line, roomList[roomIndex], description));		// Create the item with random location

				for (int i = 0; i < line.length(); i++)
					{
						line[i] = toupper(line[i]);
					}
				itemList.push_back(line);					// Push back item name in upper case for validation purpose
				getline(file, description);
			};

		// Randomize murder weapon
		// Not every item can be a weapon due to the nature of the game where the description of the corpse decides the weapon
		int murderWeapon = rand() % 3;
		switch (murderWeapon)
			{
				case 0:
					items[6].setWeapon(true);
					description = "There is a buldge in the head area, looks like the victim suffered from a concussion";
					break;
				case 1:
					items[1].setWeapon(true);
					description = "The area around the mouth emits a almond-like odor";
					break;
				case 2:
					items[4].setWeapon(true);
					description = "The corpse seems rather blue, maybe the cause is respiratory failure?";
			};

		// Add the corpse to the item vector
		itemList.push_back("CORPSE");
		items.push_back(Item("Corpse", corpseLocation, description));

		// Add each item to their corresponding room
		for (int i = 0; i < items.size(); i++)
			{
				rooms[items[i].getLocation()] -> addItem(&items[i]);
			};
	};

// This is a function to move the suspects randomly around the crime scene
void suspectsMove()
	{
		int currentLocation;

		for (int i = 0; i < suspects.size(); i++)
			{
				if(rand() % 3 == 0)		// Every suspect have a 33% chance to move around after the player inputs a command
					{
						rooms[suspects[i].getLocation()] -> removePeople(&suspects[i]);			// Remove suspect from the room

						currentLocation = rooms[suspects[i].getLocation()] -> getLocation();	// Get the index of the room where the suspect is

						vector<string> adjRooms;								//
						for (int i = 0; i < 14; i++)							//
							{													//
								if (adjRoomMatrix[currentLocation][i] == 1)		// List out all the rooms that are connected
									{											// or adjacent to the room that the suspect is in
										adjRooms.push_back(roomList[i]);		//
									};											//
							};													//

						int newLocation = rand() % adjRooms.size();
						suspects[i].setLocation(roomList[rooms[adjRooms[newLocation]] -> getLocation()]);	// Update the location of the suspect
						rooms[suspects[i].getLocation()] -> addPeople(&suspects[i]);						// Add the suspect into the new room
					};
			};
	};

// This is a function to display the description of an item
void examine(string itemName)
	{
		bool itemExist = false;
		int itemIndex;
		string itemDesc;

		for (int i = 0; i < itemList.size(); i++)
			{
				if (itemList[i] == itemName)
					{
						itemExist = true;
						itemIndex = i;
					};
			};

		if (itemExist)
			{
				// Retrieve the description of the item and output it
				itemDesc = rooms[player.getLocation()] -> examine(&items[itemIndex]); // Check for the item if it is inside the room
				if (itemDesc == "-1")
					{
						itemDesc = player.examine(&items[itemIndex]);
					};
				output << "-----" << items[itemIndex].getName() << "-----" << endl;
				output << itemDesc << endl << endl;
			}
		else
			{
				output << "There is no item with that name anywhere around here" << endl << endl;
			};
	};

// This is a function to get an item from the room and place it in the player's inventory
void get(string itemName)
	{
		bool itemExist = false;
		int itemIndex;

		for (int i = 0; i < itemList.size(); i++)
			{
				if (itemList[i] == itemName)
					{
						itemExist = true;
						itemIndex = i;
					};
			};

		if (itemExist)
			{
				if (itemList[itemIndex] == "CORPSE")
					{
						output << "You cannot put a corpse inside your bag" << endl << endl;
					}
				else if(rooms[player.getLocation()] -> itemInRoom(items[itemIndex].getName()))
					{
						rooms[player.getLocation()] -> removeItem(&items[itemIndex]);		// Remove item from the room
						player.addItem(&items[itemIndex]);									// Add it to the player's inventory
						output << "Got item " << items[itemIndex].getName() << " and put it in inventory" << endl << endl;
					}
				else
					{
						output << "That item is not in this room" << endl << endl;
					};
			}
		else
			{
				output << "There is no item with that name" << endl << endl;
			};
	};

// This is a function to drop an item from the player's inventory and place it in the room
void drop(string itemName)
	{
		bool itemExist = false;
		int itemIndex;

		for (int i = 0; i < itemList.size(); i++)
			{
				if (itemList[i] == itemName)
					{
						itemExist = true;
						itemIndex = i;
					};
			};

		if (itemExist)
			{
				if(player.itemInInventory(items[itemIndex].getName()))
					{
						player.dropItem(&items[itemIndex]);								// Remove item from player inventory
						rooms[player.getLocation()] -> addItem(&items[itemIndex]);		// Add it to the room
						output << "Dropped " << items[itemIndex].getName() << " from inventory to the room" << endl << endl;
					}
				else
					{
						output << "That item is not in your inventory" << endl << endl;
					}
			}
		else
			{
				output << "There is no item with that name" << endl << endl;
			};
	};

// This is a function to ask a suspect for their alibi
void question(string suspectName)
	{
		bool suspectExist = false;
		int suspectIndex;

		for (int i = 0; i < suspectList.size(); i++)
			{
				if (suspectList[i] == suspectName)
					{
						suspectExist = true;
						suspectIndex = i;
					};
			};

		if (suspectExist)
			{
				if (rooms[player.getLocation()] -> suspectInRoom(suspects[suspectIndex].getName()))
					{
						output << "-----" << suspects[suspectIndex].getName() << "-----" << endl;
						output << suspects[suspectIndex].getAlibi() << endl << endl;
					}
				else
					{
						output << "There is no one with that name in this room" << endl << endl;
					}
			}
		else
			{
				output << "There is no one with that name" << endl << endl;
			}
	};

// This is a function to gather all the other suspects to the room the player currently is in
void gather()
	{
		for (int i = 0; i < suspects.size(); i++)
			{
				rooms[suspects[i].getLocation()] -> removePeople(&suspects[i]);
				suspects[i].setLocation(player.getLocation());
				rooms[suspects[i].getLocation()] -> addPeople(&suspects[i]);
			};
	};

// This is a function to end the game and deduce the culprit
void accuse(string suspectName)
	{
		bool suspectExist = false;
		int suspectIndex;

		for (int i = 0; i < suspectList.size(); i++)
			{
				if(suspectList[i] == suspectName)
					{
						suspectExist = true;
						suspectIndex = i;
					};
			};
		if(suspectExist)
			{
				if(rooms[player.getLocation()] -> noOfPeople() == suspects.size())				// Check if all suspects are in that room
					{
						if(rooms[player.getLocation()] -> itemInRoom(items.back().getName()))	// Check if it is the crime scene by checking if the corpse is in the room
							{
								bool weaponExist = false;
								string weaponName;
								int weaponIndex;

								while (!weaponExist)
									{
										cout << "What weapon did the murderer use?" << endl;
										getline(cin, weaponName);

										for (int i = 0; i < weaponName.length(); i++)
											{
												weaponName[i] = toupper(weaponName[i]);
											};

										for (int i = 0; i < itemList.size(); i++)
											{
												if(itemList[i] == weaponName)
													{
														weaponExist = true;
														weaponIndex = i;
													};
											};
									};

								if(player.itemInInventory(items[weaponIndex].getName()))
									{
										gameRunning = false;
										if (suspects[suspectIndex].checkMurderer() == true && items[weaponIndex].checkWeapon() == true)
											{
												winGame = true;
											};
									}
								else
									{
										output << "You can't show them the weapon and no one took it seriously"<< endl << endl;
									}
							}
						else
							{
								output << "I need to show everyone the proof of the murder to convince them" << endl << endl;
							}
					}
				else
					{
						output << "I need everyone to be present to listen to my deduction" << endl << endl;
					};
			}
		else
			{
				output << "There is no one with that name" << endl << endl;
			}

	};

// This is a function to print the player's current location
void printCPL()
	{
		cout << "*************************************************" << endl;
		cout << "You are currently in the " << rooms[player.getLocation()] -> getName() << endl;
		cout << "*************************************************" << endl;
		cout << rooms[player.getLocation()] -> getDescription() << endl << endl;
		rooms[player.getLocation()] -> printPeople();
		cout << endl;
	};