#include <iostream>
#include <stack>
#include <vector>
#include "State.h"
#include <chrono>

void minimax();

void play() {
    State g;

    bool first = true;

    while(g.won == 0) {
        int whereX = 0;
        int whereY = 0;
        if (!first) {
            std::cout << "Where x: ";
            std::cin >> whereX;

            std::cout << "Where y: ";
            std::cin >> whereY;
        }

        std::string s;
        std::cout << "Piece " << std::endl;
        std::cin >> s;

        int num = g.getPieceNum(s);

        if (g.usedPieces[num]) {
            std::cerr << "Piece already used" << std::endl;
        }

        if (first) {
            g.firstTurn(num);
            first = false;
        } else {
            g.makeTurn(whereY * 4 + whereX,num);
        }
        std::cout << g.toString() << std::endl;

    }

    std::cout << g.won << std::endl;

}

std::stack<std::string> stack;
int main() {
    minimax();

    while(!stack.empty()) {
        std::cout << stack.top() << std::endl;
        stack.pop();
    }

    //play();
    return 0;
}


auto start = std::chrono::high_resolution_clock::now();

int minimaxStep(State s, int depth) {
//    std::cout << s.toString() << std::endl;

    if (s.won != 0) {
        return s.won;
    }

    std::vector<int> possiblePositions, possiblePieces;

    for (int i = 0; i < 16; i++) {
        if (s.positions[i] == -1) {
            if (s.winningMove(i)) {
                return s.onTurn;
            }

            possiblePositions.emplace_back(i);
        }
        if (!s.usedPieces[i]) {
            possiblePieces.emplace_back(i);
        }
    }

    for (auto position : possiblePositions) {
        for (auto piece: possiblePieces) {
            s.makeTurn(position, piece);
            int res = minimaxStep(s, depth + 1);
            s.removeTurn(position);
            if (res == s.onTurn) {
                return s.onTurn;
            }
        }
    }
//    std::cout << "Did not find any winning combination" << std::endl;
    return -s.onTurn;
}

void minimax() {
    // Simple minimax solution.

    State s;
    s.firstTurn(s.getPieceNum("LSHB"));
    s.makeTurn(13, s.getPieceNum("LSBF"));
    s.makeTurn(14, s.getPieceNum("LCBF"));
    s.makeTurn(8, s.getPieceNum("TWFC"));
    s.makeTurn(9, s.getPieceNum("TFSW"));
//    s.makeTurn(10, s.getPieceNum("SBTF"));
//    s.makeTurn(4, s.getPieceNum("TCHB"));
//    s.makeTurn(5, s.getPieceNum("LCHB"));
//    s.makeTurn(6, s.getPieceNum("LCHW"));
//    s.makeTurn(7, s.getPieceNum("TWSH"));
//    s.makeTurn(1, s.getPieceNum("TWCH"));
//    s.makeTurn(3, s.getPieceNum("LSWH"));
    std::cout << s.toString() << std::endl;
    std::cout << "On turn: " << s.onTurn << std::endl;

    int res = minimaxStep(s, 1);
    
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout <<  "Time of computation: " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";
    std::cout << "Player: " << res  << " has won!" << std::endl;


}