#pragma once
#include <vector>
#include <random>
#include "card.hpp"

class Deck{
	private:
		std::vector<Card> cards;

	public:
		Deck();

		const std::vector<Card>&getCards() const;

		void shuffle(std::mt19937& rng);
		
		Card drawCard();

		size_t cardsRemaining() const;
		bool isEmpty() const;
};
