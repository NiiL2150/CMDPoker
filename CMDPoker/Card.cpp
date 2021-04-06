#include "Card.h"

using namespace std;
using namespace Cards;

inline Card::Card(short _Number, short _Suit) 
{
	Number = _Number;
	Suit = _Suit;
}
inline Card::Card() 
{
	Number = rand() % KING + TWO;
	Suit = rand() % CLUBS + DIAMONDS;
}
inline short Card::GetNumber() { return Number; }
inline void Card::SetNumber(short _Number) { Number = _Number; }
inline short Card::GetSuit() { return Suit; }
inline void Card::SetSuit(short _Suit) { Suit = _Suit; }

inline char Card::SuitToChar() {
	switch (Suit)
	{
	case DIAMONDS:
		return DIAMOND;
		break;
	case HEARTS:
		return HEART;
		break;
	case SPADES:
		return SPADE;
		break;
	case CLUBS:
		return CLUB;
		break;
	}
}
inline char Card::NumberToChar() {
	switch (Number)
	{
	case TWO:
		return TWOch;
		break;
	case THREE:
		return THREEch;
		break;
	case FOUR:
		return FOURch;
		break;
	case FIVE:
		return FIVEch;
		break;
	case SIX:
		return SIXch;
		break;
	case SEVEN:
		return SEVENch;
		break;
	case EIGHT:
		return EIGHTch;
		break;
	case NINE:
		return NINEch;
		break;
	case TEN:
		return TENch;
		break;
	case JACK:
		return JACKch;
		break;
	case QUEEN:
		return QUEENch;
		break;
	case KING:
		return KINGch;
		break;
	case ACE:
		return ACEch;
		break;
	}
}

inline void Card::PrintEmptyRow(bool show) {
	if (!show) {
		PrintFilledRow2();
		return;
	}
	cout << WHITEB << "     " << RESET;
}
inline void Card::PrintFilledRow1() {
	cout << WHITEB << "     " << RESET;
}
inline void Card::PrintFilledRow2() {
	cout << WHITEB << " " << REDB << char(177) << char(177) << char(177) << WHITEB << " " << RESET;
}
inline void Card::PrintFirstRow(bool show) {
	if (!show) {
		PrintFilledRow1();
		return;
	}
	cout << WHITEB;
	if (Suit == DIAMONDS || Suit == HEARTS) { cout << BOLDRED; }
	else { cout << BLACK; }
	cout << NumberToChar() << "    " << RESET;
}
inline void Card::PrintThirdRow(bool show) {
	if (!show) {
		PrintFilledRow2();
		return;
	}
	cout << WHITEB << "  ";
	if (Suit == DIAMONDS || Suit == HEARTS) { cout << BOLDRED; }
	else { cout << BLACK; }
	wcout << char(SuitToChar()) << "  " << RESET;
}
inline void Card::PrintFifthRow(bool show) {
	if (!show) {
		PrintFilledRow1();
		return;
	}
	cout << WHITEB << "    ";
	if (Suit == DIAMONDS || Suit == HEARTS) { cout << BOLDRED; }
	else { cout << BLACK; }
	cout << NumberToChar() << RESET;
}