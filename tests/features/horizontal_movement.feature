Feature: Horizontal and Vertical Movement Calculation
  As a chess game
  I need to calculate horizontal and vertical movements correctly
  So that rooks and queens can move properly

  Scenario: Get horizontal moves to the right
    Given a chess board with no pieces
    When I calculate horizontal moves from [4,2] to right for WHITE
    Then the result should contain [4,3]
    And the result should contain [4,4]
    And the result should contain [4,5]
    And the result should contain [4,6]
    And the result should contain [4,7]
    And the result should have exactly 5 moves

  Scenario: Get horizontal moves to the left
    Given a chess board with no pieces
    When I calculate horizontal moves from [4,5] to left for WHITE
    Then the result should contain [4,4]
    And the result should contain [4,3]
    And the result should contain [4,2]
    And the result should contain [4,1]
    And the result should contain [4,0]
    And the result should have exactly 5 moves

  Scenario: Get vertical moves upward
    Given a chess board with no pieces
    When I calculate vertical moves from [5,3] upward for WHITE
    Then the result should contain [4,3]
    And the result should contain [3,3]
    And the result should contain [2,3]
    And the result should contain [1,3]
    And the result should contain [0,3]
    And the result should have exactly 5 moves

  Scenario: Get vertical moves downward
    Given a chess board with no pieces
    When I calculate vertical moves from [2,3] downward for WHITE
    Then the result should contain [3,3]
    And the result should contain [4,3]
    And the result should contain [5,3]
    And the result should contain [6,3]
    And the result should contain [7,3]
    And the result should have exactly 5 moves

  Scenario: Stop at board boundary horizontally
    Given a chess board with no pieces
    When I calculate horizontal moves from [4,6] to right for WHITE
    Then the result should contain [4,7]
    And the result should have exactly 1 move

  Scenario: Stop at board boundary vertically
    Given a chess board with no pieces
    When I calculate vertical moves from [6,3] downward for WHITE
    Then the result should contain [7,3]
    And the result should have exactly 1 move

  Scenario: Stop before own piece horizontally
    Given a chess board with white ROOK at [4,2]
    And a white PAWN at [4,5]
    When I calculate horizontal moves from [4,2] to right for WHITE
    Then the result should contain [4,3]
    And the result should contain [4,4]
    And the result should not contain [4,5]
    And the result should not contain [4,6]

  Scenario: Stop before own piece vertically
    Given a chess board with white ROOK at [5,3]
    And a white PAWN at [2,3]
    When I calculate vertical moves from [5,3] upward for WHITE
    Then the result should contain [4,3]
    And the result should contain [3,3]
    And the result should not contain [2,3]

  Scenario: Include capture option for opponent piece horizontally
    Given a chess board with white ROOK at [4,2]
    And a black PAWN at [4,5]
    When I calculate horizontal moves from [4,2] to right for WHITE
    Then the result should contain [4,3] with ENABLE status
    And the result should contain [4,4] with ENABLE status
    And the result should contain [4,5] with ATTACK status
    And the result should not contain [4,6]

  Scenario: Include capture option for opponent piece vertically
    Given a chess board with white ROOK at [5,3]
    And a black PAWN at [2,3]
    When I calculate vertical moves from [5,3] upward for WHITE
    Then the result should contain [4,3] with ENABLE status
    And the result should contain [3,3] with ENABLE status
    And the result should contain [2,3] with ATTACK status
    And the result should not contain [1,3]

  Scenario: Rook on edge calculates correctly
    Given a chess board with white ROOK at [0,4]
    When I calculate all horizontal and vertical moves for WHITE
    Then the result should have exactly 14 moves
    And all moves should be in row 0 or column 4
