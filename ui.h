#ifndef UI_H
#define UI_H

#include "cards.h"
#include "engine.h"
#include <vector>
#include <string>
#include <tuple>
#include <iostream>

int takeAct(bool canSplit, bool hasPlayed) {
	std::string input;
	std::vector<std::string> allowed = {"Hit","Stand"};
	if (!hasPlayed) { allowed.push_back("Double"); }
	if (canSplit) { allowed.push_back("Split"); }

	for (int i = 0; i < allowed.size(); ++i) {
		if (i != 0 ) { std::cout << ", "; }
		if ( i == allowed.size() - 1 ) {
			std::cout << "or ";
		}
		std::cout << allowed[i];
	}
	std::cout << ": ";
	std::cin >> input;

	for (int i = 0; i < allowed.size(); ++i) {
		if ( input == allowed[i] ) { return i; }
	}

	std::cout << "Error: invalid action"
	return takeAct(canSplit, hasPlayed);	
}

void runAct(Deck& deck, Player& player, int handID) {
	Hand hand = player.getHand()
	int act = takeAct((hand.getCard(0).getId() == hand.getCard(1).getId()), hand.getPlay());
	if (act == 0) { playerHit(deck, player, handID); }
	if (act == 1) { return; }
	if (act == 2) { playerDoub(deck, player, handID); }
	if (act == 3) { playerSplit(handID); }	
}




#endif // UI_H
