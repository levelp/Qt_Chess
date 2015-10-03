Feature: King Safety Determination
  As a chess game
  I need to identify squares attacked by opponent
  So that kings cannot move into check

  Scenario: Mark all squares attacked by opponent pawns
    Given a chess board with black PAWN at [3,4]
    When I calculate attacked squares for WHITE king
    Then square [4,3] should be marked as attacked
    And square [4,5] should be marked as attacked
    And square [4,4] should not be marked as attacked

  Scenario: Mark all squares attacked by opponent rook
    Given a chess board with black ROOK at [3,3]
    When I calculate attacked squares for WHITE king
    Then all squares in row 3 should be marked as attacked
    And all squares in column 3 should be marked as attacked

  Scenario: Mark all squares attacked by opponent knight
    Given a chess board with black KNIGHT at [4,4]
    When I calculate attacked squares for WHITE king
    Then square [2,3] should be marked as attacked
    And square [2,5] should be marked as attacked
    And square [3,2] should be marked as attacked
    And square [3,6] should be marked as attacked
    And square [5,2] should be marked as attacked
    And square [5,6] should be marked as attacked
    And square [6,3] should be marked as attacked
    And square [6,5] should be marked as attacked

  Scenario: Mark all squares attacked by opponent bishop
    Given a chess board with black BISHOP at [4,4]
    When I calculate attacked squares for WHITE king
    Then diagonal squares from [4,4] should be marked as attacked
    And non-diagonal squares should not be marked as attacked

  Scenario: Mark all squares attacked by opponent queen
    Given a chess board with black QUEEN at [4,4]
    When I calculate attacked squares for WHITE king
    Then all squares in row 4 should be marked as attacked
    And all squares in column 4 should be marked as attacked
    And diagonal squares from [4,4] should be marked as attacked

  Scenario: Mark all squares attacked by opponent king
    Given a chess board with black KING at [2,2]
    When I calculate attacked squares for WHITE king
    Then square [1,1] should be marked as attacked
    And square [1,2] should be marked as attacked
    And square [1,3] should be marked as attacked
    And square [2,1] should be marked as attacked
    And square [2,3] should be marked as attacked
    And square [3,1] should be marked as attacked
    And square [3,2] should be marked as attacked
    And square [3,3] should be marked as attacked

  Scenario: Identify safe squares for king
    Given a chess board with black ROOK at [0,0]
    When I calculate attacked squares for WHITE king
    Then square [5,5] should not be marked as attacked
    And square [4,4] should not be marked as attacked

  Scenario: Handle multiple attackers correctly
    Given a chess board with black ROOK at [0,0]
    And a black BISHOP at [7,7]
    When I calculate attacked squares for WHITE king
    Then square [0,4] should be marked as attacked
    And square [4,0] should be marked as attacked
    And square [4,4] should be marked as attacked
    And all attacked squares should be properly marked

  Scenario: Update attacked squares when pieces move
    Given a chess board with black ROOK at [0,0]
    And previously calculated attacked squares
    When the black ROOK moves to [0,4]
    And I recalculate attacked squares for WHITE king
    Then square [0,0] should not be marked as attacked
    And all squares in column 4 should be marked as attacked

  Scenario: King safety check blocks invalid moves
    Given a chess board with white KING at [4,4]
    And black ROOK at [0,5]
    When I get available moves for the king
    Then moves to column 5 should be excluded from available moves
