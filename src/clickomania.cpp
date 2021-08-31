/*
Clickomania is a 1-player game consisting of a rectangular grid of square blocks, each colored in one of k colors. Adjacent blocks horizontally and vertically of the same color are considered to be a part of the same group. A move selects a group containing at least two blocks and removes those blocks, followed by two "falling" rules;

Any blocks remaining above the holes created, fall down through the same column.
Any empty columns are removed by sliding the succeeding columns left.


In this game, you have to code a bot such that it eliminates as many possible blocks from the grid. The top left of the grid is indexed (0,0) and the bottom right of the grid is indexed (rows-1,columns-1).

Input Format
The first line of the input is 3 space separated integers, x y k where x and y are the row index and the column index of the grid respectively, and k is the number of colors the grid has.

An empty cell in the grid will be denoted by '-'.

Output Format
Output 2 space separated integers that represent the co-ordinates of the block you choose to remove from the grid. You can output any one of the nodes of the group which you choose to remove.

Constraints
1 ≤ k ≤ 7
Each color can be any of 'V','I','B','G','Y','O','R' (VIBGYOR)

Sample Input

20 10 2
BBRBRBRBBB
RBRBRBBRRR
RRRBBRBRRR
RBRBRRRBBB
RBRBRRRRBB
RBBRBRRRRR
BBRBRRBRBR
BRBRBBRBBB
RBBRRRRRRB
BBRBRRBBRB
BBBRBRRRBB
BRBRRBRRBB
BRRBBBBBRB
RRBBRRBRRR
RRRBRRRBBB
RRRRRBBBRR
BRRRBRRRBB
BBBBRBRRRB
BRBBBBBRBB
RRRRRBBRRR
Sample Output
0 1

Explanation
In this output, the player chooses to remove all the adjacent blocks of the group (0,0), (0,1) and (1,1) which forms one group.

Challenge
Complete the function nextMove which takes integers x, y - the row and column size of the grid, color - the number of colors the grid has, and grid - a 2D array of characters which is the board.

Scoring
Your score depends on the number of blocks left (count), the size of the board and the number of colors (k).
Score = (1 - count/20) x 5 x k

if count ≥ 20, a nominal score of 0.01 would be given.

The maximum scores for the testcases of this challenge are 10, 15, 25, and 30. Hence you can get a total score of 80.
*/
#include "clickomania.h"
#include <iostream>
#include <fstream>

Grid::Grid(int x, int y, int k, vector<string>& board) {
    this->x = x;
    this->y = y;
    this->k = k;
    this->board = board;    
    updateBoard();
    vector<vector<Pair> > parent;
    set<Pair> blocks;
    for (int i = 0; i < board.size(); i++) {
        vector<Pair> row;
        for (int j = 0; j < board[i].size(); j++) {
            struct Pair point = {i, j};
            if (this->board[i][j] != '-') {
                blocks.insert(point);
            }
            row.push_back(point);
        }
        parent.push_back(row);
    }
    this->parent = parent;
    this->blocks = blocks;
    createDisjoint();
}

void Grid::updateBoard() {
    for (int i = board.size()-2; i>=0; i--) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != '-' && board[i+1][j] == '-') {
                int howFar = 1;
                for (int k = 1; k+i < board.size(); k++) {
                    if (board[i+k][j] != '-') {
                        howFar = k-1;
                        break;
                    } else if (board[i+k][j] == '-' && i+k == board.size()-1) {
                        howFar = k;
                    }
                }
                string fallLine = board[i+howFar].substr(0, j) + board[i][j] + board[i+howFar].substr(j+1);
                board[i+howFar].swap(fallLine);
                string newLine = board[i].substr(0, j) + '-' + board[i].substr(j+1);
                board[i].swap(newLine);
            }
        }
    }
    for (int j = 0; j < board[0].size(); j++) {
        bool shift = false;
        for (int i = 0; i < board.size(); i++) {
            if (board[i][j] != '-') break;
            else if (i == board.size()-1) shift = true; 
        }
        if (shift) {
            for (int i = 0; i < board.size(); i++) {
                string newLine = board[i].substr(0, j) + board[i].substr(j+1) + '-';
                board[i].swap(newLine);
            }
        }
    }
}

void Grid::createDisjoint() {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != '-') {
                if (j < board[i].size()-1 && board[i][j] == board[i][j+1]) {
                    if (parent[i][j+1].row != i || parent[i][j+1].col != j+1) {
                        blocks.erase(parent[i][j]);
                        parent[i][j] = parent[i][j+1];
                    } else {
                        blocks.erase(parent[i][j+1]);
                        parent[i][j+1] = parent[i][j];
                    }
                }
                if (i < board.size()-1 && board[i][j] == board[i+1][j]) {
                    if (parent[i+1][j].row != i+1 || parent[i+1][j].col != j) {
                        blocks.erase(parent[i][j]);
                        parent[i][j] = parent[i+1][j];
                    } else {
                        blocks.erase(parent[i+1][j]);
                        parent[i+1][j] = parent[i][j];
                    }
                }
            }
        }
    }
}


void Grid::printBoard() {
    for (int i = 0; i < board.size(); i++) {
        cout << board[i] << "\n";
    }
}

void Grid::printParents() {
    for (int i = 0; i < parent.size(); i++) {
        for (int j = 0; j < parent[i].size(); j++) {
            cout << parent[i][j].row << parent[i][j].col << " ";
        }
        cout << "\n";
    }
}

void nextMove(int x, int y, int k, vector<string> board) {
    Grid grid(x, y, k, board);
    grid.printBoard();
    grid.printParents();
}

int main(int argc, char const *argv[])
{
    ifstream infile;
    infile.open("input.txt");
    int x, y, k;
    infile >> x >> y >> k;
    vector<string> grid;
    for (int i = 0; i < x; i++) {
        string s;
        infile >> s;
        grid.push_back(s);
    }
    nextMove(x, y, k, grid);
    infile.close();
    return 0;
}

