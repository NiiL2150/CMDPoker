#pragma once
#include "Table.cpp"

void GameSettings(int& NoP, string& name, int& defaultMoney) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 40, 11 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 22; i++)
	{
		cout << char(219);
	}
	pos = { 40, 12 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << char(219) << "Number of players:  " << char(219);
	pos = { 40, 13 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 22; i++)
	{
		cout << char(219);
	}

	pos = { 40, 15 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 38; i++)
	{
		cout << char(219);
	}
	pos = { 40, 16 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << char(219) << "Name (max 16 char):                 " << char(219);
	pos = { 40, 17 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 38; i++)
	{
		cout << char(219);
	}

	pos = { 40, 19 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 27; i++)
	{
		cout << char(219);
	}
	pos = { 40, 20 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << char(219) << "Default money:           " << char(219);
	pos = { 40, 21 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 27; i++)
	{
		cout << char(219);
	}

	pos = { 60, 12 };
	SetConsoleCursorPosition(hConsole, pos);
	cin >> NoP;
	pos = { 61, 16 };
	SetConsoleCursorPosition(hConsole, pos);
	cin >> name;
	pos = { 56, 20 };
	SetConsoleCursorPosition(hConsole, pos);
	cin >> defaultMoney;

	system("cls");
}

void Bet(Table& t, int* playerBets, int bet, int player) {
	t.GetPlayers()[player]->SetMoney(t.GetPlayers()[player]->GetMoney() - bet);
	t.SetPot(t.GetPot() + bet);
	playerBets[player] += bet;
	t.SetMaxBet(playerBets[player]);
}

int GetMaxMoney(Table& t) {
	int maxmoney = INT_MAX;
	for (int i = 0; i < t.GetNoP(); i++)
	{
		if (t.GetPlayers()[i]->GetBet() && t.GetPlayers()[i]->GetMoney() < maxmoney) {
			maxmoney = t.GetPlayers()[i]->GetMoney();
		}
	}
	return maxmoney;
}

bool BetEqual(Table& t, int* playerBets){
	int n = 0;
	for (int i = 0; i < t.GetNoP(); i++)
	{
		if (t.GetPlayers()[i]->GetBet() && playerBets[i] == t.GetMaxBet()) {
			n++;
		}
	}
	return (n == t.GetNoPr());
}

int Score(Table& t, int player) {
	int score = 0;
	if (t.GetPlayers()[player]->GetBet()) {
		vector<Card> cards;
		cards.push_back(t.GetPlayers()[player]->GetHand()[0]);
		cards.push_back(t.GetPlayers()[player]->GetHand()[1]);
		cards.push_back(t.GetGlobal()[0]);
		cards.push_back(t.GetGlobal()[1]);
		cards.push_back(t.GetGlobal()[2]);
		cards.push_back(t.GetGlobal()[3]);
		cards.push_back(t.GetGlobal()[4]);
		sort(cards.begin(), cards.end(), [](Card& left, Card& right) {return (left.GetNumber() < right.GetNumber()); });
		score = cards[6].GetNumber();

		for (int i = 0; i < 6; i++)
		{
			if (cards[i].GetNumber() == cards[i + 1].GetNumber()) {
				score = 13 + cards[i].GetNumber();
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int l = i + 2; l < 7; l++)
			{
				if (cards[i].GetNumber() == cards[i+1].GetNumber() && cards[l].GetNumber() == cards[l].GetNumber()) {
					score = 26 + cards[l].GetNumber();
				}
			}
		}

		for (int i = 0; i < 5; i++)
		{
			if (cards[i].GetNumber() == cards[i + 1].GetNumber() == cards[i + 2].GetNumber()) {
				score = 39 + cards[i].GetNumber();
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int l = i+1; l < 4; l++)
			{
				for (int j = l+1; j < 5; j++)
				{
					for (int z = j+1; z < 6; z++)
					{
						for (int p = z+1; p < 7; p++)
						{
							if (cards[i].GetNumber() == cards[l].GetNumber() - 1 == cards[j].GetNumber() - 2 == cards[z].GetNumber() - 3 == cards[p].GetNumber() - 4) {
								if (52 + cards[p].GetNumber() > score) {
									score = 52 + cards[p].GetNumber();
								}
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int l = i + 1; l < 4; l++)
			{
				for (int j = l + 1; j < 5; j++)
				{
					for (int z = j + 1; z < 6; z++)
					{
						for (int p = z + 1; p < 7; p++)
						{
							if (cards[i].GetSuit() == cards[l].GetSuit() == cards[j].GetSuit() == cards[z].GetSuit() == cards[p].GetSuit()) {
								if (65 + cards[p].GetNumber() > score) {
									score = 65 + cards[p].GetNumber();
								}
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int l = i + 3; l < 6; l++)
			{
				if (cards[i].GetNumber() == cards[i + 1].GetNumber() == cards[i + 2].GetNumber()) {
					if (cards[l].GetNumber() == cards[l + 1].GetNumber()) {
						if (78 + cards[l].GetNumber() > score) {
							score = 78 + cards[l].GetNumber();
						}
					}
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int l = i + 2; l < 5; l++)
			{
				if (cards[l].GetNumber() == cards[l + 1].GetNumber() == cards[l + 2].GetNumber()) {
					if (cards[i].GetNumber() == cards[i + 1].GetNumber()) {
						if (78 + cards[i].GetNumber() > score) {
							score = 78 + cards[i].GetNumber();
						}
					}
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (cards[i].GetNumber() == cards[i + 1].GetNumber() == cards[i + 2].GetNumber() == cards[i + 3].GetNumber()) {
				score = 91 + cards[i].GetNumber();
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int l = i + 1; l < 4; l++)
			{
				for (int j = l + 1; j < 5; j++)
				{
					for (int z = j + 1; z < 6; z++)
					{
						for (int p = z + 1; p < 7; p++)
						{
							if (cards[i].GetSuit() == cards[l].GetSuit() == cards[j].GetSuit() == cards[z].GetSuit() == cards[p].GetSuit()) {
								if (cards[i].GetNumber() == cards[l].GetNumber() - 1 == cards[j].GetNumber() - 2 == cards[z].GetNumber() - 3 == cards[p].GetNumber() - 4) {
									if (104 + cards[p].GetNumber() > score) {
										score = 104 + cards[p].GetNumber();
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return score;
}

void SinglePlayer() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0, 0 };
	SetConsoleCursorPosition(hConsole, pos);
	system("CLS");
	int NoP, defaultMoney, dealer = 0, CurrentPlayer = 0, played = 0;
	string name;
	GameSettings(NoP, name, defaultMoney);
	int* playerBets = new int[NoP];
	Table t = { NoP, defaultMoney, name };
	t.PrintTable();
	while (t.GetNoPa() > 1)
	{
#pragma region Blinds
		t.Refresh();
		for (int i = 0; i < NoP; i++)
		{
			playerBets[i] = 0;
		}
		dealer++;
		if (dealer >= NoP) {
			dealer = 0;
		}
		CurrentPlayer = dealer;
		if (t.GetPlayers()[CurrentPlayer]->GetMoney() < 20) {
			t.GetPlayers()[CurrentPlayer]->SetBet(0);
			t.GetPlayers()[CurrentPlayer]->SetActive(0);
		}
		else {
			Bet(t, playerBets, 20, CurrentPlayer);
		}
		CurrentPlayer += 1;
		if (CurrentPlayer >= NoP) {
			CurrentPlayer = 0;
		}
		if (t.GetPlayers()[CurrentPlayer]->GetMoney() < 40) {
			t.GetPlayers()[CurrentPlayer]->SetBet(0);
			t.GetPlayers()[CurrentPlayer]->SetActive(0);
		}
		else {
			Bet(t, playerBets, 40, CurrentPlayer);
		}
		CurrentPlayer += 1;
		if (CurrentPlayer >= NoP) {
			CurrentPlayer = 0;
		}
		t.PrintCards();
		played = 2;
#pragma endregion
		while (t.GetNoPr() > 1 && t.GetStage()!=5) {
			Sleep(1000);
			played++;
			if (t.GetPlayers()[CurrentPlayer]->GetBet()) {
				int maxmoney = GetMaxMoney(t);
				if (t.GetPlayers()[CurrentPlayer]->GetIsPlayer()) {
					int money = 0;
					short ch = 0;
					bool skip = false;
					do
					{
						FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
						Sleep(50);
						t.PrintControls(ch, money);
						switch (_getch()) {
						case KEY_LEFT:
							ch--;
							if (ch < 1) { ch = 6; }
							break;
						case KEY_RIGHT:
							ch++;
							if (ch > 6) { ch = 1; }
							break;
						case '1':
						case 'q':
						case 'Q':
							ch = 1;
							break;
						case '2':
							ch = 2;
							break;
						case '3':
							ch = 3;
							break;
						case '4':
							ch = 4;
							break;
						case '5':
							ch = 5;
							break;
						case '6':
							ch = 6;
							break;
						case '\r':
							ch = -ch;
							break;
						}
						if (ch == -1) {
							system("cls");
							delete[] playerBets;
							return;
						}
						else if (ch == -2) {
							t.GetPlayers()[CurrentPlayer]->SetBet(0);
							t.SetNoPr(t.GetNoPr() - 1);
							skip = true;
						}
						else if (ch == -3) {
							Bet(t, playerBets, (t.GetMaxBet() - playerBets[CurrentPlayer]), CurrentPlayer);
							skip = true;
						}
						else if (ch == -4) {
							Bet(t, playerBets, (t.GetMaxBet() - playerBets[CurrentPlayer] + money), CurrentPlayer);
							skip = true;
						}
						else if (ch == -5) {
							money -= 10;
							if (money < 0) {
								money = 0;
							}
							ch = 5;
						}
						else if (ch == -6) {
							money += 10;
							if (money > maxmoney + t.GetMaxBet() - playerBets[CurrentPlayer]) {
								money = maxmoney;
							}
							ch = 6;
						}
					} while (skip == false);
					t.DeleteControls();
				}
				else {
					short ch = rand() % 10;
					if (ch == 0) {
						t.GetPlayers()[CurrentPlayer]->SetBet(0);
						t.SetNoPr(t.GetNoPr() - 1);
					}
					else if (ch == 1 && t.GetPlayers()[CurrentPlayer]->GetMoney() >= 10) {
						int randtmp = rand() % 5 + 1;
						if (randtmp * 10 <= t.GetPlayers()[CurrentPlayer]->GetMoney() && randtmp <= maxmoney) {
							Bet(t, playerBets, t.GetMaxBet() - playerBets[CurrentPlayer] + randtmp * 10, CurrentPlayer);
						}
						else {
							Bet(t, playerBets, (t.GetMaxBet() - playerBets[CurrentPlayer]), CurrentPlayer);
						}
					}
					else {
						Bet(t, playerBets, (t.GetMaxBet() - playerBets[CurrentPlayer]), CurrentPlayer);
					}
				}
			}
			CurrentPlayer++;
			t.PrintDetails();
			if (CurrentPlayer >= t.GetNoP()) {
				CurrentPlayer = 0;
			}
			if (BetEqual(t, playerBets) && played >= t.GetNoP()) {
				t.SetStage(t.GetStage() + 1);
				t.PrintCards();
				t.SetMaxBet(0);
				played = 0;
				for (int i = 0; i < NoP; i++)
				{
					playerBets[i] = 0;
				}
			}
		}
		if (t.GetNoPr() == 1) {
			for (int i = 0; i < NoP; i++)
			{
				if (t.GetPlayers()[i]->GetBet()) {
					t.GetPlayers()[i]->SetMoney(t.GetPlayers()[i]->GetMoney() + t.GetPot());
					t.SetPot(0);
				}
			}
		}
		else {
			t.PrintDetails();
			Sleep(1000);
			int* score = new int[NoP];
			for (int i = 0; i < NoP; i++)
			{
				score[i] = 0;
			}
			int maxscore = 0, maxscores = 1;
			for (int i = 0; i < t.GetNoP(); i++)
			{
				int tmpscore = Score(t, i);
				score[i] = tmpscore;
				if (maxscore < score[i]) {
					maxscores = 1;
					maxscore = score[i];
				}
				else if (maxscore == score[i]) {
					maxscores++;
				}
			}
			if (maxscores == 1) {
				for (int i = 0; i < NoP; i++)
				{
					if (score[i] == maxscore) {
						t.GetPlayers()[i]->SetMoney(t.GetPlayers()[i]->GetMoney() + t.GetPot());
						t.SetPot(0);
					}
				}
			}
			else {
				while ((t.GetPot() / 10) % maxscores != 0) {
					t.SetPot(t.GetPot() - 10);
				}
				for (int i = 0; i < t.GetNoP(); i++)
				{
					if (score[i] == maxscore) {
						t.GetPlayers()[i]->SetMoney(t.GetPlayers()[i]->GetMoney() + t.GetPot() / maxscores);
					}
				}
				t.SetPot(0);
			}
			t.PrintDetails();
			Sleep(5000);
		}
	}
	t.DeleteControls();
	t.PrintCards();
	t.PrintDetails();
	pos = { 50, 27 };
	SetConsoleCursorPosition(hConsole, pos);
	if (t.GetPlayers()[0]->GetActive()) {
		cout << "You won!" << endl;
	}
	else {
		cout << "You lost!" << endl;
	}
	Sleep(10000);
}