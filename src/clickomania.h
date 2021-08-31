#include <vector>
#include <string>
#include <set>

using namespace std;
class Grid {
    public:
    struct Pair {int row; int col;
    bool operator< (const Pair& p) const {
        return p.row == this->row ? this->col < p.col : this->row < p.row;
    }};
    private:
    int x, y, k;
    vector<string> board;
    vector<vector<Pair> > parent;
    set<Pair> blocks;
    public: 
        Grid(int x, int y, int k, vector<string>& board);
        void updateBoard();
        void printBoard();
        void printParents();
        void createDisjoint();
};