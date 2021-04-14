#pragma once
#include "Game.h"
void PrintLogo() {
	cout << RESET << "\t\t   " << BOLDREDB << " ";
	for (int i = 0; i < 80; i++) { cout << char(220); }
	cout << " " << RESET << "\n\t\t   " << BOLDREDB << " " << char(221) <<
		"                                                                               \b" << char(222) << " " << RESET << endl;

	cout << "\t\t   " << BOLDREDB << " " << char(221) << "   ";
	for (int i = 0; i < 13; i++) { cout << char(219); }
	cout << "    ";
	for (int i = 0; i < 12; i++) { cout << char(219); }
	cout << "   " << char(219) << char(219) << "      " << char(219) << char(219) << "  ";
	for (int i = 0; i < 12; i++) { cout << char(219); }
	cout << "   ";
	for (int i = 0; i < 13; i++) { cout << char(219); }
	cout << "    \b" << char(222) << " " << RESET << endl;

	cout << "\t\t   " << BOLDREDB << " " << char(221) << "   ";
	cout << char(219) << char(219) << "          " << char(219) << char(219) << "  ";
	cout << char(219) << char(219) << "          " << char(219) << char(219) << "  ";
	cout << char(219) << char(219) << "    " << char(219) << char(219) << "    " << char(219) << char(219) << "             "
		<< char(219) << char(219) << "          " << char(219) << char(219) << "  " << char(222) << " " << RESET << endl;

	cout << "\t\t   " << BOLDREDB << " " << char(221) << "   ";
	cout << char(219) << char(219) << "          " << char(219) << char(219) << "  ";
	cout << char(219) << char(219) << "          " << char(219) << char(219) << "  ";
	cout << char(219) << char(219) << "  " << char(219) << char(219) << "      " << char(219) << char(219) << "             "
		<< char(219) << char(219) << "          " << char(219) << char(219) << "  " << char(222) << " " << RESET << endl;

	cout << "\t\t   " << BOLDREDB << " " << char(221) << "   ";
	for (int i = 0; i < 13; i++) { cout << char(219); }
	cout << "   ";
	cout << char(219) << char(219) << "          " << char(219) << char(219) << "  ";
	cout << char(219) << char(219) << char(219) << char(219) << "        ";
	for (int i = 0; i < 12; i++) { cout << char(219); }
	cout << "   ";
	for (int i = 0; i < 13; i++) { cout << char(219); }
	cout << "    \b" << char(222) << " " << RESET << endl;

	cout << "\t\t   " << BOLDREDB << " " << char(221) << "   ";
	cout << char(219) << char(219) << "              " << char(219) << char(219) << "          " << char(219) << char(219);
	cout << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "      " << char(219) << char(219) << "             ";
	cout << char(219) << char(219) << " " << char(219) << char(219) << char(219) << "          " << char(222) << " " << RESET << endl;

	cout << "\t\t   " << BOLDREDB << " " << char(221) << "   ";
	cout << char(219) << char(219) << "              " << char(219) << char(219) << "          " << char(219) << char(219);
	cout << "  " << char(219) << char(219) << "    " << char(219) << char(219) << "    " << char(219) << char(219) << "             ";
	cout << char(219) << char(219) << "    " << char(219) << char(219) << char(219) << "       " << char(222) << " " << RESET << endl;

	cout << "\t\t   " << BOLDREDB << " " << char(221) << "   ";
	cout << char(219) << char(219) << "               ";
	for (int i = 0; i < 12; i++) { cout << char(219); }
	cout << "   " << char(219) << char(219) << "      " << char(219) << char(219) << "  ";
	for (int i = 0; i < 12; i++) { cout << char(219); }
	cout << "   " << char(219) << char(219) << "       " << char(219) << char(219) << char(219) << "    " << char(222) << " " << RESET << endl;

	cout << "\t\t   " << BOLDREDB << " " << char(221) <<
		"                                                                               \b" << char(222) << " " << RESET << endl << "\t\t   " << BOLDREDB << " ";
	for (int i = 0; i < 80; i++) { cout << char(223); }
	cout << " " << RESET << endl << endl;
}

void PrintMenuItem(int ch) {
	cout << "\t\t\t\t\t\t" << "   ";
	for (int i = 0; i < 16; i++)
	{
		cout << char(220);
	}
	cout << "   " << endl;
	cout << "\t\t\t\t\t\t" << "  " << char(222) << "                " << char(221) << "  " << endl;

	switch (ch)
	{
	case 1:
		cout << "\t\t\t\t\t\t" << "  " << char(222) << "  SinglePlayer  " << char(221) << "  " << endl;
		break;
	case 2:
		cout << "\t\t\t\t\t\t" << "  " << char(222) << "  MultiPlayer   " << char(221) << "  " << endl;
		break;
	case 3:
		cout << "\t\t\t\t\t\t" << "  " << char(222) << "      Quit      " << char(221) << "  " << endl;
		break;
	}

	cout << "\t\t\t\t\t\t" << "  " << char(222) << "                " << char(221) << "  " << endl;
	cout << "\t\t\t\t\t\t" << "   ";
	for (int i = 0; i < 16; i++)
	{
		cout << char(223);
	}
	cout << "   " << RESET << endl;
}

void PrintMenu(int ch) {
	if (ch == 1) {
		cout << REDB;
	}
	PrintMenuItem(1);
	cout << endl;
	if (ch == 2) {
		cout << REDB;
	}
	PrintMenuItem(2);
	cout << endl;
	if (ch == 3) {
		cout << REDB;
	}
	PrintMenuItem(3);
}

void SetSettings() {
	HWND consoleWindow = GetConsoleWindow();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	COORD coord;
	SMALL_RECT rect;
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	coord.X = 120;
	coord.Y = 30;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = coord.Y - 1;
	rect.Right = coord.X - 1;
	SetConsoleScreenBufferSize(hConsole, coord);
	SetConsoleWindowInfo(hConsole, TRUE, &rect);
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
	srand(time(NULL));
}

void MenuChoice() {
	SetConsoleTitle(_T("CMDPoker - Menu"));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	short ch = 0;
	do
	{
		if (ch == -1) {
			ch = 0;
			SetConsoleTitle(_T("CMDPoker - SinglePlayer"));
			SinglePlayer();
		}
		else if (ch == -2) {
			ch = 0;
			SetConsoleTitle(_T("CMDPoker - MultiPlayer"));
			MultiPlayer();
		}
		if (ch == 0) {
			system("CLS");
			PrintLogo();
			PrintMenu(0);
			SetConsoleTitle(_T("CMDPoker - Menu"));
		}
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		Sleep(50);
		switch (_getch()) {
		case KEY_UP:
			ch--;
			if (ch < 1) { ch = 3; }
			break;
		case KEY_DOWN:
			ch++;
			if (ch > 3) { ch = 1; }
			break;
		case '1':
			ch = 1;
			break;
		case '2':
			ch = 2;
			break;
		case '3':
		case 'q':
		case 'Q':
			ch = 3;
			break;
		case '\r':
			ch = -ch;
			break;
		}
		pos = { 0, 12 };
		SetConsoleCursorPosition(hConsole, pos);
		PrintMenu(ch);
	} while (ch != -3);
}