Feature: Diagonal Movement Calculation
  As a chess game
  I need to calculate diagonal movements correctly
  So that bishops and queens can move properly

  Scenario: Get diagonal moves up-right direction
    Given a chess board with no pieces
    When I calculate diagonal moves from [4,4] up-right for WHITE
    Then the result should contain [3,5]
    And the result should contain [2,6]
    And the result should contain [1,7]
    And the result should have exactly 3 moves

  Scenario: Get diagonal moves up-left direction
    Given a chess board with no pieces
    When I calculate diagonal moves from [4,4] up-left for WHITE
    Then the result should contain [3,3]
    And the result should contain [2,2]
    And the result should contain [1,1]
    And the result should contain [0,0]
    And the result should have exactly 4 moves

  Scenario: Get diagonal moves down-right direction
    Given a chess board with no pieces
    When I calculate diagonal moves from [4,4] down-right for WHITE
    Then the result should contain [5,5]
    And the result should contain [6,6]
    And the result should contain [7,7]
    And the result should have exactly 3 moves

  Scenario: Get diagonal moves down-left direction
    Given a chess board with no pieces
    When I calculate diagonal moves from [4,4] down-left for WHITE
    Then the result should contain [5,3]
    And the result should contain [6,2]
    And the result should contain [7,1]
    And the result should have exactly 3 moves

  Scenario: Stop at board boundary
    Given a chess board with no pieces
    When I calculate diagonal moves from [1,1] up-left for WHITE
    Then the result should contain [0,0]
    And the result should have exactly 1 move
    And all moves should be within board boundaries

  Scenario: Stop before own piece diagonally
    Given a chess board with white BISHOP at [4,4]
    And a white PAWN at [2,6]
    When I calculate diagonal moves from [4,4] up-right for WHITE
    Then the result should contain [3,5]
    And the result should not contain [2,6]
    And the result should not contain [1,7]

  Scenario: Include capture option for opponent piece
    Given a chess board with white BISHOP at [4,4]
    And a black PAWN at [2,6]
    When I calculate diagonal moves from [4,4] up-right for WHITE
    Then the result should contain [3,5] with ENABLE status
    And the result should contain [2,6] with ATTACK status
    And the result should not contain [1,7]

  Scenario: Diagonal from corner has single direction
    Given a chess board with no pieces
    When I calculate diagonal moves from [0,0] down-right for WHITE
    Then all moves should be on main diagonal
    And the result should have exactly 7 moves

  Scenario: All diagonal moves marked with correct status
    Given a chess board with white BISHOP at [4,4]
    And a black PAWN at [6,6]
    When I calculate diagonal moves from [4,4] down-right for WHITE
    Then [5,5] should have ENABLE status
    And [6,6] should have ATTACK status
