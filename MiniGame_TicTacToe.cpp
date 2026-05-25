#include <iostream>
using namespace std;

class TicTacToe {
private:
    char board[3][3];
    char currentPlayer;

public:
    TicTacToe() {
        resetBoard();
    }

    void resetBoard() {
        char num = '1';

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                board[i][j] = num++;
            }
        }

        currentPlayer = 'X';
    }

    void displayBoard() {
        cout << "\n";
        cout << "-------------\n";

        for(int i = 0; i < 3; i++) {
            cout << "| ";

            for(int j = 0; j < 3; j++) {
                cout << board[i][j] << " | ";
            }

            cout << "\n-------------\n";
        }

        cout << "\n";
    }

    bool makeMove(int choice) {
        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if(choice < 1 || choice > 9) {
            return false;
        }

        if(board[row][col] == 'X' || board[row][col] == 'O') {
            return false;
        }

        board[row][col] = currentPlayer;
        return true;
    }

    bool checkWinner() {

        // Rows
        for(int i = 0; i < 3; i++) {
            if(board[i][0] == board[i][1] &&
               board[i][1] == board[i][2]) {
                return true;
            }
        }

        // Columns
        for(int i = 0; i < 3; i++) {
            if(board[0][i] == board[1][i] &&
               board[1][i] == board[2][i]) {
                return true;
            }
        }

        // Diagonals
        if(board[0][0] == board[1][1] &&
           board[1][1] == board[2][2]) {
            return true;
        }

        if(board[0][2] == board[1][1] &&
           board[1][1] == board[2][0]) {
            return true;
        }

        return false;
    }

    bool isDraw() {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] != 'X' &&
                   board[i][j] != 'O') {
                    return false;
                }
            }
        }

        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void play() {
        int choice;

        while(true) {

            displayBoard();

            cout << "Player " << currentPlayer
                 << ", enter position (1-9): ";
            cin >> choice;

            if(!makeMove(choice)) {
                cout << "\nInvalid move! Try again.\n";
                continue;
            }

            if(checkWinner()) {
                displayBoard();
                cout << "Player "
                     << currentPlayer
                     << " wins!\n";
                break;
            }

            if(isDraw()) {
                displayBoard();
                cout << "Game Draw!\n";
                break;
            }

            switchPlayer();
        }
    }
};

int main() {

    char replay;

    do {
        TicTacToe game;
        game.play();

        cout << "\nPlay Again? (Y/N): ";
        cin >> replay;

    } while(replay == 'Y' || replay == 'y');

    cout << "\nThanks for playing!\n";

    return 0;
}