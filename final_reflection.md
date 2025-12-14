# Final Project Reflection — TicTacToe

## Project Summary

For my final project, I implemented a fully functional **TicTacToe game in C++** using object-oriented design, inheritance, and polymorphism. The project supports multiple player types, including several AI strategies of increasing sophistication, and emphasizes correctness, testing, and incremental feature development.

The final system includes:

* A `TicTacToe` game controller
* A `Board` class encapsulating game state and rules
* A polymorphic `Player` hierarchy
* Multiple AI strategies (Regular, Unbeatable, and MiniMax)
* Automated tests and large-scale simulations to validate correctness

---

## Implemented Features

### Core Gameplay

* Fully functional TicTacToe game loop
* Board display, win detection, and tie detection
* Replay support without restarting the program
* Clear separation of responsibilities across classes

### Player Types

#### HumanPlayer

* Supports numeric keypad input (1–9)
* Also supports **Q/W/E/A/S/D/Z/X/C** inputs (case-insensitive) for laptops without numpads
* Robust input validation and recovery
* Clear visual prompt showing the board-to-input mapping

#### RegularAIPlayer

* Takes the center when available
* Plays immediate winning moves
* Blocks opponent’s immediate winning moves
* Falls back to a random valid move when no heuristic applies

#### UnbeatableAIPlayer

* Implements a full **8-step perfect-play strategy** without minimax:

  1. Win if possible
  2. Block opponent wins
  3. Create forks
  4. Block opponent forks (with refined logic)
  5. Take center
  6. Take opposite corner
  7. Take empty corner
  8. Take empty side
* Designed to **never lose**, only win or draw
* Verified through thousands of simulation games vs AI that exclusively plays random valid moves

#### MiniMaxAIPlayer

* Fully implemented recursive **MiniMax algorithm**
* Explores future game states to select optimal moves
* Uses score-based evaluation for win, loss, and tie outcomes
* Operates on simulated board copies to avoid mutating real game state
* Produces optimal play regardless of opponent strategy (verified through thousands of simulation games vs AI that exclusively plays random valid moves)

---

## Testing and Verification

### Unit Tests

* Board initialization and empty-state correctness
* Win detection across rows, columns, and diagonals
* Tie detection on full boards with no winner
* Validation that no AI overwrites occupied cells

### AI Behavior Tests

* Deterministic tests for:

  * Center selection
  * Immediate wins
  * Immediate blocks
* **Heavy simulation testing (1000+ games per matchup)**:

  * Unbeatable vs Unbeatable → always ties
  * Unbeatable vs Regular → Unbeatable never loses
  * Unbeatable vs Random → Unbeatable never loses
  * MiniMax vs any AI → Similarly optimal outcomes

When rare failures occurred during simulation, I enhanced the test harness to:

* Print the final board
* Replay the game move-by-move
  This debugging approach directly led to identifying and fixing subtle fork-handling and heuristic-ordering bugs.

---

## Design Decisions

* Used **inheritance and virtual functions** to unify all players under a single interface
* Centralized shared AI utilities in the `AIPlayer` base class
* Implemented Unbeatable AI *without minimax* to demonstrate manual game-theoretic reasoning
* Implemented MiniMax AI separately to contrast heuristic-based and search-based approaches
* Prioritized correctness, clarity, and testability over premature optimization

---

## Challenges Faced

* Correctly handling complex **fork scenarios**, especially involving opposite corners
* Avoiding duplicated logic across multiple AI implementations
* Debugging extremely rare losses that only appeared after hundreds of games
* Managing recursive logic and board copying in MiniMax without unintended side effects

---

## What I Learned

* How to design and evolve a polymorphic class hierarchy safely
* The importance of **stress testing**, not just simple unit tests
* How subtle heuristic mistakes can lead to rare but catastrophic failures
* How to debug AI decision-making using replay-based diagnostics
* The practical differences between heuristic AI and search-based AI

---

## Time Spent (Approximate)

| Task                                     | Hours         |
| ---------------------------------------- | ------------- |
| Initial design & setup                   | 4             |
| Core gameplay implementation             | 5             |
| Regular AI implementation                | 4             |
| Unbeatable AI implementation & debugging | 10            |
| MiniMax AI implementation                | 5             |
| Testing & simulations                    | 5             |
| Documentation & reflection               | 2             |
| **Total**                                | **~35 hours** |