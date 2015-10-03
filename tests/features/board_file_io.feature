Feature: Board Loading from Files
  As a chess game
  I need to load board configurations from files
  So that games can be initialized or saved/loaded

  Scenario: Load standard starting position correctly
    Given an empty chess board
    When I load board from "data/board.txt"
    Then the board should have 32 pieces
    And all pieces should be in starting positions

  Scenario: Parse uppercase letters as white pieces
    Given a file with content "P" at position [6,0]
    When I load the board from this file
    Then position [6,0] should have a white PAWN

  Scenario: Parse lowercase letters as black pieces
    Given a file with content "p" at position [1,0]
    When I load the board from this file
    Then position [1,0] should have a black PAWN

  Scenario: Parse 'r' as black ROOK
    Given a file with content "r" at position [0,0]
    When I load the board from this file
    Then position [0,0] should have a black ROOK

  Scenario: Parse 'h' as black KNIGHT
    Given a file with content "h" at position [0,1]
    When I load the board from this file
    Then position [0,1] should have a black KNIGHT

  Scenario: Parse 'b' as black BISHOP
    Given a file with content "b" at position [0,2]
    When I load the board from this file
    Then position [0,2] should have a black BISHOP

  Scenario: Parse 'q' as black QUEEN
    Given a file with content "q" at position [0,3]
    When I load the board from this file
    Then position [0,3] should have a black QUEEN

  Scenario: Parse 'k' as black KING
    Given a file with content "k" at position [0,4]
    When I load the board from this file
    Then position [0,4] should have a black KING

  Scenario: Parse underscore as empty cell
    Given a file with content "_" at position [4,4]
    When I load the board from this file
    Then position [4,4] should be empty

  Scenario: Load from Qt resource file successfully
    Given an empty chess board
    When I load board from resource ":/board.txt"
    Then the board should be initialized correctly
    And all pieces should be present

  Scenario: Handle file with full 8x8 grid
    Given a file with 8 rows and 8 columns
    When I load the board from this file
    Then all 64 cells should be processed
    And piece positions should match file content

  Scenario: Parse mixed case board configuration
    Given a file with both uppercase and lowercase pieces
    When I load the board from this file
    Then white pieces should be from uppercase letters
    And black pieces should be from lowercase letters

  Scenario: Board state after loading matches file
    Given a file representing mid-game position
    When I load the board from this file
    Then the board map should exactly match file configuration
    And piece types should be correct
    And piece colors should be correct

  Scenario: Load clears previous board state
    Given a chess board with existing pieces
    When I load a new board configuration from file
    Then previous pieces should be removed
    And only new pieces from file should be present
