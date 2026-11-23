#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <random>
#include "cards.h"

inline std::random_device rng;
inline std::ranlux48 prng(rng());

Card randomCard(Deck& deck) {
	std::vector<double> weights = deck.getWeight();
	std::vector<int> values(weights.size());
	std::iota(values.begin(), values.end(), 0);
	std::discrete_distribution<int> dist(
		weights.begin(), weights.end()	
	);

	int randId = values[dist(prng)];
	Card card = deck.dealCard(randId);
	return card;
}

void dealerAct(Deck& deck, Hand& dealer) {
	if (dealer.getSoft() >= 17) { return; }
	Card card = randomCard(deck);
	dealer.hit(card.getId());
	return dealerAct(deck, dealer);	
}

void playerHit(Deck& deck, Player& player, int handID) {
	Card card = randomCard(deck);
	player.hit(handID, card.getId());
}

void playerDoub(Deck& deck, Player& player, const int& handID) {
	Card card = randomCard(deck);
	player.doub(handID, card.getId());
}

void playerSplit(Deck& deck, Player& player, const int& handID) {
	player.split(handID);
}


#endif //  ENGINE_H
