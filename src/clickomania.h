#include <vector>
#include <string>
#include <unordered_set>

using namespace std;
class Grid {
    struct Pair {int row; int col;
    bool operator== (const Pair p) {
        return p.col == this->col && p.row == this->row;
    }};
    int x, y, k;
    vector<string> board;
    vector<vector<Pair> > parent;
    unordered_set<Pair> blocks;
    public: 
        Grid(int x, int y, int k, vector<string>& board);
        void updateBoard();
        void printBoard();
        void printParents();
        void createDisjoint();
};