//
// Created by lib_laptop on 11/29/2025.
//

#include <iostream>
#include <cassert>
#include "Board.h"

int main() {

    // =============================================================
    // Test 1: New board is empty, no winner, no tie
    // =============================================================
    {
        Board b;

        // No wins for X or O
        assert(!b.winCheck('X'));
        assert(!b.winCheck('O'));

        // Not a tie on an empty board
        assert(!b.tieCheck());

        // All cells should be empty AND valid moves
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                assert(b.isValidMove(r, c));
                assert(b.getCellValue(r, c) == ' ');
            }
        }
    }

    // =============================================================
    // Test 2: X wins on the top row
    // =============================================================
    {
        Board b;

        b.applyMove(0, 0, 'X');
        b.applyMove(0, 1, 'X');
        b.applyMove(0, 2, 'X');

        assert(b.winCheck('X'));   // X should win
        assert(!b.winCheck('O'));  // O should NOT win
        assert(!b.tieCheck());     // Not a tie
    }

    // =============================================================
    // Test 3: Tie board (full board, no winner)
    // =============================================================
    {
        Board b;

        // Pattern with no 3 in a row:
        // X O X
        // X O O
        // O X X
        b.applyMove(0, 0, 'X');
        b.applyMove(0, 1, 'O');
        b.applyMove(0, 2, 'X');

        b.applyMove(1, 0, 'X');
        b.applyMove(1, 1, 'O');
        b.applyMove(1, 2, 'O');

        b.applyMove(2, 0, 'O');
        b.applyMove(2, 1, 'X');
        b.applyMove(2, 2, 'X');

        assert(!b.winCheck('X'));  // No X win
        assert(!b.winCheck('O'));  // No O win
        assert(b.tieCheck());      // Should be a tie
    }

    std::cout << "All Board tests passed!\n";
    return 0;
}