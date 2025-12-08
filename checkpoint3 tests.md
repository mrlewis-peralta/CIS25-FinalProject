=== AI Tests (Regular, Unbeatable, MiniMax) ===

Test 1 (RegularAI): takes center on empty board... PASSED
Test 2 (RegularAI): takes immediate winning move... PASSED
Test 3 (UnbeatableAI): blocks opponent's winning move... PASSED
Test 4: AIs never overwrite occupied cells... PASSED

=== Heavy Unbeatable-AI Simulations ===

Simulation 1: Unbeatable vs Unbeatable (should always tie)... PASSED (1000 ties)
Simulation 2: Unbeatable (X) vs Regular (O)... PASSED (X wins: 833, ties: 167)
Simulation 3: Regular (X) vs Unbeatable (O)... PASSED (O wins: 54, ties: 946)
Simulation 4: Unbeatable (X) vs Random (O)... PASSED (X wins: 964, ties: 36)
Simulation 5: Random (X) vs Unbeatable (O)... PASSED (O wins: 851, ties: 149)

=== Heavy MiniMax-AI Simulations ===

Simulation 6: MiniMax (X) vs Random (O)... PASSED (X wins: 994, ties: 6)
Simulation 7: Random (X) vs MiniMax (O)... PASSED (O wins: 813, ties: 187)
Simulation 8: MiniMax (X) vs Regular (O)... PASSED (X wins: 0, ties: 1000)
Simulation 9: Regular (X) vs MiniMax (O)... PASSED (O wins: 64, ties: 936)
Simulation 10: MiniMax (X) vs Unbeatable (O)... PASSED (X wins: 0, ties: 1000)
Simulation 11: Unbeatable (X) vs MiniMax (O)... PASSED (O wins: 0, ties: 1000)

All AI tests passed!

Process finished with exit code 0
