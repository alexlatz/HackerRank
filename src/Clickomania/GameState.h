#include "Grid.h"

class GameState {
    Grid grid;
    GameState* parent;
    int moves;
    vector<GameState> children;
    bool operator< (GameState& g)  {
        return this->moves+this->grid.getNumBlocks() < g.moves + g.grid.getNumBlocks();
    }
    public:
        GameState(Grid grid, GameState* parent, int moves);
        vector<GameState>& getChildren();
};