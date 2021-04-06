#pragma once
#include "Includes.h"
namespace Cards {
	enum Numbers {
		TWO = 2,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
		ACE,
		TWOch = '2',
		THREEch = '3',
		FOURch = '4',
		FIVEch = '5',
		SIXch = '6',
		SEVENch = '7',
		EIGHTch = '8',
		NINEch = '9',
		TENch = 'T',
		JACKch = 'J',
		QUEENch = 'Q',
		KINGch = 'K',
		ACEch = 'A'
	};
	enum Suits {
		DIAMONDS = 1,
		HEARTS,
		SPADES,
		CLUBS,
		DIAMOND = 'D',
		HEART = 'H',
		SPADE = 'S',
		CLUB = 'C'
	};
};

class Card {
private:
	short Number; //A (in some cases), 2, 3, 4, 5, 6, 7, 8, 9, T(10), J, Q, K, A
	short Suit; //Diamonds, Hearts, Spades, Clubs
public:
	Card(short _Number, short _Suit);
	Card();

	short GetNumber();
	void SetNumber(short _Number);
	short GetSuit();
	void SetSuit(short _Suit);

	char SuitToChar();
	char NumberToChar();

	void PrintEmptyRow(bool show);
	void PrintFilledRow1();
	void PrintFilledRow2();
	void PrintFirstRow(bool show);
	void PrintThirdRow(bool show);
	void PrintFifthRow(bool show);
};

