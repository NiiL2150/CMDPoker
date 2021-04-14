#include "Player.h"

inline Player::Player(string _name, int _money, int _isPlayer) : hand(new Card[2]), name(_name), money(_money), bet(true), active(true), isPlayer(_isPlayer)
{
	hand[0] = Card();
	hand[1] = Card();
}

inline Card* Player::GetHand() const { return hand; }
inline void Player::SetHand(Card* _deck) { hand[0] = _deck[0]; hand[1] = _deck[1]; }

inline string Player::GetName() const { return name; }
inline void Player::SetName(string _name) { name = _name; }

inline int Player::GetMoney() const { return money; }
inline void Player::SetMoney(int _money) { money = _money; }

inline bool Player::GetBet() const { return bet; }
inline void Player::SetBet(bool _bet) { bet = _bet; }

inline bool Player::GetActive() const { return active; }
inline void Player::SetActive(bool _active) { active = _active; }

inline bool Player::GetIsPlayer() const { return isPlayer; }
inline void Player::SetIsPlayer(bool _isPlayer) { isPlayer = _isPlayer; }

inline OnlinePlayer::OnlinePlayer(string _name, int _money, string _ip) : Player(_name, _money, 1), ip(_ip) {}

inline string OnlinePlayer::GetIP() const { return ip; }
inline void OnlinePlayer::SetIP(string _ip) { ip = _ip; }