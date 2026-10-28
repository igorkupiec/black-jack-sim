
#include "deck.hpp"

Deck::Deck(){
	card.reserve(52);
	
	for(int i = static_cast<int>(Rank::Two); i <= static_cast<int>(Rank::Ace); ++i){
		Rank currRank = static_cast<Rank>(i);
		for(int j = 0; j < 4; ++j){
			cards.emplace_back(currRank);
		}
	}
}

const std::vector<Card>& Deck::getCards() const{
	return cards;
}
