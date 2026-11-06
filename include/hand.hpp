#pragma once

#include <vector>
#include "card.hpp"

class Hand {
private:
	std::vector<Card> cards;

public:
	Hand() = default;

	void addCard(const Card& card);
	int getValue() const;
	bool isBust() const;
	bool isBlackjack() const;
	bool isSoft() const;
	bool canSplit() const;
	Card split();

	const std::vector<Card>& getCards() const;
};
