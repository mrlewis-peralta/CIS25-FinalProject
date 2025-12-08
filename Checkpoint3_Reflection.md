# Checkpoint 3 Reflection

## 1. What you implemented
For my third feature, I implemented a MiniMax AI Player for TicTacToe. This AI uses the Minimax algorithm to evaluate possible move outcomes and select the best move for its symbol. This adds a alternative approach to the previously implemented Unbeatable AI.

## 2. Integration (with Features 1 and 2)
This feature integrates with my existing player/AI framework by extending the AIPlayer class and using the same Board interface for move validation and win/tie checks. The MiniMax AI appears as an additional selectable player type in the game setup menu, alongside my previous AI types. The overall gameplay flow remains unchanged, but now includes a more "algorithmic" "perfect play" option.

## 3. Challenges faced
The most challenging part of this feature was implementing a recursive Minimax solution that worked cleanly with my existing Board structure. I also had to ensure that the AI correctly handled terminal states (win/loss/tie) and that the player-creation/menu logic correctly supported the new option without breaking the earlier AI types.

## 4. What you learned
I learned how to structure a recursive decision algorithm in an object-oriented design and how to separate evaluation logic from move-selection logic. This also reinforced the importance of writing code that integrates cleanly into an existing class hierarchy.

## 5. Testing results
I extended the test I previously used for the Unbeatable AI.  The MiniMax played against Regular AI, Unbeatable AI, MiniMax AI, and random (valid) moves AI; both as player 1 and as player 2, 1000 times for each of these combinations/orderings.  The MiniMax AI never lost (and never beat the Unbeatable AI, nor an opposing MiniMax AI).

Playing 1000 times (each as Player 1 and Player 2) against the random valid moves AI ensures that both normal operation and edge cases are covered.

Overall, my tests indicate that the MiniMax AI behaves as expected and integrates correctly with my earlier features.

## 6. Overall Project Completion Progress
This checkpoint includes a new completion-progress assessment. :contentReference[oaicite:2]{index=2}

- **Percentage complete:** I estimate that I have completed about 100% of my original planned features.
- **Remaining planned features:** The features from my original plan that remain are: None
- **Scope commitment:** I am still committed to my original scope
- **Biggest remaining challenges:** Cleaning up code to be nicer?
- **On-track assessment:** I am already past the intended final submission date.

## 7. Time spent
Approximate time spent on this checkpoint: 3 hours
