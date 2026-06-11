import java.util.ArrayList;
import java.util.Arrays;
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

        Solution1.solve(grid);

    }

// reference: https://aoc.winslowjosiah.com/solutions/2025/day/7/
class Solution1 {
    static void solve(List<String> grid) {
        boolean [] beams = new boolean[grid.get(0).length()];
        int splitCount = 0;

        int start = grid.get(0).indexOf("S");
        beams[start] = true;

        for (int i = 0; i < grid.size(); ++i) {
            // System.out.printf("------%d-----\n", i);
            for (int j = 0; j < grid.get(0).length(); ++j) {
                char c = grid.get(i).charAt(j);
                // System.out.println(j);
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
}

}