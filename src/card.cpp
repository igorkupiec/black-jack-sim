include "card.hpp"

Card::Card(Rank rank) : rank(rank){}

Rank Card::getRank() const{
	return rank;
}

int Card::getValue(){
	switch(rank){
		case Rank::Two: 	return 2;
		case Rank::Three: 	return 3;
		case Rank::Four: 	return 4;
		case Rank::Five: 	return 5;
		case Rank::Six: 	return 6;
		case Rank::Seven: 	return 7;
		case Rank::Eight: 	return 8;
		case Rank::Nine: 	return 9;
		case Rank::Ten: 
		case Rank::Jack: 
		case Rank::Queen: 
		case Rank::King: 	return 10;
		case Rank::Ace: 	return 11;
	}
	return 0;
}
