#include "Menu.h"

int Socket::nofSockets_ = 0;

int main()
{
	SetSettings();
	MenuChoice();
	/*int ch = 0;
	cin >> ch;
	if (ch == 0) {
		int randomnum = rand() % 48127 + 1024;
		SocketServer server(randomnum, 1);
		cout << randomnum;
		Socket* stmp = server.Accept();
		string tmp = stmp->ReceiveLine();
		cout << tmp;
		stmp->SendLine("sample text");
		Sleep(10000);
	}
	else {
		string line, ip, tmp;
		int place, portnum;
		cin >> ip;
		cin >> portnum;
		cin >> line;
		SocketClient s(ip, portnum);
		s.SendLine(line);
		tmp = s.ReceiveLine();
		cout << tmp;
		Sleep(10000);
	}*/
	return 0;
}