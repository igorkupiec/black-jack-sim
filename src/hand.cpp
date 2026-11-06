#include "hand.hpp"

void Hand::addCard(const Card& card) {
	cards.push_back(card);
}

int Hand::getValue() const {
	int total = 0;
	int aceCount = 0;

	for (const auto& card : cards) {
		int val = card.getValue();
		if (val == 11) {
			aceCount++;
		}
		total += val;
	}

	while (total > 21 && aceCount > 0) {
		total -= 10;
		aceCount--;
	}

	return total;
}

bool Hand::isBust() const {
	return getValue() > 21;
}

bool Hand::isBlackjack() const {
	return cards.size() == 2 && getValue() == 21;
}

bool Hand::isSoft() const {
	int total = 0;
	int aceCount = 0;

	for (const auto& card : cards) {
		int val = card.getValue();
		if (val == 11) {
			aceCount++;
		}
		total += val;
	}

	while (total > 21 && aceCount > 0) {
		total -= 10;
		aceCount--;
	}

	return aceCount > 0;
}

bool Hand::canSplit() const {
	if (cards.size() != 2) {
		return false;
	}
	return cards[0].getValue() == cards[1].getValue();
}

Card Hand::split() {
	Card c = cards.back();
	cards.pop_back();
	return c;
}

const std::vector<Card>& Hand::getCards() const {
	return cards;
}
