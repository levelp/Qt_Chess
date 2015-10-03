Feature: Chess Board Rendering
  As a chess game
  I need to render the board with proper colors
  So that players can see the board and available moves

  Scenario: Render disabled cells with white/gray pattern
    Given a chess board with all cells disabled
    When the board is rendered
    Then even cells (i+j)%2==0 should be white
    And odd cells (i+j)%2==1 should be gray

  Scenario: Render enabled cells with green/dark gray pattern
    Given a chess board with cell [3,4] enabled
    When the board is rendered
    Then cell [3,4] should be green or dark gray based on position
    And the enabled color should differ from disabled color

  Scenario: Apply checkerboard pattern correctly
    Given a chess board
    When the board is rendered
    Then cell [0,0] should have one color
    And cell [0,1] should have alternating color
    And cell [1,0] should have alternating color
    And cell [1,1] should have same color as [0,0]

  Scenario: Render 8x8 grid with correct cell size
    Given a chess board
    When the board is rendered
    Then each cell should be 50x50 pixels
    And the total board should be 400x400 pixels
    And all 64 cells should be drawn

  Scenario: Render cells according to avMoves array
    Given a chess board
    And avMoves[3][4] is set to ENABLE
    And avMoves[3][5] is set to ATTACK
    When the board is rendered
    Then cell [3,4] should use enabled color scheme
    And cell [3,5] should use enabled color scheme
    And other cells should use disabled color scheme

  Scenario: Paint event draws all board cells
    Given a chess board
    When paintEvent is triggered
    Then 64 rectangles should be drawn
    And each rectangle should have correct position

  Scenario: Cell colors alternate correctly
    Given a chess board
    When the board is rendered
    Then adjacent cells should have different base colors
    And the checkerboard pattern should be consistent

  Scenario: Highlighted moves have distinct colors
    Given a chess board with white ROOK at [4,4]
    And available moves are highlighted
    When the board is rendered
    Then highlighted cells should be visually distinct
    And non-highlighted cells should use default colors

  Scenario: Rendering respects CELL constant
    Given a chess board with CELL=50
    When the board is rendered
    Then each cell width should be 50 pixels
    And each cell height should be 50 pixels
    And cell positions should be multiples of 50
