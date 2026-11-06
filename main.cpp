#include <iostream>
#include <chrono>
#include "gameengine.hpp"
#include "decisionstrategy.hpp"

int main() {
	const int totalRounds = 1e6;
	const int baseBet = 2;
	const int initialBankroll = 1e7;

	GameEngine engine(12345);
	Participant player(initialBankroll);
	BasicStrategy basicStrategy;

	auto startTime = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < totalRounds; ++i) {
		engine.playRound(player, basicStrategy, baseBet);
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = endTime - startTime;

	int finalProfit = player.getBankroll() - initialBankroll;
	double rtp = (static_cast<double>(player.getBankroll()) / initialBankroll) * 100.0;

	std::cout << "Rundy:          " << totalRounds << std::endl;
	std::cout << "Czas:           " << duration.count() << " ms" << std::endl;
	std::cout << "Predkosc:       " << static_cast<int>(totalRounds / (duration.count() / 1000.0)) << " req/s" << std::endl;
	std::cout << "Start Bankroll: " << initialBankroll << " zl" << std::endl;
	std::cout << "End Bankroll:   " << player.getBankroll() << " zl" << std::endl;
	std::cout << "Profit:         " << finalProfit << " zl" << std::endl;

	return 0;
}
