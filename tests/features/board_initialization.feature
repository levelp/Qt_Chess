Feature: Chess Board Initialization
  As a chess game
  I need to initialize the board with pieces
  So that a standard game can begin

  Scenario: Load standard starting position from resource
    Given an empty chess board
    When I load the standard starting position from resource
    Then the board should have 32 pieces
    And row 0 should have black back rank pieces
    And row 1 should have 8 black pawns
    And rows 2 through 5 should be empty
    And row 6 should have 8 white pawns
    And row 7 should have white back rank pieces

  Scenario: Correct piece types in starting position
    Given a chess board with standard starting position
    Then position [0,0] should contain a black ROOK
    And position [0,1] should contain a black KNIGHT
    And position [0,2] should contain a black BISHOP
    And position [0,3] should contain a black QUEEN
    And position [0,4] should contain a black KING
    And position [0,5] should contain a black BISHOP
    And position [0,6] should contain a black KNIGHT
    And position [0,7] should contain a black ROOK

  Scenario: White back rank correct
    Given a chess board with standard starting position
    Then position [7,0] should contain a white ROOK
    And position [7,1] should contain a white KNIGHT
    And position [7,2] should contain a white BISHOP
    And position [7,3] should contain a white QUEEN
    And position [7,4] should contain a white KING
    And position [7,5] should contain a white BISHOP
    And position [7,6] should contain a white KNIGHT
    And position [7,7] should contain a white ROOK

  Scenario: All white pawns in correct position
    Given a chess board with standard starting position
    Then all pieces at row 6 should be white PAWNs
    And there should be 8 pieces at row 6

  Scenario: All black pawns in correct position
    Given a chess board with standard starting position
    Then all pieces at row 1 should be black PAWNs
    And there should be 8 pieces at row 1

  Scenario: Middle rows are empty
    Given a chess board with standard starting position
    Then row 2 should be completely empty
    And row 3 should be completely empty
    And row 4 should be completely empty
    And row 5 should be completely empty

  Scenario: Clear available moves resets highlighting
    Given a chess board with standard starting position
    And some cells are highlighted as available moves
    When I clear available moves
    Then no cells should be highlighted
