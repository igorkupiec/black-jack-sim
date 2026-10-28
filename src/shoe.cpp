#include "shoe.hpp"
#include <algorithm>

Shoe::Shoe(int numDecks) : numDecks(numDecks){
	cards.reserve(52 * numDecks);
}

void Shoe::resetAndShuffle(std::mt19937& rng){
	cards.clear();
	runningCount = 0;
	Deck singleDeck;
	for(int i = 0; i < numDecks; ++i){
		const auto& deckCards = singleDeck.getCards();
		cards.insert(cards.end(), deckCards.begin(), deckCards.end());
	}
	std::shuffle(cards.begin(), cards.end(), rng);

	std::uniform_int_distribution<std::size_t> dist(static_cast<std::size_t>(cards.size() * 0.4), static_cast<std::size_t>(cards.size() * 0.5));
	cutPosition = dist(rng);
}

Card Shoe::drawCard() {
	Card drawn = cards.back();
	cards.pop_back();

	updateCount(drawn);
	
	return drawn;
}

bool Shoe::needsReshuffle() const {
	return cards.size() <= cutPosition;
}

void Shoe::updateCount(const Card& card){
	int val = card.getValue();
	if(val >= 2 && val <= 6){
		runningCount++;
	}
	else if(val == 10 || val == 11){
		runningCount--;
	}
}

int Shoe::getRunningCount() const{
	return runningCount;
}

float Shoe::getTrueCount() const{
	float decksRemaining = static_cast<float>(cards.size()) / 52.;
	if(decksRemaining < 0.5) decksRemaining = 0.5;
	return static_cast<float>(runningCount)/decksRemaining;
}

std::size_t Shoe::cardsRemaining() const{
	return cards.size();
}
