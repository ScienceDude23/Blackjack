#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>
#include <tuple>

struct CardList {
	std::vector<std::string> list = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};

	std::string getName(int testId) {
		if (testId >= 0 && testId < list.size()) { return list[testId]; }
		return "Error";
		}

	int getId(std::string testName) {
		for (int i = 0; i < list.size(); ++i) {
			if (list[i] == testName) { return i; }
		}
		return -1;
	}
};

class Card {
	private:
		std::string name;
		int id;

	public:
		void init(int no) {
			CardList list;

			name = list.getName(no);
			id = no;
		}

		std::string getName() const { return name; }
		int getId() const { return id; }
};

class Deck {
	private:
		std::vector<int> cards;
		int runningCount;
		double trueCount;

		int numCards;
		int initDecks;
		double currDecks;

	public:
		void init(int numDecks) {
			initDecks = numDecks;
			currDecks = numDecks;
			numCards = 52 * numDecks;

			runningCount = 0;
			trueCount = 0.0;

			cards.clear();
			for (int i = 0; i < 13; ++i) {
				cards.push_back(4 * numDecks);
			}
		}

		Card dealCard(int cardId) {
			cards[cardId] -= 1;
			numCards -= 1;
			currDecks = numCards / 52.0;

			if (cardId >= 0 && cardId <= 4) { runningCount += 1; }
			if (cardId >= 8 && cardId <= 13) { runningCount -=1; }
			trueCount = runningCount / currDecks;

			Card card;
			card.init(cardId);
			return card;
		}

		int getRun() const { return runningCount; }
		double getTrue() const { return trueCount; }
		int getNum() const { return numCards; }
		int getInit() const { return initDecks; }
		double currDecks() const { return currDecks; }
		const std::vector<double>& getWeight() const {
			std::vector<double> weights;
			for (int i = 0; i < cards.size(); ++i) {
				weights[i] = 100 * cards[i] / cards.size();
			}
			return weights;
		}
};

class Hand {
	private:
		std::vector<Card> cards;
		int softScore;
		int hardScore;

		bool hasPlayed;
		bool hasDoubled;
		bool hasBusted;

	public:
		void initS(int id) {
			hasPlayed,hasDoubled,hasBusted = false;
			cards.clear();
			hit(id);
		}

		void initD(int id1, int id2) {
			hasPlayed,hasDoubled,hasBusted = false;
			cards.clear();
			hit(id1);
			hit(id2);
		}
	
		void calScore() {
			for (const auto& card : cards) {
				int i = card.getId();
				if (i >= 0 && i <= 8) {
					softScore += i + 2;
					hardScore += i + 2;
				}

				if (i > 8 && i < 12) {
					softScore += 10;
					hardScore += 10;
				}

				if (i == 12) {
					softScore += 11;
					hardScore += 1;
				}
			}
			hasBusted = (hardScore > 21);
		}

		void hit(int id) {
			Card newCard;
			newCard.init(id);
			cards.push_back(newCard);
			calScore();

			hasPlayed = true;
		}

		void doub(int id) {
			hit(id);
			hasDoubled = true;
		}

		std::vector<Hand> split() {
			Hand hand1;
			Hand hand2;
			
			hand1.initS(cards[0].getId());
			hand2.initS(cards[1].getId());

			std::vector<Hand> hands;
			hands.push_back(hand1);
			hands.push_back(hand2);

			return hands;
		}

		Card getCard(int i) { return cards[i]; } 

		int getHard() const { return hardScore; }
		int getSoft() const { return softScore; }
		bool getPlay() const { return hasPlayed; }
		bool getDoub() const { return hasDoubled; }
		bool getBust() const { return hasBusted; }
};

class Player {
	private:
		std::vector<Hand> hands;
		int money;

	public:
		void newHand(Hand hand) {
			hands.clear();
			hands.push_back(hand);
		}
		
		void init(Hand hand, int startCash) {
			newHand(hand);
			money = startCash;
		}

		void hit(int handID, int cardID) {
			hands[handID].hit(cardID);
		}
		void doub(int handID, int cardID) {
			hands[handID].doub(cardID);
		}

		void split(int id) {
			std::vector<Hand> temp = hands[id].split();
			hands.erase(hands.begin() + id);
			hands.insert(hands.begin() + id, temp[1]);
			hands.insert(hands.begin() + id, temp[0]);
		}

		std::vector<Hand> getHands() const { return hands; }
};

#endif // CARDS_H

