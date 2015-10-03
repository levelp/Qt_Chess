Feature: Knight Movement Rules
  As a chess game
  I need to validate knight movements
  So that knights move in L-shapes according to chess rules

  Scenario: Knight can move 2 up 1 right
    Given a chess board with white KNIGHT at [4,4]
    When I get available moves for the knight
    Then the move list should contain [2,5]

  Scenario: Knight can move 2 up 1 left
    Given a chess board with white KNIGHT at [4,4]
    When I get available moves for the knight
    Then the move list should contain [2,3]

  Scenario: Knight can move 1 up 2 right
    Given a chess board with white KNIGHT at [4,4]
    When I get available moves for the knight
    Then the move list should contain [3,6]

  Scenario: Knight can move 1 up 2 left
    Given a chess board with white KNIGHT at [4,4]
    When I get available moves for the knight
    Then the move list should contain [3,2]

  Scenario: Knight can move 2 down 1 right
    Given a chess board with white KNIGHT at [4,4]
    When I get available moves for the knight
    Then the move list should contain [6,5]

  Scenario: Knight can move 2 down 1 left
    Given a chess board with white KNIGHT at [4,4]
    When I get available moves for the knight
    Then the move list should contain [6,3]

  Scenario: Knight can move 1 down 2 right
    Given a chess board with white KNIGHT at [4,4]
    When I get available moves for the knight
    Then the move list should contain [5,6]

  Scenario: Knight can move 1 down 2 left
    Given a chess board with white KNIGHT at [4,4]
    When I get available moves for the knight
    Then the move list should contain [5,2]

  Scenario: Knight in center has 8 possible moves
    Given a chess board with white KNIGHT at [4,4]
    When I get available moves for the knight
    Then the move list should have exactly 8 moves

  Scenario: Knight can jump over pieces
    Given a chess board with white KNIGHT at [4,4]
    And a white PAWN at [3,4]
    And a black PAWN at [4,5]
    When I get available moves for the knight
    Then the move list should still have 8 moves

  Scenario: Knight cannot move to square with own piece
    Given a chess board with white KNIGHT at [4,4]
    And a white PAWN at [2,5]
    When I get available moves for the knight
    Then the move list should not contain [2,5]
    And the move list should have exactly 7 moves

  Scenario: Knight can capture opponent piece
    Given a chess board with white KNIGHT at [4,4]
    And a black PAWN at [2,5]
    When I get available moves for the knight
    Then the move list should contain [2,5] with ATTACK status

  Scenario: Knight in corner has limited moves
    Given a chess board with white KNIGHT at [0,0]
    When I get available moves for the knight
    Then the move list should have exactly 2 moves
    And the move list should contain [1,2]
    And the move list should contain [2,1]

  Scenario: Knight on edge has limited moves
    Given a chess board with white KNIGHT at [0,4]
    When I get available moves for the knight
    Then the move list should have at most 4 moves

  Scenario: Knight move out of bounds is filtered
    Given a chess board with white KNIGHT at [1,1]
    When I get available moves for the knight
    Then the move list should not contain any cell with negative coordinates
    And all moves should be within board boundaries

  Scenario: Knight near corner avoids out of bounds
    Given a chess board with white KNIGHT at [7,7]
    When I get available moves for the knight
    Then the move list should have exactly 2 moves
    And all moves should have row less than 8
    And all moves should have column less than 8
