#include "GameState.h"

GameState::GameState(Grid grid, GameState* parent, int moves) {
    this->grid = grid;
    this->parent = parent;
    this->moves = moves;
}

vector<GameState>& GameState::getChildren() {
    if (children.empty()) {
        for (Grid::Pair p : grid.getBlocks()) {
            GameState newState(grid.removeSet(p), this, this->moves+1);
            children.push_back(newState);
        }
    }
    return children;
}