Feature: Available Moves Highlighting
  As a chess game
  I need to highlight available moves for selected pieces
  So that players can see where they can move

  Scenario: Clear all moves resets entire array
    Given a chess board with some highlighted moves
    When I clear available moves
    Then all cells should have DISABLE status
    And no cells should be highlighted

  Scenario: Selecting piece populates available moves
    Given a chess board with standard starting position
    When I click on white KNIGHT at [7,1]
    Then cells [5,0] and [5,2] should be highlighted
    And the avMoves array should reflect these highlights

  Scenario: Available moves match getTurnArea result
    Given a chess board with white ROOK at [4,4]
    When I select the rook
    Then the highlighted cells should match getTurnArea output

  Scenario: Highlighting empty cells with ENABLE status
    Given a chess board with white BISHOP at [4,4]
    When I select the bishop
    Then empty diagonal cells should have ENABLE status
    And should be highlighted as available moves

  Scenario: Highlighting attack cells with ATTACK status
    Given a chess board with white ROOK at [4,4]
    And a black PAWN at [4,7]
    When I select the rook
    Then cell [4,7] should have ATTACK status
    And should be highlighted differently from ENABLE cells

  Scenario: Deselecting piece clears highlights
    Given a chess board with white KNIGHT at [7,1]
    And the knight is selected with highlighted moves
    When I click on an empty cell
    Then all highlights should be cleared

  Scenario: Selecting different piece updates highlights
    Given a chess board with white KNIGHT selected
    And moves are highlighted
    When I select a white ROOK instead
    Then previous highlights should be cleared
    And new highlights for rook should appear

  Scenario: Clicking opponent piece shows no highlights
    Given a chess board with standard starting position
    When I click on black PAWN at [1,0]
    Then no cells should be highlighted
    And avMoves should remain cleared

  Scenario: Move highlighting coordinates with board rendering
    Given a chess board with white QUEEN at [3,3]
    When I select the queen
    Then highlighted cells should be visually rendered
    And paintEvent should show proper colors
