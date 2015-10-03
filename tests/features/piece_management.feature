Feature: Chess Piece Management
  As a chess game
  I need to manage individual chess pieces
  So that I can track their position, type, and state

  Scenario: Create white pawn at starting position
    Given a chess board
    When I create a white PAWN at row 6 column 0
    Then the piece should have side WHITE
    And the piece should have type PAWN
    And the piece should be at row 6
    And the piece should be at column 0

  Scenario: Create black rook at starting position
    Given a chess board
    When I create a black ROOK at row 0 column 0
    Then the piece should have side BLACK
    And the piece should have type ROOK
    And the piece should be at row 0
    And the piece should be at column 0

  Scenario: Update piece position
    Given a chess board
    And a white KNIGHT at row 7 column 1
    When I set the piece row to 5
    And I set the piece column to 2
    Then the piece should be at row 5
    And the piece should be at column 2

  Scenario: Track piece turn state
    Given a chess board
    And a white PAWN at row 6 column 4
    When I set the piece turn to 1
    Then the piece turn should be 1

  Scenario: Assign unique piece IDs
    Given a chess board
    When I create 32 pieces on the board
    Then all pieces should have unique IDs

  Scenario: Align piece to grid coordinates
    Given a chess board
    And a white QUEEN at row 3 column 4
    When I align the piece to grid
    Then the piece x position should be 200
    And the piece y position should be 150

  Scenario: Get piece type
    Given a chess board
    And a black BISHOP at row 0 column 2
    When I get the piece type
    Then the type should be BISHOP

  Scenario: Get piece side
    Given a chess board
    And a white KING at row 7 column 4
    When I get the piece side
    Then the side should be WHITE
