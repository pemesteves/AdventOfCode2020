#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

void parseDeck(queue<int> &deck, ifstream &f) {
    string line;
    getline(f, line);
    
    while (!f.eof())
    {
        getline(f, line);
        if(line.size() == 0) break;

        deck.push(stoi(line));
    }
}

bool foundRound(unordered_multimap<int, int> &rounds, int card1, int card2) {
    auto its = rounds.equal_range(card1);
    for (auto it = its.first; it != its.second; ++it) {
        if((*it).second == card2) return true;
    }

    return false;
}

int playGame(queue<int> &deck1, queue<int> &deck2) {
    unordered_multimap<int, int> rounds;
    do {
        int card1 = deck1.front(), card2 = deck2.front();

        if(foundRound(rounds, card1, card2)) {
            return 1;
        }

        rounds.insert(make_pair(card1, card2));

        deck1.pop();
        deck2.pop();

        if(card1 <= deck1.size() && card2 <= deck2.size()) {
            queue<int> d1 = deck1, d2 = deck2;
            int winner = playGame(d1, d2);
            if(winner == 1) {
                deck1.push(card1);
                deck1.push(card2);
            } else {
                deck2.push(card2);
                deck2.push(card1);
            }
        } else if(card1 > card2) {
            deck1.push(card1);
            deck1.push(card2);
        } else {
            deck2.push(card2);
            deck2.push(card1);
        }
    } while(deck1.size() > 0 && deck2.size() > 0);

    return deck1.size() == 0 ? 2 : 1;
}

unsigned long long getResult(queue<int> winningDeck) {
    unsigned long long result = 0;

    do {
        result += winningDeck.size() * winningDeck.front();
        winningDeck.pop();
    } while(winningDeck.size() > 0);

    return result;
}

int main()
{
    queue<int> player1Deck, player2Deck;

    ifstream f;
    f.open("input.txt");

    parseDeck(player1Deck, f);
    parseDeck(player2Deck, f);

    f.close();

    playGame(player1Deck, player2Deck);

    if(player1Deck.size() == 0) {
        cout << getResult(player2Deck) << endl;
    } else if (player2Deck.size() == 0) {
        cout << getResult(player1Deck) << endl;
    }

    return 0;
}