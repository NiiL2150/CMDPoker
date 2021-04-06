#pragma once
#include "Card.cpp"

class Player
{
protected:
	Card* hand; //Two cards
	string name; //Name
	int money; //Money
	bool bet; //Defines if the player is active this round
	bool active; //Defines if the player hasn't lost yet
	bool isPlayer; //PlayerOrBot
public:
	Player(string _name, int _money, int _isPlayer);

	Card* GetHand() const;
	void SetHand(Card* _hand);

	string GetName() const;
	void SetName(string _name);

	int GetMoney() const;
	void SetMoney(int _money);

	bool GetBet() const;
	void SetBet(bool _bet);

	bool GetActive() const;
	void SetActive(bool _active);

	bool GetIsPlayer() const;
	void SetIsPlayer(bool _isPlayer);
};

class OnlinePlayer : public Player {
private:
	string ip;
};