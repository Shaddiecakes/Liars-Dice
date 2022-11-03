#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "Players.h"
#include "diceMoves.h"

using namespace std;

int main()
{
	//Initializing variables. Choice for input. currentCount will raise until someone calls a player where it will be reset and set by another player.
	int numdice;
	int choice;
	int currentCount = 0;
	Players numPlayers;
	callDice diceMove;
	foundDice diceCounting;

	//Ask the players if they would like to read the rules.
	cout << "Would you like to read the rules?" << endl << "1. Yes" << endl << "2. no" << endl;
	cin >> choice;

	//Verify choice.
	while (choice < 1 || choice > 2)
	{
		cout << "Invalid choice. Please enter 1 or 2." << endl;
		cin >> choice;
	}
	cout << endl;

	//Open the rules txt and print it out when wanted. Add an end line at the end to make it easier to see player count input.
	if (choice == 1)
	{
		string line;
		ifstream gameRules("Liar's Dice Rules.txt");

		if (gameRules.is_open())
		{
			while (getline(gameRules, line))
			{
				cout << line << "\n";
			}
			cout << endl;
			gameRules.close();
		}
	}

	//Get the number of players and make sure it's more than two.
	cout << "How many players will be playing?" << endl;
	int playerCount;
	cin >> playerCount;

	while (playerCount < 2) {
		cout << "Invalid amount of players " << playerCount << ", please try again." << endl;
		cin >> playerCount;
	}
	cout << endl;

	numPlayers.setPlayers(playerCount);
	cout << "You are playing with " << numPlayers.getPlayers() << " players." << endl;

	//Establish how many dice will be needed.
	numdice = (numPlayers.getPlayers() * 5);

	//Create a vector to serve as the dice set.
	srand(unsigned(time(nullptr)));
	vector<int> v(numdice);
	generate(v.begin(), v.end(), rand);

	cout << "Each player gets five dice for a total of " << numdice << " dice." << endl << endl;


	while (numPlayers.getPlayers() > 1) {
		//Iterate through each player until each player has had a turn.
		for (int i = 1; i <= numPlayers.getPlayers(); i++)
		{
			cout << "Player " << i << ". What would you like to do?" << endl << "1. Check dice" << endl << "2. Call play" << endl << "3. Exit" << endl;
			cin >> choice;

			while (choice < 1 || choice > 3)
			{
			cout << "Invalid choice. Please pick an option by entering a number 1 - 3." << endl;
			cin >> choice;
			}
			cout << endl;

			//Choice to check the current player's dice before continuing with the game.
			if (choice == 1)
			{
				//Print the contents of the vector based on the current player and their dice set.
				for (int o = i; o < (i + 1); o++)
				{
					cout << v.at(o) << " ";
				}

				cout << endl << "What would you like to do now?" << endl << "1. Call dice" << endl << "2. Exit" << endl;
				cin >> choice;

				while (choice > 2 || choice < 1)
				{
					cout << "Invalid input. Please enter 1 or 2." << endl;
					cin >> choice;
				}
				cout << endl;

				if (choice == 1)
				{
					choice = 2;
				}

				else if (choice == 2)
				{
					return 0;
				}
			}

			//This is how the game is played.
			if (choice == 2)
			{
				int move;

				//If someone has already called the amount of dice then it will continue getting higher but if not then it will pass over the if statement.
				if (currentCount < 1)
				{
					cout << "How many dice will you call?" << endl;
					cin >> currentCount;

					//Validate input
					while (currentCount < 0 || currentCount >(numPlayers.getPlayers() * 5))
					{
						cout << "Invalid amount. Please enter an amount above 0 and below " << numPlayers.getPlayers() * 5 << "." << endl;
						cin >> currentCount;
					}
				}

				//This is the loop of the majority of the game. Each player has to call the face of the die while the amount of die being called constantly increases.
				cout << "What die face will you call?" << endl;

				cin >> move;

				//validate move
				while (move < 0 || move > 9)
				{
					cout << "Invalid move, please make a move 0-9" << endl;
					cin >> move;
				}

				//This displays what the current player has played and allows anyone to call the current player out.
				diceMove.setCall(move);
				cout << "The current player has played " << currentCount << " " << diceMove.getCall() << "'s. Would anyone like to call player " << i << " out?" << endl << "1. Yes" << endl << "2. No" << endl;
				cin >> choice;

				//Validate calling someone out or not.
				while (choice < 1 || choice > 2)
				{
					cout << "Invalid input. Please enter 1 or 2." << endl;
					cin >> choice;
				}

				//Calling a player out and now checking whether the play was correct or not.
				if (choice == 1)
				{
					cout << "Which player is calling player " << i << " out?" << endl;
					cin >> choice;

					while (choice < 0 || choice > numPlayers.getPlayers())
					{
						cout << "Invalid move, please enter a move above zero and below " << playerCount << endl;
						cin >> choice;
					}
					cout << "Player " << choice << " is calling out player " << i << " as a liar. Let's see if they are correct." << endl << endl;

					//Checking to see who loses.
					int callCount = count(v.begin(), v.end(), move);
					cout << callCount << " counted" << endl;

					diceCounting.setCounted(callCount);

					if (diceCounting.getCounted() == currentCount)
					{
						cout << "Player " << choice << " was incorrect and player " << i << " survives!" << endl << endl << "Dice will now be moved and the last dice set has been removed. Your dice may stay the same or change." << endl;
						v.resize(v.size() - 5);
						numPlayers.setPlayers(playerCount - 1);
						currentCount = -1;
					}

					else
					{
						cout << "Player " << choice << " was correct and player " << i << " lied!" << endl << endl << "Dice will now be moved and the last dice set has been removed. Your dice may stay the same or change." << endl;
						v.resize(v.size() - 5);
						numPlayers.setPlayers(playerCount - 1);
						currentCount = -1;
					}
				}

				//At the end of each turn the call has to count one more amount of die than the last.
				currentCount++;
			}

			//Option to exit the game.
			else if (choice == 3)
			{
				return 0;
			}
		}
	}

	//Ending the game.
	cout << endl << "Congratulations! You are the last player! You win!" << endl;
}