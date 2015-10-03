Feature: Queen Movement Rules
  As a chess game
  I need to validate queen movements
  So that queens move like rooks and bishops combined

  Scenario: Queen moves horizontally like a rook
    Given a chess board with white QUEEN at [4,4]
    When I get available moves for the queen
    Then the move list should contain [4,0]
    And the move list should contain [4,1]
    And the move list should contain [4,2]
    And the move list should contain [4,3]
    And the move list should contain [4,5]
    And the move list should contain [4,6]
    And the move list should contain [4,7]

  Scenario: Queen moves vertically like a rook
    Given a chess board with white QUEEN at [4,4]
    When I get available moves for the queen
    Then the move list should contain [0,4]
    And the move list should contain [1,4]
    And the move list should contain [2,4]
    And the move list should contain [3,4]
    And the move list should contain [5,4]
    And the move list should contain [6,4]
    And the move list should contain [7,4]

  Scenario: Queen moves diagonally like a bishop
    Given a chess board with white QUEEN at [4,4]
    When I get available moves for the queen
    Then the move list should contain [3,3]
    And the move list should contain [2,2]
    And the move list should contain [1,1]
    And the move list should contain [0,0]
    And the move list should contain [5,5]
    And the move list should contain [6,6]
    And the move list should contain [7,7]

  Scenario: Queen in center has maximum moves
    Given a chess board with white QUEEN at [4,4]
    When I get available moves for the queen
    Then the move list should have exactly 27 moves

  Scenario: Queen stops before own piece in all directions
    Given a chess board with white QUEEN at [4,4]
    And a white PAWN at [4,6]
    And a white PAWN at [2,4]
    And a white PAWN at [6,6]
    When I get available moves for the queen
    Then the move list should not contain [4,6]
    And the move list should not contain [4,7]
    And the move list should not contain [2,4]
    And the move list should not contain [6,6]

  Scenario: Queen can capture opponent pieces in all directions
    Given a chess board with white QUEEN at [4,4]
    And a black PAWN at [4,6]
    And a black PAWN at [2,4]
    And a black PAWN at [6,6]
    When I get available moves for the queen
    Then the move list should contain [4,6] with ATTACK status
    And the move list should contain [2,4] with ATTACK status
    And the move list should contain [6,6] with ATTACK status

  Scenario: Queen cannot jump over pieces horizontally
    Given a chess board with white QUEEN at [4,2]
    And a white PAWN at [4,4]
    When I get available moves for the queen
    Then the move list should contain [4,3]
    And the move list should not contain [4,5]
    And the move list should not contain [4,6]

  Scenario: Queen cannot jump over pieces diagonally
    Given a chess board with white QUEEN at [4,4]
    And a white PAWN at [3,5]
    When I get available moves for the queen
    Then the move list should not contain [2,6]
    And the move list should not contain [1,7]

  Scenario: Queen on corner has limited moves
    Given a chess board with white QUEEN at [0,0]
    When I get available moves for the queen
    Then the move list should have exactly 21 moves

  Scenario: Queen combines rook and bishop movement patterns
    Given a chess board with white QUEEN at [3,3]
    When I get available moves for the queen
    Then the move list should include horizontal moves
    And the move list should include vertical moves
    And the move list should include diagonal moves
    And all move directions should be present
