#pragma once
#include "Player.cpp"
class Table
{
protected:
	vector <Player*> players; //Array of players
	int NoP; //Number of players
	int NoPr; //Number of players active this round
	int NoPa; //Number of players active
	int pot; //Total of bets by players this round
	int maxbet; //Max bet by a player
	int dealer; //Defines who is dealer this round 0-(NoP-1)
	Card* deck; //Deck of 52 cards that will be randomised
	Card* global; //3-5 public cards
	int stage; //1-5
	int CardsInGame; //Used cards from Card* deck
public:
	Table() {};
	Table(int _NoP, int _defaultMoney, string name);
	void StandardDeck();
	void Shuffle();
	void Refresh();

	void PrintTable();
	void PrintCards();
	void PrintDetails();
	void PrintControls(short ch, int maxmoney);
	void DeleteControls();

	void SetStage(int _stage);
	int GetStage() const;

	void SetNoP(int _NoP);
	int GetNoP() const;

	void SetNoPr(int _NoPr);
	int GetNoPr() const;

	void SetNoPa(int _NoPa);
	int GetNoPa() const;

	void SetPot(int _pot);
	int GetPot() const;

	Card* GetGlobal() const;

	void SetMaxBet(int _maxbet);
	int GetMaxBet() const;

	vector<Player*> GetPlayers() const;
};

class OnlineTable : public Table {
private:
	vector <OnlinePlayer*> players;
public:
	OnlineTable(int _NoP, int _defaultMoney, vector<OnlinePlayer*> _players);
	OnlineTable() {}

	vector<OnlinePlayer*> GetOnlinePlayers() const;

	string InfoToString(int CurrentPlayer, int played, int* playerBets);
	void StringToInfo(string str, int& CurrentPlayer, int& played, int* playerBets);
};