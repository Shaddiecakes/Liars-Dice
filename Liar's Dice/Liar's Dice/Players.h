#pragma once
#include <iostream>

using namespace std;

//Player class to set and get the amount of players.
class Players
{
private:
	int numPlayers;

public:
	void setPlayers(const int& amount)
	{
		numPlayers = amount;
	}

	const int& getPlayers() const
	{
		return numPlayers;
	}
};

class Call
{
private:
	int calledPlayer;

public:
	void callPlayer(const int& player)
	{
		calledPlayer = player;
	}

	const int& playerCalled() const
	{
		return calledPlayer;
	}
};