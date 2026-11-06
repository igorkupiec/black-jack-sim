#include "decisionstrategy.hpp"

Action DealerStrategy::getAction(const Hand& hand, const Card& dealerUpCard, bool /*canDouble*/, bool /*canSplit*/){
	if(hand.getValue() < 17)return Action::Hit;
	return Action::Stand;
}

Action BasicStrategy::getAction(const Hand& hand, const Card& dealerUpCard, bool canDouble, bool canSplit){
	int playerTotal = hand.getValue();
	int dealerValue = dealerUpCard.getValue();
	bool soft = hand.isSoft();

	if(canSplit){
		const auto& cards = hand.getCards();
		int pairValue = cards[0].getValue();

		if(pairValue == 11 || pairValue == 8)return Action::Split;
		
		if((pairValue == 2 || pairValue == 3 || pairValue == 7) && dealerValue >= 2) return Action::Split;

		if(pairValue == 6 && dealerValue >= 3 && dealerValue <= 6) return Action::Split;

		if(pairValue == 9 && dealerValue >= 2 && dealerValue <= 9 && dealerValue != 7)	return Action::Split;
	}

	if(soft){
		if(playerTotal >= 19) return Action::Stand;

		if(playerTotal == 18){
			if(canDouble && dealerValue >= 3 && dealerValue <= 6)return Action::DoubleDown;
			if(dealerValue >= 9 || dealerValue ==11) return Action::Hit;
			return Action::Stand;
		}

		if(playerTotal >= 13 && playerTotal <= 17){
			if(canDouble && dealerValue >= 5 && dealerValue <= 6) return Action::DoubleDown;
			return Action::Hit;
		}
	}
	if(playerTotal >= 17) return Action::Stand;
	if(playerTotal >= 13 && playerTotal <= 16){
		if(dealerValue >= 2 && dealerValue <= 6) return Action::Stand;
		return Action::Hit;
	}
	if(playerTotal == 12){
		if(dealerValue >= 4 && dealerValue <= 6) return Action::Stand;
		return Action::Hit;
	}
	if(playerTotal == 11){
		if(canDouble) return Action::DoubleDown;
		return Action::Hit;
	}
	if(playerTotal == 10){
		if(canDouble && dealerValue >= 2 && dealerValue <= 6) return Action::DoubleDown;
		return Action::Hit;
	}
	if(playerTotal == 9){
		if(canDouble && dealerValue >= 3 && dealerValue <= 6)return Action::DoubleDown;
		return Action::Hit;
	}

	return Action::Hit;
}

