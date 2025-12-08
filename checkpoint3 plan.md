# Checkpoint 3: Third Feature Plan

## Feature Name
MiniMax AI Player

## Description
This feature adds a new AI difficulty option that uses the Minimax algorithm to evaluate possible game states and choose the optimal move. The MiniMax AI will play perfectly in TicTacToe, guaranteeing a win when possible and otherwise forcing a tie against optimal opponents.

## Why This Feature?
I chose this feature because it builds directly on my existing AI framework from features 1 and 2 and adds a meaningful new level of decision-making complexity. It complements my Regular AI and Unbeatable AI by introducing a more formal algorithmic approach to game-solving, improving the overall depth and polish of the AI difficulty system.

## Classes Involved
- MiniMaxAIPlayer (implement core logic)
- AIPlayer (inherit shared AI behavior)
- Player (base interface)
- Board (used for move simulation and win/tie evaluation)
- TicTacToe (enable selection of MiniMax option and create the correct player type)
- main.cpp

## Expected User Workflow
When starting a new game, the user will select the type of Player 1 and Player 2. A new menu option will allow choosing “Minimax AI” as one of the player types. During gameplay, the MiniMax AI will automatically compute and place the best move on its turn.

## Estimated Time
3 hours
