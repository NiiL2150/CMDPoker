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
	t.SetMaxBet(t.GetMaxBet() + bet);
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

void SinglePlayer() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0, 0 };
	SetConsoleCursorPosition(hConsole, pos);
	system("CLS");
	int NoP, defaultMoney, dealer = 0, CurrentPlayer = 0;
	string name;
	GameSettings(NoP, name, defaultMoney);
	int* playerBets = new int[NoP];
	Table t = { NoP, defaultMoney, name };
	t.PrintTable();
	t.PrintCards();
	while (t.GetNoPa() > 1)
	{
#pragma region Blinds
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
#pragma endregion
		while (t.GetNoPr() > 1 && t.GetStage()!=5) {
			system("cls");
			t.PrintTable();
			t.PrintCards();
			t.PrintDetails();
			if (t.GetPlayers()[CurrentPlayer]->GetBet()) {
				if (t.GetPlayers()[CurrentPlayer]->GetIsPlayer()) {
					int money = 0;
					int maxmoney = t.GetPlayers()[CurrentPlayer]->GetMoney();
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
							Bet(t, playerBets, money, CurrentPlayer);
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
							if (money > maxmoney) {
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
					else {
						Bet(t, playerBets, (t.GetMaxBet() - playerBets[CurrentPlayer]), CurrentPlayer);
					}
					t.DeleteControls();
				}
			}
			CurrentPlayer++;
			if (CurrentPlayer >= NoP) {
				CurrentPlayer = 0;
			}
			if (BetEqual(t, playerBets)) {
				t.SetStage(t.GetStage() + 1);
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
	}
}