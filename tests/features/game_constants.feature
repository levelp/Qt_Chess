Feature: Game Constants and Conversions
  As a chess game
  I need to convert between enums and strings
  So that pieces and players can be properly represented

  Scenario: Convert WHITE player side to string
    Given a player side of WHITE
    When I convert it to string
    Then the result should be "WHITE"

  Scenario: Convert BLACK player side to string
    Given a player side of BLACK
    When I convert it to string
    Then the result should be "BLACK"

  Scenario: Convert PAWN piece type to string
    Given a piece type of PAWN
    When I convert it to string
    Then the result should be "PAWN"

  Scenario: Convert ROOK piece type to string
    Given a piece type of ROOK
    When I convert it to string
    Then the result should be "ROOK"

  Scenario: Convert KNIGHT piece type to string
    Given a piece type of KNIGHT
    When I convert it to string
    Then the result should be "KNIGHT"

  Scenario: Convert BISHOP piece type to string
    Given a piece type of BISHOP
    When I convert it to string
    Then the result should be "BISHOP"

  Scenario: Convert QUEEN piece type to string
    Given a piece type of QUEEN
    When I convert it to string
    Then the result should be "QUEEN"

  Scenario: Convert KING piece type to string
    Given a piece type of KING
    When I convert it to string
    Then the result should be "KING"

  Scenario: Convert EMPTY piece type to string
    Given a piece type of EMPTY
    When I convert it to string
    Then the result should be "EMPTY"

  Scenario: Parse lowercase 'p' as PAWN
    Given a character 'p'
    When I parse it as piece type
    Then the result should be PAWN

  Scenario: Parse uppercase 'P' as PAWN
    Given a character 'P'
    When I parse it as piece type
    Then the result should be PAWN

  Scenario: Parse lowercase 'r' as ROOK
    Given a character 'r'
    When I parse it as piece type
    Then the result should be ROOK

  Scenario: Parse 'h' as KNIGHT
    Given a character 'h'
    When I parse it as piece type
    Then the result should be KNIGHT

  Scenario: Parse 'b' as BISHOP
    Given a character 'b'
    When I parse it as piece type
    Then the result should be BISHOP

  Scenario: Parse 'q' as QUEEN
    Given a character 'q'
    When I parse it as piece type
    Then the result should be QUEEN

  Scenario: Parse 'k' as KING
    Given a character 'k'
    When I parse it as piece type
    Then the result should be KING

  Scenario: Parse '_' as EMPTY
    Given a character '_'
    When I parse it as piece type
    Then the result should be EMPTY

  Scenario: Parse invalid character throws exception
    Given a character 'x'
    When I parse it as piece type
    Then an exception should be thrown
