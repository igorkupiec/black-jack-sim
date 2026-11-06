#pragma once

#include <cstddef>
#include <vector>
#include "hand.hpp"

class Participant {
private:
	int bankroll;
	std::vector<Hand> hands;
	std::vector<int> bets;

public:
	explicit Participant(int initialBankroll = 0);

	void clear();
	bool placeBet(int amount);
	void addWinnings(int amount);
	void addCard(const Card& card, std::size_t handIndex = 0);

	bool canSplit(std::size_t handIndex) const;
	bool executeSplit(std::size_t handIndex);

	int getBankroll() const;
	const Hand& getHand(std::size_t handIndex) const;
	int getBet(std::size_t handIndex) const;
	std::size_t getHandCount() const;
};
