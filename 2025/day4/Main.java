// https://www.reddit.com/r/adventofcode/comments/1pe3xwh/2025_day_4_go_spoiler_why_dont_we_need_to_add_a/

import java.util.*;
import java.io.*;

public class Main {

    static int offsets [][] = {
                        new int[] {-1, 1}, 
                        new int[] {-1, -1},
                        new int[] {0, -1},
                        new int[] {0, 1},
                        new int[] {1, 0},
                        new int[] {-1, 0},
                        new int[] {1, 1},
                        new int[] {1, -1}
                        };
    static int rowSize;
    static int colSize;

    public static void buildGrid(boolean[] grid, ArrayList<String> lines) {
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                int index = colSize * i + j;
                char ch = lines.get(i).charAt(j);
                if (ch == '@') {
                    grid[index] = true;
                } else {
                    grid[index] = false;
                }
            }
        }
    }

    public static boolean accessible(boolean[] grid, int rows, int cols) {
        int count = 0;
        for (int p = 0; p < offsets.length; p++) {
            int x = rows+offsets[p][0];
            int y = cols+offsets[p][1];
            if (x > -1 && x < rowSize && y > -1 && y < colSize && grid[x*colSize+y]) {
                count++;
            }
            if (count >= 4)
                break;
        }

        return count < 4;
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner f = new Scanner(new File(args[0]));
        ArrayList<String> lines = new ArrayList<>();
        while (f.hasNext()) {
            lines.add(f.nextLine().strip());
        }
        f.close();   
        
        colSize = lines.get(0).length();
        rowSize = lines.size();
        boolean grid[] = new boolean[rowSize * colSize];

        buildGrid(grid, lines);
        
        int rollsOfPaper = 0;
        for (int rows = 0; rows < rowSize; rows++) {
            for (int cols = 0; cols < colSize; cols++) {
                if (grid[rows*colSize+cols] && accessible(grid, rows, cols)) {
                    rollsOfPaper++;
                }
            }
        }

        System.out.println("accessible paper rolls " + rollsOfPaper);
    }
}