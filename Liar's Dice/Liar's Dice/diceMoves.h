#pragma once
#include <iostream>

using namespace std;
//The call class will be used to call which dice are being played.
class callDice
{
private:
	int call;

public:
	void setCall(const int& diceCall)
	{
		call = diceCall;
	}

	const int& getCall() const
	{
		return call;
	}
};

class foundDice
{
private:
	int counted;

public:
	void setCounted(const int& diceCounted)
	{
		counted = diceCounted;
	}

	const int& getCounted() const
	{
		return counted;
	}
};