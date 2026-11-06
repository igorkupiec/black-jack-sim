#pragma once

#include "hand.hpp"
#include "card.hpp"

enum class Action{
	Hit, Stand, DoubleDown, Split
};

class DecisionStrategy{
	public:
		virtual ~DecisionStrategy() = default;
		virtual Action getAction(const Hand& playerHand, const Card& dealerUpCard, bool canDouble, bool canSplit) = 0;
};

class DealerStrategy : public DecisionStrategy {
	public:
		Action getAction(const Hand& hand, const Card& dealerUpCard, bool canDouble, bool canSplit) override;
};

class BasicStrategy : public DecisionStrategy {
	public:
		Action getAction(const Hand& hand, const Card& dealerUpCard, bool canDouble, bool canSplit) override;
};
