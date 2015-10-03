Feature: Rook Movement Rules
  As a chess game
  I need to validate rook movements
  So that rooks move according to chess rules

  Scenario: Rook moves right along rank
    Given a chess board with white ROOK at [4,2]
    When I get available moves for the rook
    Then the move list should contain [4,3]
    And the move list should contain [4,4]
    And the move list should contain [4,5]
    And the move list should contain [4,6]
    And the move list should contain [4,7]

  Scenario: Rook moves left along rank
    Given a chess board with white ROOK at [4,5]
    When I get available moves for the rook
    Then the move list should contain [4,4]
    And the move list should contain [4,3]
    And the move list should contain [4,2]
    And the move list should contain [4,1]
    And the move list should contain [4,0]

  Scenario: Rook moves up along file
    Given a chess board with white ROOK at [4,3]
    When I get available moves for the rook
    Then the move list should contain [3,3]
    And the move list should contain [2,3]
    And the move list should contain [1,3]
    And the move list should contain [0,3]

  Scenario: Rook moves down along file
    Given a chess board with white ROOK at [3,3]
    When I get available moves for the rook
    Then the move list should contain [4,3]
    And the move list should contain [5,3]
    And the move list should contain [6,3]
    And the move list should contain [7,3]

  Scenario: Rook stops before own piece horizontally
    Given a chess board with white ROOK at [4,2]
    And a white KNIGHT at [4,5]
    When I get available moves for the rook
    Then the move list should contain [4,3]
    And the move list should contain [4,4]
    And the move list should not contain [4,5]
    And the move list should not contain [4,6]

  Scenario: Rook can capture opponent piece horizontally
    Given a chess board with white ROOK at [4,2]
    And a black KNIGHT at [4,5]
    When I get available moves for the rook
    Then the move list should contain [4,3]
    And the move list should contain [4,4]
    And the move list should contain [4,5] with ATTACK status
    And the move list should not contain [4,6]

  Scenario: Rook stops before own piece vertically
    Given a chess board with white ROOK at [4,3]
    And a white PAWN at [2,3]
    When I get available moves for the rook
    Then the move list should contain [3,3]
    And the move list should not contain [2,3]
    And the move list should not contain [1,3]

  Scenario: Rook can capture opponent piece vertically
    Given a chess board with white ROOK at [4,3]
    And a black PAWN at [2,3]
    When I get available moves for the rook
    Then the move list should contain [3,3]
    And the move list should contain [2,3] with ATTACK status
    And the move list should not contain [1,3]

  Scenario: Rook cannot jump over pieces
    Given a chess board with white ROOK at [4,2]
    And a white PAWN at [4,3]
    And an empty cell at [4,4]
    When I get available moves for the rook
    Then the move list should not contain [4,4]
    And the move list should not contain [4,5]

  Scenario: Rook on corner has two directions
    Given a chess board with white ROOK at [0,0]
    When I get available moves for the rook
    Then all moves should be in row 0 or column 0
    And the move list should have at least 14 moves

  Scenario: Rook in center has maximum moves
    Given a chess board with white ROOK at [4,4]
    When I get available moves for the rook
    Then the move list should have exactly 14 moves
