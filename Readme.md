# Blackjack Simulator

A fast blackjack simulator written in C++. It plays millions of rounds using basic strategy and reports the player's results.

## Features

- 8-deck shoe with a cut card and card counting (running / true count)
- Player basic strategy: hit, stand, double down, split
- Dealer draws to 17
- Blackjack pays 3:2
- Fixed RNG seed for reproducible results

## Build and run

```bash
g++ -std=c++17 -O2 -Iinclude main.cpp src/*.cpp -o blackjack_sim
./blackjack_sim
```

## Sample output

```
Rundy:          1000000
Czas:           402.628 ms
Predkosc:       2483683 req/s
Start Bankroll: 10000000 zl
End Bankroll:   9987143 zl
Profit:         -12857 zl
```

Simulation parameters (number of rounds, bet size and bankroll) can be changed in `main.cpp`.

## Structure

```
include/   headers (Card, Deck, Shoe, Hand, Participant, DecisionStrategy, GameEngine)
src/       implementations
main.cpp   runs the simulation
```

To add your own strategy, inherit from `DecisionStrategy` and override `getAction()`.
