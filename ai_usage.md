# AI-assisted changes

This log records AI-assisted code changes visible in this conversation. It may
not include work from other conversations or sessions.

**Difficulty scale:** Ratings are relative to this project: Low is a localized
change, Moderate involves nontrivial control flow or recursion, and High
coordinates multiple functions or move-processing steps.

## 2026-11-07 — Fix enemy AI movement

- **Input:** “std::vector<std::set<std::pair<int, int>>> set; ... enemy::moveEnemy(theSet, board, choosenSpotToMove, temp);”
- **Why:** The enemy turn was using mouse-driven handlers for an automatic move,
  and piece coordinates were stored in row-column order while move logic expects
  x-y order. Empty move sets could also lead to selecting an invalid destination.
- **Changes:** Added direct enemy move generation and application by source and
  destination square, corrected enemy coordinates, recorded the index of the
  piece with the most legal moves, and skipped turns with no legal moves. Enemy
  pieces now move toward increasing row indexes, promote on the far row, and
  enemy kings are rendered.
- **Verification:** The full C++ build and link succeeded, and `python3 run.py`
  completed successfully.
- **Difficulty:** High. The fix coordinated move generation, coordinate
  handling, destination selection, board updates, and promotion across files.

## 2026-11-07 — Prevent player king capture-path loop

- **Input:** “whenever the PlayerKing goes backwards, there is a chance that it
  gets stuck in an infite loop. it's probaly the recusrsion error or some
  infinite looping”
- **Why:** The player capture-removal routine guessed the previous jump square
  by iterating an unordered set. It could revisit squares and fail to make
  progress toward the starting square.
- **Changes:** Replaced that reconstruction loop in `src/player.cpp` with a
  bounded search that tracks visited landing squares and only follows jumps
  over enemy pieces.
- **Verification:** C++ syntax checks passed; a backward multi-jump regression
  test confirmed both captured pieces were removed.
- **Difficulty:** Moderate. The fix required making a recursive capture search
  terminate and follow valid landing squares.

## 2026-11-07 — Prevent enemy king capture-path loop

- **Input:** “look at enemy.cpp for that error now”
- **Why:** The enemy capture-removal routine had the same unordered-set path
  reconstruction loop, which could cycle while following a multi-jump path.
- **Changes:** Applied the corresponding bounded path search in
  `src/enemy.cpp`, following jumps over player pieces and tracking visited
  landing squares.
- **Verification:** C++ syntax checks passed; a backward multi-jump regression
  test for an enemy king confirmed both captured pieces were removed.
- **Difficulty:** Moderate. It applied the same recursive path-search reasoning
  to the enemy pieces and their capture targets.

## 2026-11-07 — Fix multi-jump capture reconstruction

- **Input:** “rewrite both functions with fixes”
- **Why:** The capture-removal routine received the destination as both the
  start and end position, so it could not traverse the completed jump path.
- **Changes:** Rewrote `RemoveCapturedPieces()` and `movePlayer()` in
  `src/player.cpp`, passed the selected piece coordinates as the start and the
  clicked landing square as the destination, and added backward traversal to
  remove captured pieces along a multi-jump sequence.
- **Verification:** Manual gameplay testing confirmed that single jumps and
  chained multi-jumps remove the captured pieces, update the board, and complete
  without errors.
- **Difficulty:** High. The fix coordinated move arguments, multi-jump path
  reconstruction, and removal of every captured piece.