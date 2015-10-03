Feature: King Movement Rules
  As a chess game
  I need to validate king movements
  So that kings move one square in any direction and avoid check

  Scenario: King moves one square in each direction
    Given a chess board with white KING at [4,4]
    And no pieces attacking [3,3], [3,4], [3,5], [4,3], [4,5], [5,3], [5,4], [5,5]
    When I get available moves for the king
    Then the move list should contain [3,3]
    And the move list should contain [3,4]
    And the move list should contain [3,5]
    And the move list should contain [4,3]
    And the move list should contain [4,5]
    And the move list should contain [5,3]
    And the move list should contain [5,4]
    And the move list should contain [5,5]

  Scenario: King in center has 8 possible moves when safe
    Given a chess board with white KING at [4,4]
    And no pieces attacking squares around [4,4]
    When I get available moves for the king
    Then the move list should have exactly 8 moves

  Scenario: King cannot move into check
    Given a chess board with white KING at [4,4]
    And a black ROOK at [0,5]
    When I get available moves for the king
    Then the move list should not contain [3,5]
    And the move list should not contain [4,5]
    And the move list should not contain [5,5]

  Scenario: King cannot move to square attacked by opponent pawn
    Given a chess board with white KING at [4,4]
    And a black PAWN at [2,4]
    When I get available moves for the king
    Then the move list should not contain [3,3]
    And the move list should not contain [3,5]

  Scenario: King cannot move to square attacked by opponent knight
    Given a chess board with white KING at [4,4]
    And a black KNIGHT at [1,3]
    When I get available moves for the king
    Then the move list should not contain [3,5]

  Scenario: King cannot capture own piece
    Given a chess board with white KING at [4,4]
    And a white PAWN at [3,4]
    When I get available moves for the king
    Then the move list should not contain [3,4]

  Scenario: King can capture opponent piece on safe square
    Given a chess board with white KING at [4,4]
    And a black PAWN at [3,4]
    And no other pieces attacking [3,4]
    When I get available moves for the king
    Then the move list should contain [3,4] with ATTACK status

  Scenario: King cannot capture protected opponent piece
    Given a chess board with white KING at [4,4]
    And a black PAWN at [3,4]
    And a black ROOK at [3,0]
    When I get available moves for the king
    Then the move list should not contain [3,4]

  Scenario: King at board corner has limited moves
    Given a chess board with white KING at [0,0]
    And no pieces attacking [0,1], [1,0], [1,1]
    When I get available moves for the king
    Then the move list should have exactly 3 moves
    And the move list should contain [0,1]
    And the move list should contain [1,0]
    And the move list should contain [1,1]

  Scenario: King at board edge has limited moves
    Given a chess board with white KING at [0,4]
    And no pieces attacking adjacent squares
    When I get available moves for the king
    Then the move list should have at most 5 moves

  Scenario: King surrounded by own pieces has no moves
    Given a chess board with white KING at [4,4]
    And white pieces at [3,3], [3,4], [3,5], [4,3], [4,5], [5,3], [5,4], [5,5]
    When I get available moves for the king
    Then the move list should be empty

  Scenario: King tracks turn for castling
    Given a chess board with white KING at [7,4]
    When the king has not moved yet
    Then the king turn should be 0

  Scenario: King turn updates after first move
    Given a chess board with white KING at [7,4]
    When the king moves to [7,5]
    Then the king turn should be 1
