#include <iostream>
#include <vector>
#include <iterator>
#include <map>

#include "squares.h"

using namespace std;

// Prints the game board
void print_game_board(const vector<vector<int>>& gameBoard)
{
    vector<vector<int>>::const_iterator rit;
    vector<vector<int>>::const_iterator rend = gameBoard.end();
    for (rit = gameBoard.begin(); rit < rend; ++rit)
    {
        vector<int>::const_iterator cit;
        vector<int>::const_iterator cend = rit->end();
        for (cit = rit->begin(); cit < cend; ++cit)
        {
            switch (*cit)
            {
                case Squares::EMPTY:
                    cout << " ";
                    break;
                case Squares::EDGE:
                    // If even row, horizontal edge, else, vertical edge
                    ((rit - gameBoard.begin()) % 2) ? (cout << "|") : (cout << "-");
                    break;
                case Squares::PLUS:
                    cout << "+";
                    break;
                default:
                    // Write the player name
                    cout << (char)*cit;
                    break;
            }
        }
        // End of row, print newline
        cout << endl;
    }
}

// Main function
int main()
{
    int length = 0;
    int height = 0;

    cout << "Length: ";
    cin >> length;
    cout << "Height: ";
    cin >> height;
    Squares s(length, height);

    int numPlayers;
    cout << "Number of players: ";
    cin >> numPlayers;

    const int maxPoints = length * height;
    int currentPoints = 0;
    int currentPlayer = 0;
    vector<int> playerPoints(numPlayers, 0);

    // Print the game board
    const vector<vector<int>>& gb = s.get_game_board();
    print_game_board(gb);

    while (currentPoints != maxPoints)
    {
        int row = 0;
        int col = 0;
        char edge = 0;
        Squares::Edge e;
        int pointsWonByCurrentMove = 0;

        // Prompt the player to make a move
        cout << (char)('A' + currentPlayer) << "> ";
        cin >> row >> col >> edge;

        // Make the play
        switch (edge)
        {
            case 'W':
            case 'w':
                e = Squares::UP;
                break;
            case 'A':
            case 'a':
                e = Squares::LEFT;
                break;
            case 'S':
            case 's':
                e = Squares::DOWN;
                break;
            case 'D':
            case 'd':
                e = Squares::RIGHT;
                break;
            default:
                break;
        }
        pointsWonByCurrentMove = s.play(row, col, e, ('A' + currentPlayer));

        // Add points to total tally, and to the player's score
        currentPoints += pointsWonByCurrentMove;
        playerPoints[currentPlayer] += pointsWonByCurrentMove;

        // Switch to next player
        currentPlayer = (currentPlayer + 1) % numPlayers;

        print_game_board(gb);
    }

    // Determine who won
    vector<int>::const_iterator it;
    vector<int>::const_iterator end = playerPoints.end();
    vector<int> winningPlayers;
    int highestScore = 0;
    for (it = playerPoints.begin(); it != end; ++it)
    {
        if (*it > highestScore)
        {
            winningPlayers.clear();
            winningPlayers.push_back(it - playerPoints.begin());
            highestScore = *it;
        }
        else if (*it == highestScore)
        {
            winningPlayers.push_back(it - playerPoints.begin());
        }
    }

    cout << "Winning player(s): ";
    end = winningPlayers.end();
    for (it = winningPlayers.begin(); it != end; ++it)
    {
        cout << (char)('A' + *it);
    }
    cout << endl;

    return 0;
}
