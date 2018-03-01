#ifndef SQAURES_H
#define SQAURES_H

#include <vector>

class Squares
{
    public:
        // The edge of a square, used in the play function
        enum Edge
        {
            UP, LEFT, RIGHT, DOWN
        };

        // Integers for representing symbols on the gameboard (edge, plus, empty)
        enum GameBoardElement
        {
            EDGE, PLUS, EMPTY
        };

        // Default constructor, game board is 3x3 sqaures
        Squares();

        // Constructor where size is the length and height of the game board
        Squares(int size);

        // Constructor where game board length and height are specified
        Squares(int length, int height);

        // Make a play at (row, col) with edge e. Returns the number of points scored
        // or -1 if the play is invalid
        int play(int row, int col, Edge e, char name);

        // Returns a data structure representing the game board
        const std::vector<std::vector<int>>& get_game_board();

    private:
        // Contains integers representing symbols on the game board
        std::vector<std::vector<int>> gameBoard_;

        // Height of game board
        int height_;

        // Length of game board
        int length_;

        // Returns true of a square has all edges filled, false otherwise
        // If row/col is invalid, returns false
        bool square_is_filled(int row, int col);
};

#endif