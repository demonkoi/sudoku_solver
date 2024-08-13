#include <vector>
#include <iostream>

void fillChars(std::vector<std::vector<char>> *board, std::vector<std::vector<std::vector<char>>> *working_Board);

bool check_solved(const std::vector<std::vector<char>> *board) {
    for(char i = 0; i < 9; i++) {
        for(char j = 0; j < 9; j++) {
            if((*board)[i][j] == '.') {
                return false;
            }
        }
    }
    return true;
}

void solveSudoku(std::vector<std::vector<char>> &board) {
    std::vector<std::vector<std::vector<char>>> working_Board(
        9, std::vector<std::vector<char>>(9, std::vector<char>(9, '.'))
    );
    
    for (char outer = 0; outer < 9; outer++) {
        for(char middle = 0; middle < 9; middle++) {
            if (board[outer][middle] != '.') {
                char val = board[outer][middle] - '1'; // convert char to 0-8 index
                working_Board[outer][middle][val] = board[outer][middle];
            }
        }
    }
    
    while(!check_solved(&board)) {
        for(char i = 0; i < 9; i++) {
            for(char j = 0; j < 9; j++) {
                if(board[i][j] != '.') {
                    // remove possible from row
                    for(char t = 0; t < 9; t++) {
                        working_Board[i][t][board[i][j] - '1'] = '.';
                    }
                    // remove possible from column
                    for(char t = 0; t < 9; t++) {
                        working_Board[t][j][board[i][j] - '1'] = '.';
                    }
                    // remove possible from square
                    for(char t = 0; t < 3; t++) {
                        for(char k = 0; k < 3; k++) {
                            working_Board[(i/3)*3 + t][(j/3)*3 + k][board[i][j] - '1'] = '.';
                        }
                    }
                }
            }
        }
        fillChars(&board, &working_Board);
    }
}

void fillChars(std::vector<std::vector<char>> *board, std::vector<std::vector<std::vector<char>>> *working_Board) {
    for(char i = 0; i < 9; i++) {
        for(char j = 0; j < 9; j++) {
            if((*board)[i][j] == '.') {
                for(char t = 0; t < 9; t++) {
                    if((*working_Board)[i][j][t] != '.') {
                        (*board)[i][j] = (*working_Board)[i][j][t];
                        fillChars(board, working_Board);
                        return; // Stop after filling one position to avoid infinite recursion
                    }
                }
            }
        }
    }
}

void print_solved(const std::vector<std::vector<char>> &board) {
    for(char i = 0; i < 9; i++) {
        for(char j = 0; j < 9; j++) {
            std::cout << board[i][j] << " ";
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
    print_solved(board);
    
    return 0;
}
