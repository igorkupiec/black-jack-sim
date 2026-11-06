#include <cstddef>
#include "participant.hpp"

Participant::Participant(int initialBankroll) : bankroll(initialBankroll) {
	hands.push_back(Hand());
	bets.push_back(0);
}

void Participant::clear() {
	hands.clear();
	bets.clear();
	hands.push_back(Hand());
	bets.push_back(0);
}

bool Participant::placeBet(int amount) {
	if (bankroll < amount) {
		return false;
	}
	bankroll -= amount;
	bets[0] += amount;
	return true;
}

void Participant::addWinnings(int amount) {
	bankroll += amount;
}

void Participant::addCard(const Card& card, std::size_t handIndex) {
	if (handIndex < hands.size()) {
		hands[handIndex].addCard(card);
	}
}

bool Participant::canSplit(std::size_t handIndex) const {
	if (handIndex >= hands.size()) {
		return false;
	}
	return hands[handIndex].canSplit() && bankroll >= bets[handIndex];
}

bool Participant::executeSplit(std::size_t handIndex) {
	if (!canSplit(handIndex)) {
		return false;
	}

	int currentBet = bets[handIndex];
	bankroll -= currentBet;

	Card secondCard = hands[handIndex].split();

	Hand newHand;
	newHand.addCard(secondCard);

	hands.push_back(newHand);
	bets.push_back(currentBet);

	return true;
}

int Participant::getBankroll() const {
	return bankroll;
}

const Hand& Participant::getHand(std::size_t handIndex) const {
	return hands.at(handIndex);
}

int Participant::getBet(std::size_t handIndex) const {
	if (handIndex < bets.size()) {
		return bets[handIndex];
	}
	return 0;
}

std::size_t Participant::getHandCount() const {
	return hands.size();
}
