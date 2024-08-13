#include <vector>
#include <iostream>

bool isValid(const std::vector<std::vector<char>>& board, int row, int col, char c) {
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == c || board[row][i] == c || 
            board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) {
            return false;
        }
    }
    return true;
}

bool solveSudoku(std::vector<std::vector<char>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == '.') {
                for (char c = '1'; c <= '9'; c++) {
                    if (isValid(board, row, col, c)) {
                        board[row][col] = c;
                        if (solveSudoku(board)) {
                            return true;
                        }
                        board[row][col] = '.'; // Backtrack
                    }
                }
                return false; // If no valid number found, trigger backtrack
            }
        }
    }
    return true; // If no empty cells, the board is solved
}

void printBoard(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<char>> board = {
        {'.','.','9','7','4','8','.','.','.'},
        {'7','.','.','.','.','.','.','.','.'},
        {'.','2','.','1','.','9','.','.','.'},
        {'.','.','7','.','.','.','2','4','.'},
        {'.','6','4','.','1','.','5','9','.'},
        {'.','9','8','.','.','.','3','.','.'},
        {'.','.','.','8','.','3','.','2','.'},
        {'.','.','.','.','.','.','.','.','6'},
        {'.','.','.','2','7','5','9','.','.'}
    };
    
    solveSudoku(board);
    printBoard(board); 
    return 0;
}