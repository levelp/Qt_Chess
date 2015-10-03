Feature: Cell Status Determination
  As a chess game
  I need to determine if a cell is empty, occupied by own piece, or occupied by opponent
  So that move validation can work correctly

  Scenario: Empty cell returns ENABLE status
    Given a chess board with standard starting position
    When I check the status of cell [4,4] for WHITE player
    Then the status should be ENABLE

  Scenario: Cell with own piece returns DISABLE status
    Given a chess board with standard starting position
    When I check the status of cell [6,0] for WHITE player
    Then the status should be DISABLE

  Scenario: Cell with opponent piece returns ATTACK status
    Given a chess board with standard starting position
    When I check the status of cell [1,0] for WHITE player
    Then the status should be ATTACK

  Scenario: Out-of-bounds row returns DISABLE
    Given a chess board with standard starting position
    When I check the status of cell [8,4] for WHITE player
    Then the status should be DISABLE

  Scenario: Out-of-bounds column returns DISABLE
    Given a chess board with standard starting position
    When I check the status of cell [4,8] for WHITE player
    Then the status should be DISABLE

  Scenario: Negative row returns DISABLE
    Given a chess board with standard starting position
    When I check the status of cell [-1,4] for WHITE player
    Then the status should be DISABLE

  Scenario: Negative column returns DISABLE
    Given a chess board with standard starting position
    When I check the status of cell [4,-1] for WHITE player
    Then the status should be DISABLE

  Scenario: Cell at boundary with own piece
    Given a chess board with standard starting position
    When I check the status of cell [7,7] for WHITE player
    Then the status should be DISABLE

  Scenario: Cell at boundary with opponent piece
    Given a chess board with standard starting position
    When I check the status of cell [0,0] for WHITE player
    Then the status should be ATTACK

  Scenario: BLACK player checking white piece cell
    Given a chess board with standard starting position
    When I check the status of cell [7,0] for BLACK player
    Then the status should be ATTACK

  Scenario: BLACK player checking black piece cell
    Given a chess board with standard starting position
    When I check the status of cell [0,0] for BLACK player
    Then the status should be DISABLE
