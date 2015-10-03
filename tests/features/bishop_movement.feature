Feature: Bishop Movement Rules
  As a chess game
  I need to validate bishop movements
  So that bishops move diagonally according to chess rules

  Scenario: Bishop moves diagonally up-right
    Given a chess board with white BISHOP at [4,4]
    When I get available moves for the bishop
    Then the move list should contain [3,5]
    And the move list should contain [2,6]
    And the move list should contain [1,7]

  Scenario: Bishop moves diagonally up-left
    Given a chess board with white BISHOP at [4,4]
    When I get available moves for the bishop
    Then the move list should contain [3,3]
    And the move list should contain [2,2]
    And the move list should contain [1,1]
    And the move list should contain [0,0]

  Scenario: Bishop moves diagonally down-right
    Given a chess board with white BISHOP at [4,4]
    When I get available moves for the bishop
    Then the move list should contain [5,5]
    And the move list should contain [6,6]
    And the move list should contain [7,7]

  Scenario: Bishop moves diagonally down-left
    Given a chess board with white BISHOP at [4,4]
    When I get available moves for the bishop
    Then the move list should contain [5,3]
    And the move list should contain [6,2]
    And the move list should contain [7,1]

  Scenario: Bishop in center has maximum diagonal moves
    Given a chess board with white BISHOP at [4,4]
    When I get available moves for the bishop
    Then the move list should have exactly 13 moves

  Scenario: Bishop stops before own piece
    Given a chess board with white BISHOP at [4,4]
    And a white PAWN at [2,6]
    When I get available moves for the bishop
    Then the move list should contain [3,5]
    And the move list should not contain [2,6]
    And the move list should not contain [1,7]

  Scenario: Bishop can capture opponent piece
    Given a chess board with white BISHOP at [4,4]
    And a black PAWN at [2,6]
    When I get available moves for the bishop
    Then the move list should contain [3,5]
    And the move list should contain [2,6] with ATTACK status
    And the move list should not contain [1,7]

  Scenario: Bishop cannot jump over pieces
    Given a chess board with white BISHOP at [4,4]
    And a white PAWN at [3,5]
    When I get available moves for the bishop
    Then the move list should not contain [2,6]
    And the move list should not contain [1,7]

  Scenario: Bishop on corner has limited moves
    Given a chess board with white BISHOP at [0,0]
    When I get available moves for the bishop
    Then the move list should have exactly 7 moves
    And all moves should be diagonal from [0,0]

  Scenario: Bishop on opposite corner
    Given a chess board with white BISHOP at [7,7]
    When I get available moves for the bishop
    Then the move list should have exactly 7 moves
    And all moves should be diagonal from [7,7]

  Scenario: Bishop blocked in all directions
    Given a chess board with white BISHOP at [4,4]
    And white pieces at [3,3], [3,5], [5,3], [5,5]
    When I get available moves for the bishop
    Then the move list should be empty

  Scenario: Bishop can capture multiple opponent pieces in different directions
    Given a chess board with white BISHOP at [4,4]
    And a black PAWN at [2,2]
    And a black PAWN at [6,6]
    When I get available moves for the bishop
    Then the move list should contain [2,2] with ATTACK status
    And the move list should contain [6,6] with ATTACK status
