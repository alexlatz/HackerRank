import java.util.*;

public class PacmanAStar {
    private static class Pacman implements Comparable<Pacman> {
        int x, y;
        char[][] board;
        int[] fruit;
        int numMoves;
        int manhattan;
        Pacman prev;

        public Pacman(char[][] board, int[] fruit, int x, int y, int numMoves, Pacman prev) {
            this.x = x;
            this.y = y;
            this.board = board;
            this.fruit = fruit;
            this.manhattan = Math.abs(fruit[0] - x) + Math.abs(fruit[1] - y);
            this.numMoves = numMoves;
            this.prev = prev;
        }

        public Iterable<Pacman> moves() {
            ArrayList<Pacman> moves = new ArrayList<>();
            if (x > 0 && board[x - 1][y] != '%') moves.add(new Pacman(board, fruit, x - 1, y, numMoves + 1, this));
            if (x < board.length && board[x + 1][y] != '%')
                moves.add(new Pacman(board, fruit, x + 1, y, numMoves + 1, this));
            if (y > 0 && board[x][y - 1] != '%') moves.add(new Pacman(board, fruit, x, y - 1, numMoves + 1, this));
            if (y < board[0].length && board[x][y + 1] != '%')
                moves.add(new Pacman(board, fruit, x, y + 1, numMoves + 1, this));
            return moves;
        }

        @Override
        public int compareTo(Pacman that) {
            return Integer.compare(this.manhattan + this.numMoves, that.manhattan + that.numMoves);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Pacman pacman = (Pacman) o;
            return x == pacman.x &&
                    y == pacman.y;
        }

    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int y = scan.nextInt();
        int[] pacman = new int[]{scan.nextInt(), y};
        y = scan.nextInt();
        int[] fruit = new int[]{scan.nextInt(), y};
        int rowLength = scan.nextInt();
        char[][] board = new char[scan.nextInt()][rowLength];
        for (int j = 0; j < board.length; j++) {
            String row = scan.next();
            for (int i = 0; i < row.length(); i++) {
                board[i][j] = row.charAt(i);
            }
        }
        PriorityQueue<Pacman> pq = new PriorityQueue<>();
        pq.add(new Pacman(board, fruit, pacman[0], pacman[1], 0, null));
        while (pq.peek().manhattan > 0) {
            Pacman min = pq.poll();
            for (Pacman p : min.moves()) {
                if (min.numMoves == 0) pq.add(p);
                else if (!min.prev.equals(p)) pq.add(p);
            }
        }
        Pacman solved = pq.poll();
        System.out.println(solved.numMoves);
        Deque<String> deque = new ArrayDeque<>();
        while (solved != null) {
            deque.push(solved.y + " " + solved.x);
            solved = solved.prev;
        }
        for (String s : deque) System.out.println(s);
    }
}
