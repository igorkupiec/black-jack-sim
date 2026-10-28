#pragma once

enum class Rank{
	Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
	Jack, Queen, King, Ace
};

class Card{
	private:
		Rank rank;	
	public:
		explicit Card(Rank rank);
		Rank getRank() const;
		int getValue() const;
};
