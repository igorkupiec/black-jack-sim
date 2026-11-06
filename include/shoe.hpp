#pragma once
#include <cstddef>
#include <vector>
#include <random>
#include "card.hpp"
#include "deck.hpp"
class Shoe{
	private:
		int numDecks;
		std::vector<Card> cards;
		std::size_t cutPosition{0};
		int runningCount{0};

		void updateCount(const Card& card);

	public:
		explicit Shoe(int numDecks = 8);
		void resetAndShuffle(std::mt19937& rng);
		Card drawCard();
		bool needsReshuffle() 		const;
		int getRunningCount() 		const;
		float getTrueCount() 		const;
		std::size_t cardsRemaining() 	const;

};
