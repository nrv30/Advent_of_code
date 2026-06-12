import java.util.ArrayList;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.io.IOException;
import java.util.List;

public class Main {

    // public record Point(int x, int y) {}

    // boolean validLocation() {
    //     return false;
    // }

    // char value_at_point(List<String> grid, Point p) {
    //     return grid.get(p.y).charAt(p.x);
    // }

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Missing filepath");
            return;
        }
        Path filepath = Paths.get(args[0]);

        List<String> grid = new ArrayList<>();

        try {
            grid = Files.readAllLines(filepath);
        } catch (IOException e) {
            System.out.println("error reading file");
            return;
        }

        //Solution1.solve(grid);
        Solution1.solve2(grid);

    }

// reference: https://aoc.winslowjosiah.com/solutions/2025/day/7/
// https://joshcena.com/notes/aoc/2025/7/
// these both took the same approach but copying the python code to java leads to a bug
// because the original beams array shouldn't be modified while iterating
// and rust code was easier for me to understand / similar to java
// Problem statement was super confusing for me with this one idk
    class Solution1 {
        static long sum (long[] nums) {
            long sum = 0;
            for (int i = 0; i < nums.length; ++i) {
                sum += nums[i];
            }
            return sum;
        }

        static void solve(List<String> grid) {
            boolean [] beams = new boolean[grid.get(0).length()];
            int splitCount = 0;

            int start = grid.get(0).indexOf("S");
            beams[start] = true;

            for (int i = 0; i < grid.size(); ++i) {
                for (int j = 0; j < grid.get(0).length(); ++j) {
                    char c = grid.get(i).charAt(j);
                    if (!(c == '^' && beams[j]))
                        continue;

                    splitCount++;
                    beams[j-1] = true;
                    beams[j+1] = true;
                    beams[j] = false;
                }
            }
            System.out.println("Answer: " + splitCount);
        }

        static void solve2(List<String>grid) {
            long[] beams = new long[grid.get(0).length()];
            beams[grid.get(0).indexOf('S')] = 1;
            for (int i = 1; i < grid.size(); ++i) {
                long[] newBeams = new long[grid.get(i).length()];
                for (int j = 0; j < newBeams.length; ++j) {
                    char c = grid.get(i).charAt(j);
                    if (c == '^') {
                        // I don't think bounds checks are necesary for the input
                        if (j > 0) {
                            newBeams[j-1] += beams[j];
                        }
                        
                        if (j + 1 < newBeams.length) {
                            newBeams[j+1] += beams[j];
                        }
                    } else {
                        newBeams[j] += beams[j];
                    }
                }
                beams = newBeams;
            }
            System.out.println(sum(beams));
        }
    }

}