cmake_minimum_required(VERSION 4.0)
project(FinalProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(FinalProject main.cpp
        TicTacToe.cpp
        TicTacToe.h
        Board.cpp
        Board.h
        Player.cpp
        Player.h
        HumanPlayer.cpp
        HumanPlayer.h
        AIPlayer.cpp
        AIPlayer.h
        RegularAIPlayer.cpp
        RegularAIPlayer.h
        UnbeatableAIPlayer.cpp
        UnbeatableAIPlayer.h
        MiniMaxAIPlayer.cpp
        MiniMaxAIPlayer.h
)

# --- Testing setup ---
enable_testing()

# Test executable for Board
add_executable(board_tests
        test_board.cpp
        Board.cpp
)

# === AI TESTS EXE ===
add_executable(ai_tests
        test_ai.cpp
        Board.cpp
        Player.cpp
        AIPlayer.cpp
        RegularAIPlayer.cpp
        UnbeatableAIPlayer.cpp
        HumanPlayer.cpp
        TicTacToe.cpp
        MiniMaxAIPlayer.cpp
)

# Register this test with CTest
# add_test(NAME BoardTests COMMAND board_tests)
add_test(NAME BoardTests COMMAND board_tests)