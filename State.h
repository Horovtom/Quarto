//
// Created by lactosis on 9.2.19.
//

#ifndef QUARTO_STATE_H
#define QUARTO_STATE_H
#include <iostream>

class State {
public:

    State();

    bool usedPieces[16];
    int positions[16];
    int onTurn = -1;
    int won;
    int inHand;
    int prevInHand;

    std::string toString();
    std::string pieceString(int piece);
    void makeTurn(int where, int piece);
    void removeTurn(int where);
    void checkEnd();
    void firstTurn(int piece);

    bool winningMove(int where);

    bool haveWon();

    bool theSame(int i, int i1, int i2, int i3);
    State copy();

    int getPieceNum(std::string properties);
};


#endif //QUARTO_STATE_H
