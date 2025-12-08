//
// Created by lib_laptop on 11/26/2025.
//

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H

class MiniMaxAIPlayer;

class Board {
public:
    // Constructor
    Board();

    void display() const;
    char getCellValue(int row, int col) const;  // helper for display() (useful for hypothetical GUI)

    void applyMove(int row, int col, char symbol);
    bool isValidMove(int row, int col) const; // helper for applyMove()

    bool winCheck(char symbol) const;
    bool tieCheck() const;

private:
    // Not initializing here because may want to test w/ pre-filled board via constructor
    char grid[3][3];
    int filledCells;

    friend class MiniMaxAIPlayer;
};


#endif //FINALPROJECT_BOARD_H