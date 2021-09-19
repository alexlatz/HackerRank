#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Grid.h"

class GameState {
    Grid grid;
    GameState* parent;
    int moves;
    vector<GameState> children;
    bool boardFinished;
    public:
        GameState(Grid grid, GameState* parent, int moves);
        GameState(const GameState& original);
        vector<GameState>& getChildren();
        Grid& getGrid();
        bool operator> (const GameState& g) const  {
            return this->moves+this->grid.getNumBlocks() > g.moves + g.grid.getNumBlocks();
        }
        [[nodiscard]] bool getBoardFinished() const {
            return this->boardFinished;
        }
        GameState* getParent() {
            return this->parent;
        }
};
#endif