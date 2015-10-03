Feature: Piece Movement via Drag and Drop
  As a chess game
  I need to handle drag and drop operations
  So that players can move pieces by dragging

  Scenario: Accept drag for chess piece MIME type
    Given a chess board with standard starting position
    When I start dragging white PAWN at [6,0]
    Then the drag event should be accepted

  Scenario: Reject drag for other MIME types
    Given a chess board
    When I start dragging a non-chess-piece item
    Then the drag event should be rejected

  Scenario: Calculate correct grid position from drop coordinates
    Given a chess board
    When I drop a piece at pixel coordinates (125, 175)
    Then the calculated grid position should be [3,2]

  Scenario: Calculate grid position at cell boundary
    Given a chess board
    When I drop a piece at pixel coordinates (50, 50)
    Then the calculated grid position should be [1,1]

  Scenario: Calculate grid position with offset
    Given a chess board
    When I drop a piece at pixel coordinates (230, 340)
    Then the calculated grid position should be close to [6,4]

  Scenario: Update board map when piece is dropped
    Given a chess board with white KNIGHT at [7,1]
    When I drag the knight to [5,2]
    Then position [5,2] should contain the knight
    And position [7,1] should be empty

  Scenario: Clear old board position when piece moves
    Given a chess board with white ROOK at [7,0]
    When I drag the rook to [5,0]
    Then boardMap[7][0] should be NULL
    And boardMap[5][0] should point to the rook

  Scenario: Align piece to grid after drop
    Given a chess board with white BISHOP at [7,2]
    When I drag and drop the bishop to [5,4]
    Then the bishop should be aligned to grid cell [5,4]
    And the bishop pixel position should match grid coordinates

  Scenario: Accept drag move event during dragging
    Given a chess board
    And a piece is being dragged
    When the mouse moves during drag
    Then dragMoveEvent should accept the event

  Scenario: Update piece row and column on drop
    Given a chess board with white QUEEN at [7,3]
    When I drag the queen to [4,5]
    Then the queen row should be 4
    And the queen column should be 5

  Scenario: Handle drop at board edge
    Given a chess board with white PAWN at [6,4]
    When I drag the pawn to [5,7]
    Then the pawn should be at [5,7]
    And the pawn should not be out of bounds

  Scenario: Drop event updates piece visual position
    Given a chess board with black KNIGHT at [0,6]
    When I drag the knight to [2,5]
    Then the knight QLabel should be at correct pixel position
    And alignToGrid should be called
