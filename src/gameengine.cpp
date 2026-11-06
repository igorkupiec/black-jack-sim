#include "gameengine.hpp"

GameEngine::GameEngine(unsigned int seed) : rng(seed), shoe(8) {
	shoe.resetAndShuffle(rng);
}

void GameEngine::playRound(Participant& player, DecisionStrategy& playerStrategy, int betAmount) {
	if (shoe.needsReshuffle()) {
		shoe.resetAndShuffle(rng);
	}

	player.clear();
	dealer.clear();

	if (!player.placeBet(betAmount)) {
		return;
	}

	dealInitialCards(player);

	bool playerBJ = player.getHand(0).isBlackjack();
	bool dealerBJ = dealer.getHand(0).isBlackjack();

	if (playerBJ || dealerBJ) {
		if (playerBJ && !dealerBJ) {
			int totalPayout = static_cast<int>(player.getBet(0) * 2.5);
			player.addWinnings(totalPayout);
		} else if (playerBJ && dealerBJ) {
			player.addWinnings(player.getBet(0));
		}
		return;
	}

	handlePlayerTurn(player, playerStrategy);

	bool hasActiveHand = false;
	for (std::size_t i = 0; i < player.getHandCount(); ++i) {
		if (!player.getHand(i).isBust()) {
			hasActiveHand = true;
			break;
		}
	}

	if (hasActiveHand) {
		handleDealerTurn();
	}

	evaluateAndPay(player);
}

void GameEngine::dealInitialCards(Participant& player) {
	player.addCard(shoe.drawCard(), 0);
	dealer.addCard(shoe.drawCard(), 0);
	player.addCard(shoe.drawCard(), 0);
	dealer.addCard(shoe.drawCard(), 0);
}

void GameEngine::handlePlayerTurn(Participant& player, DecisionStrategy& playerStrategy) {
	Card dealerUpCard = dealer.getHand(0).getCards()[0];

	for (std::size_t i = 0; i < player.getHandCount(); ++i) {
		bool turnOver = false;

		while (!turnOver && !player.getHand(i).isBust()) {
			bool canDouble = (player.getHand(i).getCards().size() == 2) &&
			                 (player.getBankroll() >= player.getBet(i));
			bool canSplit = (player.getHandCount() == 1) && player.canSplit(i);

			Action action = playerStrategy.getAction(player.getHand(i), dealerUpCard, canDouble, canSplit);

			switch (action) {
				case Action::Hit:
					player.addCard(shoe.drawCard(), i);
					break;

				case Action::Stand:
					turnOver = true;
					break;

				case Action::DoubleDown:
					player.placeBet(player.getBet(i));
					player.addCard(shoe.drawCard(), i);
					turnOver = true;
					break;

				case Action::Split:
					if (player.executeSplit(i)) {
						player.addCard(shoe.drawCard(), i);
						player.addCard(shoe.drawCard(), player.getHandCount() - 1);
					}
					break;
			}
		}
	}
}

void GameEngine::handleDealerTurn() {
	Card dummyCard(Rank::Two);
	while (dealerStrategy.getAction(dealer.getHand(0), dummyCard, false, false) == Action::Hit) {
		dealer.addCard(shoe.drawCard(), 0);
	}
}

void GameEngine::evaluateAndPay(Participant& player) {
	int dealerTotal = dealer.getHand(0).getValue();
	bool dealerBust = dealer.getHand(0).isBust();

	for (std::size_t i = 0; i < player.getHandCount(); ++i) {
		const Hand& hand = player.getHand(i);
		int bet = player.getBet(i);

		if (hand.isBust()) {
			continue;
		}

		int playerTotal = hand.getValue();

		if (dealerBust || playerTotal > dealerTotal) {
			player.addWinnings(bet * 2);
		} else if (playerTotal == dealerTotal) {
			player.addWinnings(bet);
		}
	}
}

const Shoe& GameEngine::getShoe() const {
	return shoe;
}

const Participant& GameEngine::getDealer() const {
	return dealer;
}
