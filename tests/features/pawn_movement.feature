Feature: Pawn Movement Rules
  As a chess game
  I need to validate pawn movements
  So that pawns move according to chess rules

  Scenario: White pawn moves one square forward from starting position
    Given a chess board with standard starting position
    When I get available moves for white PAWN at [6,4]
    Then the move list should contain [5,4]

  Scenario: White pawn moves two squares on first move
    Given a chess board with standard starting position
    When I get available moves for white PAWN at [6,4]
    Then the move list should contain [4,4]

  Scenario: White pawn cannot move two squares on second move
    Given a chess board with white PAWN at [5,4] with turn=1
    When I get available moves for the pawn
    Then the move list should contain [4,4]
    And the move list should not contain [3,4]

  Scenario: Black pawn moves one square forward from starting position
    Given a chess board with standard starting position
    When I get available moves for black PAWN at [1,4]
    Then the move list should contain [2,4]

  Scenario: Black pawn moves two squares on first move
    Given a chess board with standard starting position
    When I get available moves for black PAWN at [1,4]
    Then the move list should contain [3,4]

  Scenario: Pawn cannot move forward when piece blocks
    Given a chess board with white PAWN at [5,4]
    And a white KNIGHT at [4,4]
    When I get available moves for white PAWN at [5,4]
    Then the move list should be empty

  Scenario: White pawn can capture diagonally forward-left
    Given a chess board with white PAWN at [5,4]
    And a black PAWN at [4,3]
    When I get available moves for white PAWN at [5,4]
    Then the move list should contain [4,3] with ATTACK status

  Scenario: White pawn can capture diagonally forward-right
    Given a chess board with white PAWN at [5,4]
    And a black PAWN at [4,5]
    When I get available moves for white PAWN at [5,4]
    Then the move list should contain [4,5] with ATTACK status

  Scenario: Black pawn can capture diagonally forward-left
    Given a chess board with black PAWN at [3,4]
    And a white PAWN at [4,3]
    When I get available moves for black PAWN at [3,4]
    Then the move list should contain [4,3] with ATTACK status

  Scenario: Black pawn can capture diagonally forward-right
    Given a chess board with black PAWN at [3,4]
    And a white PAWN at [4,5]
    When I get available moves for black PAWN at [3,4]
    Then the move list should contain [4,5] with ATTACK status

  Scenario: Pawn cannot move diagonally without opponent piece
    Given a chess board with white PAWN at [5,4]
    When I get available moves for white PAWN at [5,4]
    Then the move list should not contain [4,3]
    And the move list should not contain [4,5]

  Scenario: White pawn at left edge cannot capture off board
    Given a chess board with white PAWN at [5,0]
    And a black PAWN at [4,1]
    When I get available moves for white PAWN at [5,0]
    Then the move list should contain [4,1] with ATTACK status
    And the move list should not contain any cell with column -1

  Scenario: White pawn at right edge cannot capture off board
    Given a chess board with white PAWN at [5,7]
    And a black PAWN at [4,6]
    When I get available moves for white PAWN at [5,7]
    Then the move list should contain [4,6] with ATTACK status
    And the move list should not contain any cell with column 8

  Scenario: Pawn cannot capture own piece
    Given a chess board with white PAWN at [5,4]
    And a white KNIGHT at [4,3]
    When I get available moves for white PAWN at [5,4]
    Then the move list should not contain [4,3]
