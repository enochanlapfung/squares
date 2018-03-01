#include "squares.h"

using std::vector;

// Default constructor, game board is 3x3 squares
Squares::Squares() : Squares(3) {}

// Constructor where size is the length and height of the game board
Squares::Squares(int size) : Squares(size, size) {}

// Constructor where game board length and height are specified
Squares::Squares(int length, int height)
:   gameBoard_(2*height+1, vector<int>(2*length+1, EMPTY)),
    height_(height),
    length_(length)
{
    // Place plusses
    vector<vector<int>>::iterator rit;
    vector<vector<int>>::iterator rend = gameBoard_.end();
    for (rit = gameBoard_.begin(); rit < rend; rit += 2)
    {
        vector<int>::iterator cit;
        vector<int>::iterator cend = rit->end();
        for (cit = rit->begin(); cit < cend; cit += 2)
        {
            *cit = PLUS;
        }
    }
}

// Returns true of a square has all edges filled, false otherwise
// If row/col is invalid, returns false
bool Squares::square_is_filled(int row, int col)
{
    // Check if (row, col) are valid inputs
    if (row < 0 || row >= height_ || col < 0 || col >= length_)
    {
        return false;
    }

    int x = (2 * col) + 1;
    int y = (2 * row) + 1;

    // Check up
    if (gameBoard_[y-1][x] != EDGE) { return false; }
    // Check left
    if (gameBoard_[y][x-1] != EDGE) { return false; }
    // Check right
    if (gameBoard_[y][x+1] != EDGE) { return false; }
    // Check down
    if (gameBoard_[y+1][x] != EDGE) { return false; }

    // All edges are filled
    return true;
}

// Make a play at (row, col) with edge e. Returns the number of points scored
// or -1 if the play is invalid
int Squares::play(int row, int col, Edge e, char name)
{
    // Check if (row, col) are valid inputs
    if (row < 0 || row >= height_ || col < 0 || col >= length_)
    {
        return -1;
    }

    // Determining which symbol on the game board is being changed
    int x = (2 * col) + 1;
    int y = (2 * row) + 1;
    switch (e)
    {
        case UP:    --y; break;
        case LEFT:  --x; break;
        case RIGHT: ++x; break;
        case DOWN:  ++y; break;
        default:
            // Invalid
            return -1;
    }

    // Checking if there is already an edge there
    if (gameBoard_[y][x] != EMPTY)
    {
        return -1;
    }

    // Placing an edge
    gameBoard_[y][x] = EDGE;

    int points = 0;

    // Calculate points gained as a result of the move
    if (y % 2)
    {
        // Vertical edge

        // Checking left square
        if (square_is_filled(row, (x-2)/2))
        {
            ++points;
            gameBoard_[y][x-1] = name;
        }

        // Checking right square
        if (square_is_filled(row, x/2))
        {
            ++points;
            gameBoard_[y][x+1] = name;
        }
    }
    else
    {
        // Horizontal edge

        // Checking up square
        if (square_is_filled((y-2)/2, col))
        {
            ++points;
            gameBoard_[y-1][x] = name;
        }

        // Checking down square
        if (square_is_filled(y/2, col))
        {
            ++points;
            gameBoard_[y+1][x] = name;
        }
    }

    return points;
}

// Returns a data structure representing the game board
const std::vector<std::vector<int>>& Squares::get_game_board()
{
    return gameBoard_;
}