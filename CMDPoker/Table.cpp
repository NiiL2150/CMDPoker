#include "Table.h"
inline Table::Table(int _NoP, int _defaultMoney, string name) {
	players.push_back(new Player(name, _defaultMoney, 1));
	for (int i = 1; i < _NoP; i++)
	{
		players.push_back(new Player("Bot" + to_string(i), _defaultMoney, 0));
	}
	NoP = _NoP;
	NoPr = NoP;
	NoPa = NoP;
	pot = 0;
	maxbet = 0;
	dealer = 0;
	stage = 1;
	deck = new Card[52];
	global = new Card[5];
	StandardDeck();
	Shuffle();
	CardsInGame = 0;
	for (int i = 0; i < 5; i++)
	{
		global[i] = deck[51 - CardsInGame];
		CardsInGame+=1;
	}
	for (int i = 0; i < NoP; i++)
	{
		Card tmpdeck[2] = { deck[51 - CardsInGame], deck[51 - CardsInGame - 1] };
		CardsInGame += 2;
		players[i]->SetHand(tmpdeck);
	}
}

inline void Table::Refresh() {
	pot = 0;
	maxbet = 0;
	dealer++;
	stage = 1;
	NoPr = NoPa;
	StandardDeck();
	Shuffle();
	CardsInGame = 0;
	for (int i = 0; i < 5; i++)
	{
		global[i] = deck[51 - CardsInGame];
		CardsInGame += 1;
	}
	for (int i = 0; i < NoP; i++)
	{
		Card tmpdeck[2] = { deck[51 - CardsInGame], deck[51 - CardsInGame - 1] };
		CardsInGame += 2;
		players[i]->SetHand(tmpdeck);
		if (players[i]->GetActive()) {
			players[i]->SetBet(1);
		}
	}
}

inline void Table::StandardDeck() {
	for (short i = 0; i < 4; i++)
	{
		for (short l = 0; l < 13; l++)
		{
			deck[i * 13 + l] = { l + 2, i + 1 };
		}
	}
}

inline void Table::Shuffle() {
	for (int i = 0; i < 52; i++)
	{
		for (int l = 0; l < 51; l++)
		{
			if (rand() % 100 < 90) {
				Card tmp = deck[l];
				deck[l] = deck[l + 1];
				deck[l + 1] = tmp;
			}
		}
	}
}

inline void Table::PrintTable() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 24, 7 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << MAGENTA;
	for (int i = 0; i < 72; i++)
	{
		cout << char(219);
	}

	pos = { 20, 8 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 8; i++)
	{
		cout << char(219);
	}
	cout << GREEN;
	for (int i = 0; i < 64; i++)
	{
		cout << char(219);
	}
	cout << MAGENTA;
	for (int i = 0; i < 8; i++)
	{
		cout << char(219);
	}

	for (short i = 0; i < 7; i++)
	{
		pos = { 19, 9+i };
		SetConsoleCursorPosition(hConsole, pos);
		cout << char(219) << char(219) << GREEN;
		for (int i = 0; i < 78; i++)
		{
			cout << char(219);
		}
		cout << MAGENTA << char(219) << char(219);
	}

	pos = { 20, 16 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 8; i++)
	{
		cout << char(219);
	}
	cout << GREEN;
	for (int i = 0; i < 64; i++)
	{
		cout << char(219);
	}
	cout << MAGENTA;
	for (int i = 0; i < 8; i++)
	{
		cout << char(219);
	}

	pos = { 24, 17 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << MAGENTA;
	for (int i = 0; i < 72; i++)
	{
		cout << char(219);
	}
	cout << RESET;
}

inline void Table::PrintCards() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	int a;
	if (stage <= 1) {
		a = 0;
	}
	else {
		a = 1;
	}
	pos = { 28 + 1 * 6, 10 };
	SetConsoleCursorPosition(hConsole, pos);
	global[0].PrintFirstRow(a);
	pos = { 28 + 1 * 6, 11 };
	SetConsoleCursorPosition(hConsole, pos);
	global[0].PrintEmptyRow(a);
	pos = { 28 + 1 * 6, 12 };
	SetConsoleCursorPosition(hConsole, pos);
	global[0].PrintThirdRow(a);
	pos = { 28 + 1 * 6, 13 };
	SetConsoleCursorPosition(hConsole, pos);
	global[0].PrintEmptyRow(a);
	pos = { 28 + 1 * 6, 14 };
	SetConsoleCursorPosition(hConsole, pos);
	global[0].PrintFifthRow(a);

	pos = { 34 + 2 * 6, 10 };
	SetConsoleCursorPosition(hConsole, pos);
	global[1].PrintFirstRow(a);
	pos = { 34 + 2 * 6, 11 };
	SetConsoleCursorPosition(hConsole, pos);
	global[1].PrintEmptyRow(a);
	pos = { 34 + 2 * 6, 12 };
	SetConsoleCursorPosition(hConsole, pos);
	global[1].PrintThirdRow(a);
	pos = { 34 + 2 * 6, 13 };
	SetConsoleCursorPosition(hConsole, pos);
	global[1].PrintEmptyRow(a);
	pos = { 34 + 2 * 6, 14 };
	SetConsoleCursorPosition(hConsole, pos);
	global[1].PrintFifthRow(a);

	pos = { 40 + 3 * 6, 10 };
	SetConsoleCursorPosition(hConsole, pos);
	global[2].PrintFirstRow(a);
	pos = { 40 + 3 * 6, 11 };
	SetConsoleCursorPosition(hConsole, pos);
	global[2].PrintEmptyRow(a);
	pos = { 40 + 3 * 6, 12 };
	SetConsoleCursorPosition(hConsole, pos);
	global[2].PrintThirdRow(a);
	pos = { 40 + 3 * 6, 13 };
	SetConsoleCursorPosition(hConsole, pos);
	global[2].PrintEmptyRow(a);
	pos = { 40 + 3 * 6, 14 };
	SetConsoleCursorPosition(hConsole, pos);
	global[2].PrintFifthRow(a);

	if (stage <= 2) {
		a = 0;
	}
	else {
		a = 1;
	}
	pos = { 46 + 4 * 6, 10 };
	SetConsoleCursorPosition(hConsole, pos);
	global[3].PrintFirstRow(a);
	pos = { 46 + 4 * 6, 11 };
	SetConsoleCursorPosition(hConsole, pos);
	global[3].PrintEmptyRow(a);
	pos = { 46 + 4 * 6, 12 };
	SetConsoleCursorPosition(hConsole, pos);
	global[3].PrintThirdRow(a);
	pos = { 46 + 4 * 6, 13 };
	SetConsoleCursorPosition(hConsole, pos);
	global[3].PrintEmptyRow(a);
	pos = { 46 + 4 * 6, 14 };
	SetConsoleCursorPosition(hConsole, pos);
	global[3].PrintFifthRow(a);

	if (stage <= 3) {
		a = 0;
	}
	else {
		a = 1;
	}
	pos = { 52 + 5 * 6, 10 };
	SetConsoleCursorPosition(hConsole, pos);
	global[4].PrintFirstRow(a);
	pos = { 52 + 5 * 6, 11 };
	SetConsoleCursorPosition(hConsole, pos);
	global[4].PrintEmptyRow(a);
	pos = { 52 + 5 * 6, 12 };
	SetConsoleCursorPosition(hConsole, pos);
	global[4].PrintThirdRow(a);
	pos = { 52 + 5 * 6, 13 };
	SetConsoleCursorPosition(hConsole, pos);
	global[4].PrintEmptyRow(a);
	pos = { 52 + 5 * 6, 14 };
	SetConsoleCursorPosition(hConsole, pos);
	global[4].PrintFifthRow(a);
}

inline void Table::PrintDetails() {
	int pl = 0, ch = 1;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {70 , 18};
	SetConsoleCursorPosition(hConsole, pos);
	cout << players[pl]->GetName();
	pos = { 70, 19 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "          ";
	pos = { 70, 19 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << players[pl]->GetMoney();
	pos = { 68, 20 };
	SetConsoleCursorPosition(hConsole, pos);
	if (players[pl]->GetBet()) {
		players[pl]->GetHand()[0].PrintFirstRow(ch);
		cout << " ";
		players[pl]->GetHand()[1].PrintFirstRow(ch);
		pos = { 68, 21 };
		SetConsoleCursorPosition(hConsole, pos);
		players[pl]->GetHand()[0].PrintEmptyRow(ch);
		cout << " ";
		players[pl]->GetHand()[1].PrintEmptyRow(ch);
		pos = { 68, 22 };
		SetConsoleCursorPosition(hConsole, pos);
		players[pl]->GetHand()[0].PrintThirdRow(ch);
		cout << " ";
		players[pl]->GetHand()[1].PrintThirdRow(ch);
		pos = { 68, 23 };
		SetConsoleCursorPosition(hConsole, pos);
		players[pl]->GetHand()[0].PrintEmptyRow(ch);
		cout << " ";
		players[pl]->GetHand()[1].PrintEmptyRow(ch);
		pos = { 68, 24 };
		SetConsoleCursorPosition(hConsole, pos);
		players[pl]->GetHand()[0].PrintFifthRow(ch);
		cout << " ";
		players[pl]->GetHand()[1].PrintFifthRow(ch);
	}
	else if (players[pl]->GetActive()) {
		cout << "Folded     ";
		pos = { 68, 21 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "           ";
		pos = { 68, 22 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "           ";
		pos = { 68, 23 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "           ";
		pos = { 68, 24 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "           ";
	}
	else {
		cout << "Lost       ";
		pos = { 68, 21 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "           ";
		pos = { 68, 22 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "           ";
		pos = { 68, 23 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "           ";
		pos = { 68, 24 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "           ";
	}

	if (NoP >= 2) {
		pl = 1;
		if (stage == 5) {
			ch = 1;
		}
		else {
			ch = 0;
		}
		pos = { 40 , 18 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << players[pl]->GetName();
		pos = { 40, 19 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "          ";
		pos = { 40, 19 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << players[pl]->GetMoney();
		pos = { 38, 20 };
		SetConsoleCursorPosition(hConsole, pos);
		if (players[pl]->GetBet()) {
			players[pl]->GetHand()[0].PrintFirstRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintFirstRow(ch);
			pos = { 38, 21 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintEmptyRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintEmptyRow(ch);
			pos = { 38, 22 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintThirdRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintThirdRow(ch);
			pos = { 38, 23 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintEmptyRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintEmptyRow(ch);
			pos = { 38, 24 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintFifthRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintFifthRow(ch);
		}
		else if (players[pl]->GetActive()) {
			cout << "Folded     ";
			pos = { 38, 21 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 22 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 23 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 24 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
		}
		else {
			cout << "Lost       ";
			pos = { 38, 21 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 22 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 23 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 24 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
		}
	}

	if (NoP >= 3) {
		pl = 2;
		if (stage == 5) {
			ch = 1;
		}
		else {
			ch = 0;
		}
		pos = { 6 , 8 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << players[pl]->GetName();
		pos = { 6, 9 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "          ";
		pos = { 6, 9 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << players[pl]->GetMoney();
		pos = { 4, 10 };
		SetConsoleCursorPosition(hConsole, pos);
		if (players[pl]->GetBet()) {
			players[pl]->GetHand()[0].PrintFirstRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintFirstRow(ch);
			pos = { 4, 11 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintEmptyRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintEmptyRow(ch);
			pos = { 4, 12 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintThirdRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintThirdRow(ch);
			pos = { 4, 13 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintEmptyRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintEmptyRow(ch);
			pos = { 4, 14 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintFifthRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintFifthRow(ch);
		}
		else if (players[pl]->GetActive()) {
			cout << "Folded     ";
			pos = { 4, 11 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 4, 12 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 4, 13 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 4, 14 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
		}
		else {
			cout << "Lost       ";
			pos = { 4, 11 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 4, 12 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 4, 13 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 4, 14 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
		}
	}

	if (NoP >= 4) {
		pl = 3;
		if (stage == 5) {
			ch = 1;
		}
		else {
			ch = 0;
		}
		pos = { 40 , 0 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << players[pl]->GetName();
		pos = { 40, 1 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "          ";
		pos = { 40, 1 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << players[pl]->GetMoney();
		pos = { 38, 2 };
		SetConsoleCursorPosition(hConsole, pos);
		if (players[pl]->GetBet()) {
			players[pl]->GetHand()[0].PrintFirstRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintFirstRow(ch);
			pos = { 38, 3 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintEmptyRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintEmptyRow(ch);
			pos = { 38, 4 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintThirdRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintThirdRow(ch);
			pos = { 38, 5 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintEmptyRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintEmptyRow(ch);
			pos = { 38, 6 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintFifthRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintFifthRow(ch);
		}
		else if (players[pl]->GetActive()) {
			cout << "Folded     ";
			pos = { 38, 3 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 4 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 5 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 6 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
		}
		else {
			cout << "Lost       ";
			pos = { 38, 3 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 4 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 5 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 38, 6 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
		}
	}

	if (NoP >= 5) {
		pl = 4;
		if (stage == 5) {
			ch = 1;
		}
		else {
			ch = 0;
		}
		pos = { 70 , 0 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << players[pl]->GetName();
		pos = { 70, 1 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "          ";
		pos = { 70, 1 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << players[pl]->GetMoney();
		pos = { 68, 2 };
		SetConsoleCursorPosition(hConsole, pos);
		if (players[pl]->GetBet()) {
			players[pl]->GetHand()[0].PrintFirstRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintFirstRow(ch);
			pos = { 68, 3 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintEmptyRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintEmptyRow(ch);
			pos = { 68, 4 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintThirdRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintThirdRow(ch);
			pos = { 68, 5 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintEmptyRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintEmptyRow(ch);
			pos = { 68, 6 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintFifthRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintFifthRow(ch);
		}
		else if (players[pl]->GetActive()) {
			cout << "Folded     ";
			pos = { 68, 3 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 68, 4 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 68, 5 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 68, 6 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
		}
		else {
			cout << "Lost       ";
			pos = { 68, 3 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 68, 4 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 68, 5 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 68, 6 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
		}
	}

	if (NoP >= 6) {
		pl = 5;
		if (stage == 5) {
			ch = 1;
		}
		else {
			ch = 0;
		}
		pos = { 106 , 8 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << players[pl]->GetName();
		pos = { 106, 9 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << "          ";
		pos = { 106, 9 };
		SetConsoleCursorPosition(hConsole, pos);
		cout << players[pl]->GetMoney();
		pos = { 104, 10 };
		SetConsoleCursorPosition(hConsole, pos);
		if (players[pl]->GetBet()) {
			players[pl]->GetHand()[0].PrintFirstRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintFirstRow(ch);
			pos = { 104, 11 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintEmptyRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintEmptyRow(ch);
			pos = { 104, 12 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintThirdRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintThirdRow(ch);
			pos = { 104, 13 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintEmptyRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintEmptyRow(ch);
			pos = { 104, 14 };
			SetConsoleCursorPosition(hConsole, pos);
			players[pl]->GetHand()[0].PrintFifthRow(ch);
			cout << " ";
			players[pl]->GetHand()[1].PrintFifthRow(ch);
		}
		else if (players[pl]->GetActive()) {
			cout << "Folded     ";
			pos = { 104, 11 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 104, 12 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 104, 13 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 104, 14 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
		}
		else {
			cout << "Lost       ";
			pos = { 104, 11 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 104, 12 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 104, 13 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
			pos = { 104, 14 };
			SetConsoleCursorPosition(hConsole, pos);
			cout << "           ";
		}
	}
	pos = { 58, 9 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << GREENB << "              " << RESET;
	pos = { 58, 9 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << GREENB << BLACK << pot << "$" << RESET;
}

inline void Table::PrintControls(short ch, int maxmoney)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 5, 26 };
	SetConsoleCursorPosition(hConsole, pos);
	if (ch == 1) {
		cout << REDB;
	}
	cout << "      ";
	pos = { 5, 27 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << " QUIT ";
	pos = { 5, 28 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "      " << RESET;
	
	if (ch == 2) {
		cout << REDB;
	}
	pos = { 12, 26 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "      ";
	pos = { 12, 27 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << " FOLD ";
	pos = { 12, 28 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "      " << RESET;

	if (ch == 3) {
		cout << REDB;
	}
	pos = { 19, 26 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "            ";
	pos = { 19, 27 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << " CHECK/CALL ";
	pos = { 19, 28 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "            " << RESET;

	if (ch == 4) {
		cout << REDB;
	}
	pos = { 32, 26 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "       ";
	pos = { 32, 27 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << " RAISE ";
	pos = { 32, 28 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "       " << RESET;

	if (ch == 5) {
		cout << REDB;
	}
	pos = { 40, 26 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "   ";
	pos = { 40, 27 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << " < ";
	pos = { 40, 28 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "   " << RESET;

	if (ch == 6) {
		cout << REDB;
	}
	pos = { 44, 26 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "   ";
	pos = { 44, 27 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << " > ";
	pos = { 44, 28 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "   " << RESET;

	pos = { 48, 27 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << "                         ";
	pos = { 48, 27 };
	SetConsoleCursorPosition(hConsole, pos);
	cout << GREENB << BLACK << maxmoney << "$" << RESET;
}

inline void Table::DeleteControls()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0, 26 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 120; i++)
	{
		cout << " ";
	}
	pos = { 0, 27 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 120; i++)
	{
		cout << " ";
	}
	pos = { 0, 28 };
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 120; i++)
	{
		cout << " ";
	}
}

inline void Table::SetStage(int _stage) {
	stage = _stage;
}
inline int Table::GetStage() const {
	return stage;
}

inline void Table::SetNoP(int _NoP) {
	NoP = _NoP;
}
inline int Table::GetNoP() const {
	return NoP;
}

inline void Table::SetNoPr(int _NoPr) {
	NoPr = _NoPr;
}
inline int Table::GetNoPr() const {
	return NoPr;
}

inline void Table::SetNoPa(int _NoPa) {
	NoPa = _NoPa;
}
inline int Table::GetNoPa() const {
	return NoPa;
}

inline void Table::SetPot(int _pot) {
	pot = _pot;
}
inline int Table::GetPot() const {
	return pot;
}

inline Card* Table::GetGlobal() const
{
	return global;
}

inline void Table::SetMaxBet(int _maxbet)
{
	maxbet = _maxbet;
}

inline int Table::GetMaxBet() const
{
	return maxbet;
}

inline vector<Player*> Table::GetPlayers() const
{
	return players;
}

inline OnlineTable::OnlineTable(int _NoP, int _defaultMoney, vector<OnlinePlayer*> _players) {
	players = _players;
	NoP = _NoP;
	NoPr = NoP;
	NoPa = NoP;
	pot = 0;
	maxbet = 0;
	dealer = 0;
	stage = 1;
	deck = new Card[52];
	global = new Card[5];
	StandardDeck();
	Shuffle();
	CardsInGame = 0;
	for (int i = 0; i < 5; i++)
	{
		global[i] = deck[51 - CardsInGame];
		CardsInGame += 1;
	}
	for (int i = 0; i < NoP; i++)
	{
		Card tmpdeck[2] = { deck[51 - CardsInGame], deck[51 - CardsInGame - 1] };
		CardsInGame += 2;
		players[i]->SetHand(tmpdeck);
	}
}

inline vector<OnlinePlayer*> OnlineTable::GetOnlinePlayers() const {
	return players;
}

inline string OnlineTable::InfoToString(int _CurrentPlayer, int _played, int* _playerBets)
{
	string tmp = "";
	tmp += char(NoP);
	tmp += char(NoPr);
	tmp += char(NoPa);
	tmp += pot;
	tmp += "-";
	tmp += maxbet;
	tmp += "-";
	tmp += char(dealer);
	tmp += char(stage);
	tmp += char(deck[0].GetNumber());
	tmp += char(deck[0].GetSuit());
	tmp += char(deck[1].GetNumber());
	tmp += char(deck[1].GetSuit());
	tmp += char(deck[2].GetNumber());
	tmp += char(deck[2].GetSuit());
	tmp += char(deck[3].GetNumber());
	tmp += char(deck[3].GetSuit());
	tmp += char(deck[4].GetNumber());
	tmp += char(deck[4].GetSuit());
	for (int i = 0; i < NoP; i++)
	{
		tmp += char(players[i]->GetHand()[0].GetNumber());
		tmp += char(players[i]->GetHand()[0].GetSuit());
		tmp += char(players[i]->GetHand()[1].GetNumber());
		tmp += char(players[i]->GetHand()[1].GetSuit());
		tmp += players[i]->GetMoney();
		tmp += "-";
		tmp += char(players[i]->GetBet());
		tmp += char(players[i]->GetActive());
		tmp += players[i]->GetName();
		tmp += "-";
		tmp += players[i]->GetIP();
		tmp += "-";
	}
	tmp += char(_CurrentPlayer);
	tmp += char(_played);
	for (int i = 0; i < NoP; i++)
	{
		tmp += _playerBets[i];
		tmp += "-";
	}
	return tmp;
}

inline void OnlineTable::StringToInfo(string str, int& _CurrentPlayer, int& _played, int* _playerBets)
{
	string tmp = "";
	int pos = 0;
	
	NoP = str[pos++];
	NoPr = str[pos++];
	NoPa = str[pos++];

	while (str[pos] != '-') {
		tmp += str[pos++];
	}
	pot = atoi(tmp.c_str());
	tmp = "";
	pos++;

	while (str[pos] != '-') {
		tmp += str[pos++];
	}
	maxbet = atoi(tmp.c_str());
	tmp = "";
	pos++;

	while (str[pos] != '-') {
		tmp += str[pos++];
	}
	pot = atoi(tmp.c_str());
	tmp = "";
	pos++;

	dealer = str[pos++];
	stage = str[pos++];

	deck[0].SetNumber(str[pos++]);
	deck[0].SetSuit(str[pos++]);
	deck[1].SetNumber(str[pos++]);
	deck[1].SetSuit(str[pos++]);
	deck[2].SetNumber(str[pos++]);
	deck[2].SetSuit(str[pos++]);
	deck[3].SetNumber(str[pos++]);
	deck[3].SetSuit(str[pos++]);
	deck[4].SetNumber(str[pos++]);
	deck[4].SetSuit(str[pos++]);

	for (int i = 0; i < NoP; i++)
	{
		players[i]->GetHand()[0].SetNumber(str[pos++]);
		players[i]->GetHand()[0].SetSuit(str[pos++]);
		players[i]->GetHand()[1].SetNumber(str[pos++]);
		players[i]->GetHand()[1].SetSuit(str[pos++]);

		while (str[pos] != '-') {
			tmp += str[pos++];
		}
		players[i]->SetMoney(atoi(tmp.c_str()));
		tmp = "";
		pos++;

		players[i]->SetBet(str[pos++]);
		players[i]->SetActive(str[pos++]);

		while (str[pos] != '-') {
			tmp += str[pos++];
		}
		players[i]->SetName(tmp.c_str());
		tmp = "";
		pos++;

		while (str[pos] != '-') {
			tmp += str[pos++];
		}
		players[i]->SetIP(tmp.c_str());
		tmp = "";
		pos++;
	}

	_CurrentPlayer = str[pos++];
	_played = str[pos++];

	for (int i = 0; i < NoP; i++)
	{
		while (str[pos] != '-') {
			tmp += str[pos++];
		}
		_playerBets[i] = atoi(tmp.c_str());
		tmp = "";
		pos++;
	}
}