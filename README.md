# TicTacToe AI — Final Project Submission (CIS 25)

A C++ console Tic-Tac-Toe game with multiple player types:
- Human player (keyboard input)
- Regular AI (simple strategy)
- Unbeatable AI (perfect-play rules)
- MiniMax AI (minimax search)

---

## How to Run

### Option A: CLion
1. Open the project folder in CLion.
2. Choose the **FinalProject** target.
3. Build + Run.

### Option B: Command Line (CMake)
From your build directory (example: `cmake-build-debug/`):

```bash
cmake ..
cmake --build .
./FinalProject
```

---

## How to Play (Controls)

When prompted for a move, you can use either:

### Numpad-style numbers
```
7 | 8 | 9
--+---+--
4 | 5 | 6
--+---+--
1 | 2 | 3
```

### OR “WASD-style” letters (case-insensitive)
```
Q | W | E      maps to      7 | 8 | 9
--+---+--                   --+---+--
A | S | D      maps to      4 | 5 | 6
--+---+--                   --+---+--
Z | X | C      maps to      1 | 2 | 3
```

---

## Implemented Features

### Board System
- 3×3 grid stored and managed by `Board`
- Valid move detection (`isValidMove`)
- Apply move (`applyMove`)
- Win detection (`winCheck`)
- Tie detection (`tieCheck`)
- Console rendering (`display`)

### Game Loop / Controller
- Menu-driven `TicTacToe::run()` loop
- Player selection (Human / Regular AI / Unbeatable AI / MiniMax AI)
- Alternating turns, win/tie detection, and cleanup

### AI Players
- **RegularAIPlayer**
  - Takes center if available
  - Plays an immediate winning move if possible
  - Blocks an opponent’s immediate winning move if needed
  - Otherwise chooses a random valid move

- **UnbeatableAIPlayer**
  - Implements the classic “perfect play” rule ordering (win, block, fork logic, center, opposite corner, corner, edge)
  - Verified by simulation testing that it never loses against random or Regular AI

- **MiniMaxAIPlayer**
  - Uses minimax search to select optimal moves
  - Designed to be unbeatable (win or tie with perfect play)

---

## Tests

### Board Tests
- Test file: `test_board.cpp`
- Executable: `board_tests`

Run:
```bash
ctest --verbose
```
(or run `board_tests` directly inside CLion)

### AI Tests (including simulations)
- Test file: `test_ai.cpp`
- Executable: `ai_tests`
- Includes both small deterministic tests and heavy simulations.

Run directly:
```bash
./ai_tests
```

---

## Repository Structure (Typical)

- `main.cpp` — program entry
- `TicTacToe.*` — menu + game loop
- `Board.*` — board state and rules
- `Player.*` — base class for players
- `HumanPlayer.*` — human input handling
- `AIPlayer.*` — shared AI helpers
- `RegularAIPlayer.*` — regular AI strategy
- `UnbeatableAIPlayer.*` — perfect-play rules
- `MiniMaxAIPlayer.*` — minimax AI
- `test_board.cpp` — board unit tests
- `test_ai.cpp` — AI tests + simulations
- `docs/` — checkpoint documentation (tests + reflections)

---

## Current Status

**Implemented Features**:
- ✅ Feature 1: Board system (moves, win/tie detection, display)
- ✅ Feature 2: Player system (Human + AI subclasses)
- ✅ Feature 3: Regular AI strategy
- ✅ Feature 4: Unbeatable AI strategy
- ✅ Feature 5: MiniMax AI strategy
- ✅ Feature 6: Automated tests (Board + AI test suite)

**In Progress**:
- ⏳ (None)

---

## Author
Matthew Lewis — CIS 25 Final Project