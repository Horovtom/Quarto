//
// Created by lactosis on 9.2.19.
//

#include <cmath>
#include "State.h"

State::State() {
    for (int i = 0; i < 16; i++) {
        usedPieces[i] = false;
        positions[i] = -1;
    }

}

std::string State::toString() {
    std::string res;

    res += "---------------------\n";

    for (int i = 0; i < 4; i++) {
        res += "|";
        for (int j = 0; j < 4; j++) {
            int curr = i * 4 + j;

            if (positions[curr] != -1) {
                res += pieceString(positions[curr]) + "|";
            } else {
                res += "    |";
            }
        }
        res += "\n";
    }
    res += "-------------------\n";
    return res;


}

std::string State::pieceString(int piece) {

    // Tall Little
    // Black White
    // Circle Square
    // Flat Hole
    std::string res;
    if ((piece & 1) > 0) res += "T";
    else res += "L";

    if ((piece & 2) > 0) res += "B";
    else res += "W";

    if ((piece & 4) > 0) res += "S";
    else res += "C";

    if ((piece & 8) > 0) res += "H";
    else res += "F";
    return res;

}

void State::makeTurn(int where, int piece) {
    if (usedPieces[piece]) {
        std::cerr << "Piece already used" << std::endl;
        return;
    } else if (positions[where] != -1) {
        std::cerr << "Position is already occupied" << std::endl;
        return;
    }


    positions[where] = inHand;
    usedPieces[piece] = true;
    prevInHand = inHand;
    inHand = piece;

    checkEnd();
//    if (won != 0) {
//        std::cout << "Player " << won;
//        if (won == 1) {
//            std::cout << " who first dealt a piece ";
//        } else {
//            std::cout << " who got the first piece ";
//        }
//        std::cout << " has won!" << std::endl;
//    }
    onTurn = onTurn * -1;
}


void State::checkEnd() {
    if (haveWon()) won = onTurn;
}

bool State::theSame(int i, int i1, int i2, int i3) {
    if (positions[i] == -1 || positions[i1] == -1 || positions[i2] == -1 || positions[i3] == -1) return false;

    for (int j = 0; j < 4; j++) {
        auto mask = static_cast<int>(pow(2, j));
        int a = positions[i] & mask;
        int b = positions[i1] &mask;
        int c = positions[i2] & mask;
        int d = positions[i3] & mask;

        if (a == b && b == c && c == d) return true;
    }

    return false;
}


void State::firstTurn(int piece) {
    inHand = piece;
    usedPieces[piece] = true;
    onTurn = onTurn * -1;
}

State State::copy() {
    State s;
    s.onTurn = onTurn;
    s.won = won;
    s.inHand = inHand;

    for (int i = 0; i < 16; i++) {
        s.usedPieces[i] = usedPieces[i];
        s.positions[i] = positions[i];
    }

    return s;
}

void State::removeTurn(int where) {
    int piece = positions[where];
    if (piece == -1) return;
    usedPieces[inHand] = false;
    positions[where] = -1;
    onTurn = onTurn * -1;
    inHand = prevInHand;
    won = 0;
}

int State::getPieceNum(std::string properties) {
    bool tall = false;
    bool black = false;
    bool flat = false;
    bool circle = false;

    // Tall Little
    // Black White
    // Circle Square
    // Flat Hole

    if (properties.find('T') != properties.npos) {
        tall = true;
    }
    if (properties.find('L') != properties.npos) {
        tall = false;
    }

    if (properties.find('B') != properties.npos) {
        black = true;
    }
    if (properties.find('W') != properties.npos) {
        black = false;
    }

    if (properties.find('C') != properties.npos) {
        circle = true;
    }
    if (properties.find('S') != properties.npos) {
        circle = false;
    }

    if (properties.find('F') != properties.npos) {
        flat = true;
    }
    if (properties.find('H') != properties.npos) {
        flat = false;
    }

    int num = tall + black * 2 + (!circle) * 4 + (!flat) * 8;
    return num;
}

bool State::winningMove(int where) {
    int orig = positions[where];
    positions[where] = inHand;
    bool winning = haveWon();
    positions[where] = orig;

    return winning;
}

bool State::haveWon() {
    for (int i = 0; i < 16; i += 4) {
        if (theSame(i, i + 1, i + 2, i + 3)) {
            return true;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (theSame(i, i + 4, i + 8, i + 12)) {
            return true;
        }
    }

    //diag

    if (theSame(0, 5, 10, 15)) {
        return true;
    }

    return theSame(3, 6, 9, 12);

}


