import java.util.*;

public class NPuzzle {

    private static class Board implements Comparable<Board> {
        int[][] board;
        int k;
        int[] zeroPos;
        int manhattan;
        String move;
        int moves;
        Board prev;

        public Board(int k, int[][] tiles, String move, int moves, Board prev) {
            this.k = k;
            this.board = tiles.clone();
            this.move = move;
            this.moves = moves;
            this.prev = prev;
            int sum = 0;
            for (int i = 0; i < board.length; i++) {
                for (int j = 0; j < board[0].length; j++) {
                    if (board[i][j] == 0) zeroPos = new int[]{i, j};
                    int[] coord = tileToIndex(board[i][j]);
                    sum += Math.abs(coord[0] - i) + Math.abs(coord[1] - j);
                }
            }
            this.manhattan = sum;
        }

        private int[] tileToIndex(int tile) {
            return new int[]{tile % k, tile / k};
        }

        public Iterable<Board> moves() {
            ArrayList<Board> boards = new ArrayList<>();
            if (zeroPos[1] != 0) boards.add(swap(zeroPos, zeroPos[0], zeroPos[1] - 1, "UP"));
            if (zeroPos[1] != k - 1) boards.add(swap(zeroPos, zeroPos[0], zeroPos[1] + 1, "DOWN"));
            if (zeroPos[0] != 0) boards.add(swap(zeroPos, zeroPos[0] - 1, zeroPos[1], "LEFT"));
            if (zeroPos[0] != k - 1) boards.add(swap(zeroPos, zeroPos[0] + 1, zeroPos[1], "RIGHT"));
            return boards;
        }

        private Board swap(int[] zeroPos, int x, int y, String move) {
            int[][] newBoard = new int[k][k];
            for (int i = 0; i < board.length; i++) {
                for (int j = 0; j < board[0].length; j++) {
                    newBoard[i][j] = board[i][j];
                }
            }
            int tmp = newBoard[zeroPos[0]][zeroPos[1]];
            newBoard[zeroPos[0]][zeroPos[1]] = newBoard[x][y];
            newBoard[x][y] = tmp;
            return new Board(k, newBoard, move, this.moves + 1, this);
        }

        @Override
        public int compareTo(Board that) {
            return Integer.compare(this.manhattan + this.moves, that.manhattan + that.moves);
        }

        @Override
        public boolean equals(Object obj) {
            Board that = (Board) obj;
            return Arrays.deepEquals(this.board, that.board);
        }
    }

    private static class Solver {
        Board solved;
        Deque<String> moves;

        public Solver(int k, int[][] tiles) {
            PriorityQueue<Board> pq = new PriorityQueue<>();
            pq.add(new Board(k, tiles, null, 0, null));
            while (pq.peek().manhattan > 0) {
                Board min = pq.poll();
                for (Board b : min.moves()) {
                    if (min.moves == 0) pq.add(b);
                    else if (!min.prev.equals(b)) pq.add(b);
                }
            }
            this.solved = pq.poll();
            Board b = solved;
            this.moves = new ArrayDeque<>();
            while (b.prev != null) {
                moves.push(b.move);
                b = b.prev;
            }
        }

        public Iterable<String> moves() {
            return this.moves;
        }

        public int numMoves() {
            return solved.moves;
        }
    }

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner scan = new Scanner(System.in);
        int k = scan.nextInt();
        int[][] board = new int[k][k];
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                board[j][i] = scan.nextInt();
            }
        }
        scan.close();
        Solver solver = new Solver(k, board);
        System.out.println(solver.numMoves());
        for (String s : solver.moves()) System.out.println(s);
    }
}