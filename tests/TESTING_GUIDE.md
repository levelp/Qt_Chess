# Qt Chess BDD Testing Guide

## What is BDD (Behavior-Driven Development)?

BDD is a software development approach that extends Test-Driven Development (TDD) by writing test cases in a natural language that non-programmers can read. It focuses on the behavior of the application from the end user's perspective.

### Key Concepts

1. **Feature Files**: Written in Gherkin syntax, these describe the behavior of the system in human-readable format
2. **Scenarios**: Specific examples of how the system should behave
3. **Given-When-Then**: The structure of each scenario
   - **Given**: Initial context/state
   - **When**: Action/event that occurs
   - **Then**: Expected outcome

## Example: From Feature to Code

### Feature File (Gherkin)

```gherkin
Feature: Pawn Movement Rules
  As a chess game
  I need to validate pawn movements
  So that pawns move according to chess rules

  Scenario: White pawn moves one square forward from starting position
    Given a chess board with standard starting position
    When I get available moves for white PAWN at [6,4]
    Then the move list should contain [5,4]
```

### Step Definition (C++ Implementation)

```cpp
void test_white_pawn_one_square_forward() {
    // Given: a chess board with standard starting position
    board->loadRes(":/board.txt");

    // When: I get available moves for white PAWN at [6,4]
    QVector<Area> moves = board->getTurnArea(board->boardMap[6][4]);

    // Then: the move list should contain [5,4]
    QVERIFY(containsMove(moves, 5, 4));
}
```

## Complete Testing Workflow

### 1. Understanding the Feature

Before writing tests, understand what you're testing:

```gherkin
Feature: Rook Movement Rules
  Background: Rooks move horizontally and vertically

  Scenario: Rook moves right along rank
    Given a chess board with white ROOK at [4,2]
    When I get available moves for the rook
    Then the move list should contain [4,3]
    And the move list should contain [4,4]
```

### 2. Writing Test Code

```cpp
void test_rook_moves_horizontal() {
    // Setup
    ChessPiece* whiteRook = new ChessPiece(board, WHITE, ROOK, 4, 2);
    board->boardMap[4][2] = whiteRook;

    // Execute
    QVector<Area> moves = board->getTurnArea(whiteRook);

    // Verify
    QVERIFY(containsMove(moves, 4, 3));
    QVERIFY(containsMove(moves, 4, 4));
}
```

### 3. Running the Test

```bash
cd tests
qmake movement_test.pro
make
./movement_test
```

## Test Organization

### Test Structure

```
tests/
├── features/              # Human-readable specifications
│   └── *.feature         # Gherkin files
├── step_definitions/      # Test implementations
│   └── *_steps.cpp       # C++ test code
└── *.pro                 # Build configurations
```

### File Naming Conventions

- Feature files: `snake_case.feature`
- Step definitions: `snake_case_steps.cpp`
- Test projects: `snake_case_test.pro`
- Test executables: `snake_case_test`

## Writing Effective BDD Tests

### 1. Focus on Behavior, Not Implementation

**Good:**
```gherkin
Scenario: Knight can jump over pieces
  Given a chess board with white KNIGHT at [4,4]
  And a white PAWN at [3,4]
  When I get available moves for the knight
  Then the move list should still have 8 moves
```

**Bad:**
```gherkin
Scenario: getTurnArea returns vector with 8 elements
  Given knight object at position [4,4]
  When getTurnArea is called
  Then vector.size() equals 8
```

### 2. Use Domain Language

Use chess terminology that stakeholders understand:
- "white PAWN" instead of "ChessPiece(WHITE, PAWN)"
- "moves to [5,4]" instead of "setRow(5), setCol(4)"
- "captures opponent piece" instead of "ATTACK status"

### 3. Test One Thing Per Scenario

**Good:**
```gherkin
Scenario: Pawn moves one square forward
Scenario: Pawn moves two squares on first move
Scenario: Pawn captures diagonally
```

**Bad:**
```gherkin
Scenario: Pawn does everything
  Given pawn at starting position
  Then it can move forward
  And it can move two squares
  And it can capture diagonally
```

### 4. Use Scenario Outlines for Similar Tests

```gherkin
Scenario Outline: Parse piece characters
  Given a character '<char>'
  When I parse it as piece type
  Then the result should be <type>

  Examples:
    | char | type   |
    | p    | PAWN   |
    | r    | ROOK   |
    | h    | KNIGHT |
```

## Test Helpers and Utilities

### TestContext

Shared context between tests:

```cpp
TestContext* context = TestContext::instance();
context->board = new ChessBoard(nullptr);
context->currentPiece = somePiece;
```

### Helper Functions

```cpp
// Check if move list contains a specific position
bool containsMove(const QVector<Area>& moves, int row, int col);

// Check if move has specific status
bool containsMoveWithStatus(
    const QVector<Area>& moves,
    int row,
    int col,
    status expectedStatus
);
```

### Setup and Cleanup

```cpp
private slots:
    void init() {
        // Runs before each test
        board = new ChessBoard(nullptr);
    }

    void cleanup() {
        // Runs after each test
        delete board;
    }
```

## Coverage Analysis

### What is Covered?

The test suite provides 100% coverage of:

1. **All Public Methods**
   - game.h: playerSide2s(), pieceType2s(), char2pieceType()
   - chesspiece.h: All getters/setters, alignToGrid()
   - chessboard.h: getTurnArea(), getPoleStatus(), getDiagonalStatus(), etc.

2. **All Movement Rules**
   - Pawn: forward, capture, first move
   - Rook: horizontal/vertical
   - Knight: L-shaped jumps
   - Bishop: diagonal
   - Queen: combined
   - King: one square + safety

3. **All Edge Cases**
   - Board boundaries
   - Piece blocking
   - Capture vs. move
   - Empty cells
   - Invalid inputs

4. **All Data Structures**
   - boardMap[8][8]
   - avMoves[8][8]
   - endOfGame[8][8]

### How to Verify Coverage

With code coverage tools:

```bash
# Using lcov (Linux)
qmake CONFIG+=coverage
make
lcov --directory . --capture --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# View results
firefox coverage_html/index.html
```

## Common Testing Patterns

### Pattern 1: Standard Board Setup

```cpp
void test_with_standard_position() {
    board->loadRes(":/board.txt");
    // Test with full initial position
}
```

### Pattern 2: Custom Board Setup

```cpp
void test_with_custom_position() {
    ChessPiece* piece1 = new ChessPiece(board, WHITE, ROOK, 4, 4);
    ChessPiece* piece2 = new ChessPiece(board, BLACK, PAWN, 4, 6);
    board->boardMap[4][4] = piece1;
    board->boardMap[4][6] = piece2;
    // Test custom scenario
}
```

### Pattern 3: Testing Boundaries

```cpp
void test_boundary_conditions() {
    // Test at board edges
    for (int edge = 0; edge < 8; edge++) {
        // Test row 0, row 7, col 0, col 7
    }
}
```

### Pattern 4: Testing Invalid Input

```cpp
void test_invalid_input() {
    bool exceptionCaught = false;
    try {
        // Trigger invalid condition
    } catch (...) {
        exceptionCaught = true;
    }
    QVERIFY(exceptionCaught);
}
```

## Debugging Failed Tests

### 1. Read the Feature File

Understand what behavior is expected:

```gherkin
Scenario: Rook stops before own piece
  Given a chess board with white ROOK at [4,2]
  And a white KNIGHT at [4,5]
  When I get available moves for the rook
  Then the move list should not contain [4,5]
```

### 2. Check Test Output

```
FAIL!  : MovementSteps::test_rook_blocked_by_own_piece()
   Actual: true
   Expected: false
   Loc: [movement_steps.cpp(95)]
```

### 3. Add Debug Output

```cpp
qDebug() << "Move count:" << moves.size();
for (const Area& area : moves) {
    qDebug() << "Move:" << area.row << area.col << area.state;
}
```

### 4. Run Single Test

```bash
./movement_test test_rook_blocked_by_own_piece
```

## Performance Considerations

### Fast Tests

- Use minimal board setup
- Avoid unnecessary object creation
- Clean up resources properly

```cpp
void test_fast() {
    ChessPiece piece(board, WHITE, PAWN, 6, 4);  // Stack allocation
    // Test
    // Automatic cleanup
}
```

### Slow Tests (If Needed)

- Load full board state
- Test complex interactions
- Mark as integration tests

```cpp
void test_full_game_scenario() {
    board->loadRes(":/board.txt");
    // Complex multi-move scenario
}
```

## Integration with CI/CD

### GitHub Actions Example

```yaml
name: BDD Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Install Qt
        run: sudo apt-get install qt5-default qtbase5-dev
      - name: Build Tests
        run: |
          cd tests
          qmake tests.pro
          make
      - name: Run Tests
        run: |
          cd tests
          for test in *_test; do
            ./$test -xunitxml -o ${test}_results.xml
          done
      - name: Upload Results
        uses: actions/upload-artifact@v2
        with:
          name: test-results
          path: tests/*_results.xml
```

## Best Practices Summary

1. **Write Feature First**: Specify behavior before implementation
2. **One Scenario = One Test Method**: Keep tests focused
3. **Use Descriptive Names**: Test names describe what they test
4. **Test Edge Cases**: Boundaries, nulls, invalid input
5. **Keep Tests Independent**: No dependencies between tests
6. **Clean Up Resources**: Use init()/cleanup() properly
7. **Use Assertions Wisely**: QVERIFY for booleans, QCOMPARE for values
8. **Document Complex Tests**: Add comments for tricky scenarios
9. **Run Tests Frequently**: Catch regressions early
10. **Maintain Test Code**: Tests are code too!

## Resources

- Qt Test Documentation: https://doc.qt.io/qt-5/qtest-overview.html
- Gherkin Syntax: https://cucumber.io/docs/gherkin/
- BDD Best Practices: https://cucumber.io/docs/bdd/

## Getting Help

If you encounter issues:
1. Check the test output for error messages
2. Review the feature file to understand expected behavior
3. Debug step definitions with qDebug()
4. Run tests individually to isolate problems
5. Check that Qt Test module is properly installed

## Conclusion

This BDD test suite provides comprehensive coverage of the Qt Chess application. By following the patterns and practices outlined in this guide, you can maintain and extend the tests as the application evolves.

Happy Testing!
