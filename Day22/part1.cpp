#include <fstream>
#include <iostream>
#include <string>
#include <queue>

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

void playGame(queue<int> &deck1, queue<int> &deck2) {
    do {
        int card1 = deck1.front(), card2 = deck2.front();
        deck1.pop();
        deck2.pop();
        if(card1 > card2) {
            deck1.push(card1);
            deck1.push(card2);
        } else {
            deck2.push(card2);
            deck2.push(card1);
        }
    } while(deck1.size() > 0 && deck2.size() > 0);
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