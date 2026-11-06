#pragma once

#include <random>
#include "shoe.hpp"
#include "participant.hpp"
#include "decisionstrategy.hpp"

class GameEngine{
	private:
		std::mt19937 rng;
		Shoe shoe;
		Participant dealer;
		DealerStrategy dealerStrategy;

		void dealInitialCards(Participant& player);
		void handlePlayerTurn(Participant& player, DecisionStrategy& playerStrategy);
		void handleDealerTurn();
		void evaluateAndPay(Participant& player);

	public:
		explicit GameEngine(unsigned int seed = std::random_device{}());
		void playRound(Participant& player, DecisionStrategy& playerStrategy, int betAmount);
		const Shoe& getShoe() const;
		const Participant& getDealer() const;
};
