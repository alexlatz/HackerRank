#include "Grid.h"
#include <iostream>

Grid::Grid(vector<string>& board) {
    this->board = board;    
    updateBoard();
    prepareBlocks();
    this->disjointCreated = false;
}

Grid::Grid(Grid& original) {
    vector<string> newBoard(original.board);
    vector<vector<Pair> > newParent(original.parent); 
    set<Pair> newBlocks(original.blocks);
    this->board = newBoard;
    this->parent = newParent;
    this->blocks = newBlocks;
    this->numBlocks = original.numBlocks;
    this->disjointCreated = original.disjointCreated; 
}

void Grid::prepareBlocks() {
    vector<vector<Pair> > parent;
    set<Pair> blocks;
    int numBlocks = 0;
    for (int i = 0; i < board.size(); i++) {
        vector<Pair> row;
        for (int j = 0; j < board[i].size(); j++) {
            struct Pair point = {i, j};
            if (this->board[i][j] != '-') {
                blocks.insert(point);
                numBlocks++;
            }
            row.push_back(point);
        }
        parent.push_back(row);
    }
    this->blocks = blocks;
    this->parent = parent;
    this->numBlocks = numBlocks;
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

Grid& Grid::removeSet(Grid::Pair p) {
    vector<string> newBoard(board);
    for (int i = 0; i < newBoard.size(); i++) {
        for (int j = 0; j < newBoard[i].size(); j++) {
            if (parent[i][j] == p) newBoard[i][j] = '-';
        }
    }
    Grid newGrid(newBoard);
    return newGrid;
}

set<Grid::Pair>& Grid::getBlocks() {
    if (!disjointCreated) {
        createDisjoint();
        disjointCreated = true;
    }
    return this->blocks;
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