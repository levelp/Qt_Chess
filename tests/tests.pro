TEMPLATE = subdirs

# All test executables
SUBDIRS = \
    game_constants_test \
    piece_management_test \
    board_initialization_test \
    cell_status_test \
    movement_test \
    diagonal_movement_test \
    horizontal_movement_test \
    king_safety_test \
    board_file_io_test

# Configuration for each test
game_constants_test.file = game_constants_test.pro
piece_management_test.file = piece_management_test.pro
board_initialization_test.file = board_initialization_test.pro
cell_status_test.file = cell_status_test.pro
movement_test.file = movement_test.pro
diagonal_movement_test.file = diagonal_movement_test.pro
horizontal_movement_test.file = horizontal_movement_test.pro
king_safety_test.file = king_safety_test.pro
board_file_io_test.file = board_file_io_test.pro
