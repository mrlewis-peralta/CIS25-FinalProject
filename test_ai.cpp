//
// Created by lib_laptop on 11/30/2025.
//

// test_ai.cpp
// Tests for RegularAIPlayer, UnbeatableAIPlayer, and MiniMaxAIPlayer, including
// heavy simulations to verify Unbeatable AI never loses and MiniMax AI never loses.

#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <cstdlib>

#include "Board.h"
#include "Player.h"
#include "RegularAIPlayer.h"
#include "UnbeatableAIPlayer.h"
#include "MiniMaxAIPlayer.h"

// Simple random-move AI for testing
// ------------------------------------------------------------
class RandomAIPlayer : public Player {
public:
    explicit RandomAIPlayer(char symbol)
        : Player(symbol, "Random AI") {}

    void makeMove(Board& board) override {
        // Collect all valid moves
        std::vector<std::pair<int, int>> moves;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if (board.isValidMove(r, c)) {moves.emplace_back(r, c);}
            }
        }

        assert(!moves.empty()); // should never be called on a full board

        // Choose one at random
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, static_cast<int>(moves.size()) - 1);

        auto [row, col] = moves[dist(rng)];
        board.applyMove(row, col, symbol);
    }
};

// Helper: play one full AI vs AI game
// Returns 'X' if X wins, 'O' if O wins, 'T' for tie.
// ------------------------------------------------------------
char playAIGame(Player& xPlayer, Player& oPlayer) {
    Board b;
    Player* current = &xPlayer;
    char currentSymbol = 'X';

    for (int turn = 0; turn < 9; turn++) {
        current->makeMove(b);

        if (b.winCheck(currentSymbol)) {return currentSymbol;}
        else if (b.tieCheck()) {return 'T';}

        // Switch players
        if (current == &xPlayer) {
            current = &oPlayer;
            currentSymbol = 'O';
        }
        else {
            current = &xPlayer;
            currentSymbol = 'X';
        }
    }

    // If we somehow get here, treat as tie
    return 'T';
}

// Basic unit tests (small, deterministic)
// ============================================================
void testRegularAI_CenterOnEmptyBoard() {
    std::cout << "Test 1 (RegularAI): takes center on empty board... ";

    Board b;
    RegularAIPlayer ai('X');

    ai.makeMove(b);

    // Center should be 'X'
    assert(b.getCellValue(1, 1) == 'X');

    std::cout << "PASSED\n";
}

void testRegularAI_TakesWinningMove() {
    std::cout << "Test 2 (RegularAI): takes immediate winning move... ";

    Board b;
    // Setup: X X _
    //        _ _ _
    //        _ _ _
    b.applyMove(0, 0, 'X');
    b.applyMove(0, 1, 'X');

    RegularAIPlayer ai('X');
    ai.makeMove(b);

    // AI should place at (0,2) to win
    assert(b.getCellValue(0, 2) == 'X');
    assert(b.winCheck('X'));

    std::cout << "PASSED\n";
}

void testUnbeatableAI_BlocksImmediateThreat() {
    std::cout << "Test 3 (UnbeatableAI): blocks opponent's winning move... ";

    Board b;
    // Setup: _ _ _
    //        _ _ _
    //        O O _
    b.applyMove(2, 0, 'O');
    b.applyMove(2, 1, 'O');

    UnbeatableAIPlayer ai('X');
    ai.makeMove(b);

    // Unbeatable AI should block at (2,2)
    assert(b.getCellValue(2, 2) == 'X');

    std::cout << "PASSED\n";
}

void testAIs_DoNotOverwriteOccupiedCells() {
    std::cout << "Test 4: AIs never overwrite occupied cells... ";

    // Part A: Regular AI
    {
        Board b;
        b.applyMove(1, 1, 'O'); // center already taken

        RegularAIPlayer ai('X');
        ai.makeMove(b);

        // RegularAI must not change the center
        assert(b.getCellValue(1, 1) == 'O');
    }

    // Part B: Unbeatable AI
    {
        Board b;
        b.applyMove(0, 0, 'X');
        b.applyMove(1, 1, 'O');
        b.applyMove(2, 2, 'X');

        UnbeatableAIPlayer ai('O');
        ai.makeMove(b);

        // None of the originally occupied cells should change
        assert(b.getCellValue(0, 0) == 'X');
        assert(b.getCellValue(1, 1) == 'O');
        assert(b.getCellValue(2, 2) == 'X');
    }

    // Part C: MiniMax AI
    {
        Board b;
        b.applyMove(1, 1, 'X');
        b.applyMove(0, 0, 'O');

        MiniMaxAIPlayer ai('X');
        ai.makeMove(b);

        // Originally occupied cells should not change
        assert(b.getCellValue(1, 1) == 'X');
        assert(b.getCellValue(0, 0) == 'O');
    }

    std::cout << "PASSED\n";
}

// Heavy simulation tests for UnbeatableAI
// ============================================================
void simulate_Unbeatable_vs_Unbeatable() {
    std::cout << "Simulation 1: Unbeatable vs Unbeatable (should always tie)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    UnbeatableAIPlayer xAI('X');
    UnbeatableAIPlayer oAI('O');

    for (int i = 0; i < NUM_GAMES; i++) {
        char result = playAIGame(xAI, oAI);
        if (result == 'X') xWins++;
        else if (result == 'O') oWins++;
        else ties++;
    }

    // Unbeatable vs Unbeatable should never have a winner
    assert(xWins == 0);
    assert(oWins == 0);
    assert(ties == NUM_GAMES);

    std::cout << "PASSED (" << ties << " ties)\n";
}

void simulate_Unbeatable_vs_Regular() {
    std::cout << "Simulation 2: Unbeatable (X) vs Regular (O)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    UnbeatableAIPlayer xAI('X');
    RegularAIPlayer oAI('O');

    for (int i = 0; i < NUM_GAMES; i++) {
        char result = playAIGame(xAI, oAI);
        if (result == 'X') xWins++;
        else if (result == 'O') oWins++;
        else ties++;
    }

    // Unbeatable should never lose
    assert(oWins == 0);

    std::cout << "PASSED (X wins: " << xWins << ", ties: " << ties << ")\n";
}

void simulate_Regular_vs_Unbeatable() {
    std::cout << "Simulation 3: Regular (X) vs Unbeatable (O)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    RegularAIPlayer xAI('X');
    UnbeatableAIPlayer oAI('O');

    for (int i = 0; i < NUM_GAMES; i++) {
        char result = playAIGame(xAI, oAI);
        if (result == 'X') xWins++;
        else if (result == 'O') oWins++;
        else ties++;
    }

    // Unbeatable (O) should never lose
    assert(xWins == 0);

    std::cout << "PASSED (O wins: " << oWins << ", ties: " << ties << ")\n";
}

void simulate_Unbeatable_vs_Random() {
    std::cout << "Simulation 4: Unbeatable (X) vs Random (O)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    UnbeatableAIPlayer xAI('X');
    RandomAIPlayer oAI('O');

    for (int i = 0; i < NUM_GAMES; i++) {
        char result = playAIGame(xAI, oAI);
        if (result == 'X') xWins++;
        else if (result == 'O') oWins++;
        else ties++;
    }

    // Unbeatable should never lose
    assert(oWins == 0);

    std::cout << "PASSED (X wins: " << xWins << ", ties: " << ties << ")\n";
}

void simulate_Random_vs_Unbeatable() {
    std::cout << "Simulation 5: Random (X) vs Unbeatable (O)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    RandomAIPlayer xAI('X');
    UnbeatableAIPlayer oAI('O');

    // We'll log each move (player + coordinates) so we can replay if Unbeatable loses.
    struct Move {char player; int row; int col;};

    for (int game = 0; game < NUM_GAMES; game++) {

        Board b;
        Player* current = &xAI;
        char currentSymbol = 'X';
        bool gameEnded = false;

        std::vector<Move> history;
        history.reserve(9);  // max 9 moves in Tic-Tac-Toe

        for (int turn = 0; turn < 9; turn++) {
            // Save board before move
            Board before = b;

            // Let current player move
            current->makeMove(b);

            // Detect which cell changed
            int moveRow = -1;
            int moveCol = -1;

            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    char oldVal = before.getCellValue(r, c);
                    char newVal = b.getCellValue(r, c);

                    if (oldVal != newVal) {
                        moveRow = r;
                        moveCol = c;
                    }
                }
            }

            // Sanity check: exactly one cell should have changed
            assert(moveRow != -1 && moveCol != -1);

            history.push_back(Move{ currentSymbol, moveRow, moveCol });

            // Check win
            if (b.winCheck(currentSymbol)) {

                if (currentSymbol == 'X') {
                    // 🔥 Unbeatable (O) just lost. Print full move-by-move replay.
                    std::cout << "\n\n*** FAILURE DETECTED IN SIMULATION 5 ***\n";
                    std::cout << "Random AI (X) defeated Unbeatable AI (O).\n";
                    std::cout << "Final board:\n\n";
                    b.display();

                    std::cout << "\nMove-by-move replay:\n";

                    Board replay;
                    for (size_t i = 0; i < history.size(); i++) {
                        const Move& m = history[i];
                        replay.applyMove(m.row, m.col, m.player);

                        std::cout << "\nAfter move " << (i + 1)
                                  << " (" << m.player << " at ["
                                  << m.row << "," << m.col << "]):\n";
                        replay.display();
                    }

                    std::cout << "\nStopping further simulations.\n";
                    std::exit(1);
                }

                // O (Unbeatable) won normally
                oWins++;
                gameEnded = true;
                break;
            }

            // Check tie
            if (b.tieCheck()) {
                ties++;
                gameEnded = true;
                break;
            }

            // Switch players
            if (current == &xAI) {
                current = &oAI;
                currentSymbol = 'O';
            }
            else {
                current = &xAI;
                currentSymbol = 'X';
            }
        }

        // Safety: if somehow we exit loop without win/tie, count as tie
        if (!gameEnded) {ties++;}
    }

    std::cout << "PASSED (O wins: " << oWins << ", ties: " << ties << ")\n";
}

// Heavy simulation tests for MiniMaxAI
// ============================================================
void simulate_MiniMax_vs_Random() {
    std::cout << "Simulation 6: MiniMax (X) vs Random (O)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    MiniMaxAIPlayer xAI('X');
    RandomAIPlayer oAI('O');

    for (int i = 0; i < NUM_GAMES; i++) {
        char result = playAIGame(xAI, oAI);
        if (result == 'X') xWins++;
        else if (result == 'O') oWins++;
        else ties++;
    }

    // MiniMax should never lose
    assert(oWins == 0);

    std::cout << "PASSED (X wins: " << xWins << ", ties: " << ties << ")\n";
}

void simulate_Random_vs_MiniMax() {
    std::cout << "Simulation 7: Random (X) vs MiniMax (O)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    RandomAIPlayer xAI('X');
    MiniMaxAIPlayer oAI('O');

    // We'll log each move (player + coordinates) so we can replay if MiniMax loses.
    struct Move {char player; int row; int col;};

    for (int game = 0; game < NUM_GAMES; game++) {

        Board b;
        Player* current = &xAI;
        char currentSymbol = 'X';
        bool gameEnded = false;

        std::vector<Move> history;
        history.reserve(9);

        for (int turn = 0; turn < 9; turn++) {
            Board before = b;

            current->makeMove(b);

            int moveRow = -1;
            int moveCol = -1;

            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    char oldVal = before.getCellValue(r, c);
                    char newVal = b.getCellValue(r, c);

                    if (oldVal != newVal) {
                        moveRow = r;
                        moveCol = c;
                    }
                }
            }

            assert(moveRow != -1 && moveCol != -1);
            history.push_back(Move{ currentSymbol, moveRow, moveCol });

            if (b.winCheck(currentSymbol)) {
                if (currentSymbol == 'X') {
                    // 🔥 MiniMax (O) just lost. Print full move-by-move replay.
                    std::cout << "\n\n*** FAILURE DETECTED IN SIMULATION 7 ***\n";
                    std::cout << "Random AI (X) defeated MiniMax AI (O).\n";
                    std::cout << "Final board:\n\n";
                    b.display();

                    std::cout << "\nMove-by-move replay:\n";
                    Board replay;

                    for (size_t i = 0; i < history.size(); i++) {
                        const Move& m = history[i];
                        replay.applyMove(m.row, m.col, m.player);

                        std::cout << "\nAfter move " << (i + 1)
                                  << " (" << m.player << " at ["
                                  << m.row << "," << m.col << "]):\n";
                        replay.display();
                    }

                    std::cout << "\nStopping further simulations.\n";
                    std::exit(1);
                }

                // O (MiniMax) won
                oWins++;
                gameEnded = true;
                break;
            }

            if (b.tieCheck()) {
                ties++;
                gameEnded = true;
                break;
            }

            if (current == &xAI) {
                current = &oAI;
                currentSymbol = 'O';
            }
            else {
                current = &xAI;
                currentSymbol = 'X';
            }
        }

        if (!gameEnded) {ties++;}
    }

    // MiniMax should never lose
    assert(xWins == 0);

    std::cout << "PASSED (O wins: " << oWins << ", ties: " << ties << ")\n";
}

void simulate_MiniMax_vs_Regular() {
    std::cout << "Simulation 8: MiniMax (X) vs Regular (O)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    MiniMaxAIPlayer xAI('X');
    RegularAIPlayer oAI('O');

    for (int i = 0; i < NUM_GAMES; i++) {
        char result = playAIGame(xAI, oAI);
        if (result == 'X') xWins++;
        else if (result == 'O') oWins++;
        else ties++;
    }

    // MiniMax should never lose
    assert(oWins == 0);

    std::cout << "PASSED (X wins: " << xWins << ", ties: " << ties << ")\n";
}

void simulate_Regular_vs_MiniMax() {
    std::cout << "Simulation 9: Regular (X) vs MiniMax (O)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    RegularAIPlayer xAI('X');
    MiniMaxAIPlayer oAI('O');

    for (int i = 0; i < NUM_GAMES; i++) {
        char result = playAIGame(xAI, oAI);
        if (result == 'X') xWins++;
        else if (result == 'O') oWins++;
        else ties++;
    }

    // MiniMax should never lose
    assert(xWins == 0);

    std::cout << "PASSED (O wins: " << oWins << ", ties: " << ties << ")\n";
}

void simulate_MiniMax_vs_Unbeatable() {
    std::cout << "Simulation 10: MiniMax (X) vs Unbeatable (O)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    MiniMaxAIPlayer xAI('X');
    UnbeatableAIPlayer oAI('O');

    for (int i = 0; i < NUM_GAMES; i++) {
        char result = playAIGame(xAI, oAI);
        if (result == 'X') xWins++;
        else if (result == 'O') oWins++;
        else ties++;
    }

    // MiniMax should never lose
    assert(oWins == 0);

    std::cout << "PASSED (X wins: " << xWins << ", ties: " << ties << ")\n";
}

void simulate_Unbeatable_vs_MiniMax() {
    std::cout << "Simulation 11: Unbeatable (X) vs MiniMax (O)... ";

    const int NUM_GAMES = 1000;
    int xWins = 0, oWins = 0, ties = 0;

    UnbeatableAIPlayer xAI('X');
    MiniMaxAIPlayer oAI('O');

    for (int i = 0; i < NUM_GAMES; i++) {
        char result = playAIGame(xAI, oAI);
        if (result == 'X') xWins++;
        else if (result == 'O') oWins++;
        else ties++;
    }

    // MiniMax should never lose
    assert(xWins == 0);

    std::cout << "PASSED (O wins: " << oWins << ", ties: " << ties << ")\n";
}

// main
// ============================================================
int main() {
    std::cout << "\n=== AI Tests (Regular, Unbeatable, MiniMax) ===\n\n";

    // Basic unit tests
    testRegularAI_CenterOnEmptyBoard();
    testRegularAI_TakesWinningMove();
    testUnbeatableAI_BlocksImmediateThreat();
    testAIs_DoNotOverwriteOccupiedCells();

    std::cout << "\n=== Heavy Unbeatable-AI Simulations ===\n\n";

    simulate_Unbeatable_vs_Unbeatable();
    simulate_Unbeatable_vs_Regular();
    simulate_Regular_vs_Unbeatable();
    simulate_Unbeatable_vs_Random();
    simulate_Random_vs_Unbeatable();

    std::cout << "\n=== Heavy MiniMax-AI Simulations ===\n\n";

    simulate_MiniMax_vs_Random();
    simulate_Random_vs_MiniMax();
    simulate_MiniMax_vs_Regular();
    simulate_Regular_vs_MiniMax();
    simulate_MiniMax_vs_Unbeatable();
    simulate_Unbeatable_vs_MiniMax();

    std::cout << "\nAll AI tests passed!\n";
    return 0;
}
