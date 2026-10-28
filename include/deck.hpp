#pragma once
#include <vector>
#include <random>
#include "card.hpp"

class Deck{
	private:
		std::vector<Card> cards;

	public:
		Deck();

		void shuffle(std::mt19937& rng);
		
		Card drawCard();

		std::size_t cardsRemaining() const;
		bool isEmpty() const;
}
