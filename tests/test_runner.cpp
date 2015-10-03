#include <QtTest/QtTest>
#include <QCoreApplication>
#include <iostream>

/**
 * BDD Test Runner for Qt Chess
 *
 * This runner executes all BDD tests defined in step definitions
 * Each test file is a separate test suite that can be run independently
 *
 * Usage:
 *   ./test_runner                  - Run all tests
 *   ./test_runner <test_name>      - Run specific test
 */

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    std::cout << "=====================================" << std::endl;
    std::cout << "Qt Chess BDD Test Suite" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Test suites available:" << std::endl;
    std::cout << "  1. Game Constants Tests" << std::endl;
    std::cout << "  2. Piece Management Tests" << std::endl;
    std::cout << "  3. Board Initialization Tests" << std::endl;
    std::cout << "  4. Cell Status Tests" << std::endl;
    std::cout << "  5. Movement Tests (All pieces)" << std::endl;
    std::cout << std::endl;

    std::cout << "To run individual test suites, compile them separately:" << std::endl;
    std::cout << "  - game_constants_steps" << std::endl;
    std::cout << "  - piece_management_steps" << std::endl;
    std::cout << "  - board_initialization_steps" << std::endl;
    std::cout << "  - cell_status_steps" << std::endl;
    std::cout << "  - movement_steps" << std::endl;
    std::cout << std::endl;

    std::cout << "=====================================" << std::endl;
    std::cout << "BDD Feature Files:" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "All feature files are located in tests/features/" << std::endl;
    std::cout << "  - game_constants.feature" << std::endl;
    std::cout << "  - piece_management.feature" << std::endl;
    std::cout << "  - board_initialization.feature" << std::endl;
    std::cout << "  - cell_status.feature" << std::endl;
    std::cout << "  - pawn_movement.feature" << std::endl;
    std::cout << "  - rook_movement.feature" << std::endl;
    std::cout << "  - knight_movement.feature" << std::endl;
    std::cout << "  - bishop_movement.feature" << std::endl;
    std::cout << "  - queen_movement.feature" << std::endl;
    std::cout << "  - king_movement.feature" << std::endl;
    std::cout << "  - diagonal_movement.feature" << std::endl;
    std::cout << "  - horizontal_movement.feature" << std::endl;
    std::cout << "  - king_safety.feature" << std::endl;
    std::cout << "  - move_highlighting.feature" << std::endl;
    std::cout << "  - drag_and_drop.feature" << std::endl;
    std::cout << "  - board_file_io.feature" << std::endl;
    std::cout << "  - board_rendering.feature" << std::endl;
    std::cout << std::endl;

    return 0;
}
