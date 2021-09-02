#include <vector>
#include <string>
#include <set>

using namespace std;
class Grid {
    public:
        struct Pair {
            int row; int col;
            bool operator< (const Pair& p) const {
                return p.row == this->row ? this->col < p.col : this->row < p.row;
            }
            bool operator== (const Pair& p) const {
                return p.row == this->row && p.col == this->col;
            }
        };
    private: 
        int numBlocks;
        vector<string> board;
        vector<vector<Pair> > parent;
        set<Pair> blocks;
    public: 
        Grid(vector<string>& board);
        void updateBoard();
        void printBoard();
        void printParents();
        void createDisjoint();
        Grid removeSet(Pair p);
        int getNumBlocks() {return this->numBlocks;}
        set<Pair>& getBlocks() {return this->blocks;}
};