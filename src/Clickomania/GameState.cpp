#include "GameState.h"

GameState::GameState(Grid grid, GameState* parent, int moves) : grid(grid) {
    this->parent = parent;
    this->moves = moves;
    this->boardFinished = this->grid.getBlocks().empty();
}

GameState::GameState(const GameState& original) : grid(original.grid) {
    this->parent = original.parent;
    this->moves = original.moves;
    this->boardFinished = this->grid.getBlocks().empty();
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

Grid& GameState::getGrid() {
    return this->grid;
}