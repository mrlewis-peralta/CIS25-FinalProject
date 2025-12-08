# TicTacToe AI

A command-line TicTacToe game featuring multiple types of players, including Human players, a Regular AI, a traditional Unbeatable AI, and a Minimax-based AI.

## Features

Planned core features for this project:

- Human vs Human gameplay
- Human vs Regular AI (simple or non-optimal strategy)
- Human vs Unbeatable AI (traditional perfect strategy)
- Human vs Minimax AI (algorithmic perfect strategy using recursive minimax)
- Ability to choose the type of Player 1 and Player 2 independently (any combination of the four types)
- Clear board display, input validation, and turn-by-turn prompts
- Game menu that allows replaying multiple games without restarting the program

## Building

This project is intended to be built with CMake.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

This will generate and compile the executable inside the `build/` directory.

## Usage

After building, run:

```bash
./tictactoe_game
```

When complete, the program will:

- Display a main menu
- Let the user choose the type of Player 1 (X) and Player 2 (O):
  - Human
  - Regular AI
  - Unbeatable AI
  - Minimax AI
- Run a full TicTacToe game:
  - Alternate turns between player1 and player2
  - Display the board after each move
  - Enforce valid moves
  - Detect and announce wins or ties
- Ask the user if they want to play another game or quit

## Class Overview

### `Board`
Manages the TicTacToe grid, move validation, applying moves, win detection, tie detection, and displaying the board.

### `Player` (abstract)
Base class for all player types. Stores the player's symbol and name and declares `makeMove(Board& board)` as a pure virtual function.

### `AIPlayer` (abstract)
Base class for AI player types. Inherits from `Player` and provides a common interface and constructor for AI-based players.

### `HumanPlayer`
Derived from `Player`. Handles user input, validates moves using the `Board`, and applies valid moves.

### `RegularAIPlayer`
Derived from `AIPlayer`. Uses a simple or non-optimal strategy to pick moves (e.g., random valid moves or basic heuristics).

### `UnbeatableAIPlayer`
Derived from `AIPlayer`. Implements a traditional perfect TicTacToe strategy using known optimal play patterns.

### `MiniMaxAIPlayer`
Derived from `AIPlayer`. Uses a recursive minimax search to evaluate possible board states and choose an optimal move. This class is a friend of `Board` so it can examine internal board state for evaluation.

### `TicTacToe`
Coordinates the overall program flow:
- Presents the main menu
- Allows the user to choose player types for Player 1 and Player 2
- Manages the `Board`, `player1`, `player2`, and `currentPlayer`
- Runs the game loop and handles replaying games

## Project Structure

- `src/` Implementation files (`main.cpp`, `Board.cpp`, `TicTacToe.cpp`, and player `.cpp` files)
- `include/` Header files for all classes
- `docs/` Checkpoint documents and reflections
- `CMakeLists.txt`

## Current Status

### ✅ Implemented Features (Checkpoint Features)
- **Feature 1: Regular AI Player**  
  Implemented with intelligent heuristics:  
  - Plays winning move if available  
  - Blocks opponent’s immediate win  
  - Takes center when available  
  - Otherwise takes a corner or a valid move  

- **Feature 2: Unbeatable AI Player (Perfect Strategy)**  
  Fully implemented using the traditional 8-rule perfect TicTacToe strategy:  
  - Immediate win  
  - Immediate block  
  - Fork creation  
  - Correct specialized fork-blocking logic  
  - Center, opposite-corner, empty-corner, empty-side rules  
  - Verified through automated AI-vs-AI simulations ensuring Unbeatable never loses  

- **Feature 3: MiniMax AI Player**  
  Fully implemented using recursive minimax to evaluate game states and select optimal moves.  
  - Uses the existing `Board` interface for move simulation  
  - Plays perfect TicTacToe (wins when possible, otherwise forces a tie)  
  - Integrates as an additional selectable player type in the setup menu  

### ✅ Core Gameplay Completed
- Working 3×3 board with formatted display
- Valid-move enforcement
- Win and tie detection
- Replay-friendly game loop
- Independent selection of Player 1 and Player 2 types

### 🔧 In Progress / Optional Improvements
- Additional UI polish for prompts and menu text
- Polishing of implementation code
- Secret QWE/ASD/ZXC input in-lieu of numberpad for Human Player

## Known Issues / Limitations
- **Numberpad-style input** may be awkward on laptops without a numberpad.
- **Phone keypad layout** differs from a keyboard keypad layout, which may confuse some users.
- The Unbeatable AI implementation is functional but could be refactored for cleaner reuse of shared AI utilities.
