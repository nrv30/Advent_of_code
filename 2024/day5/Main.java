// reference: https://www.youtube.com/watch?v=TymMkbH8e6A

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Scanner;
import java.io.File;

public class Main {
    public static void main(String[] args) throws Exception {

        HashMap<Integer, ArrayList<Integer>> map = new HashMap<>();
        ArrayList<ArrayList<Integer>> grid = new ArrayList<>(); // just for logging
        ArrayList<ArrayList<Integer>> fail_grid = new ArrayList<>();
        Scanner scanner = new Scanner(new File("input.txt"));

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (line.contains("|")) {
                build_map(line, map);
            } else if (line.contains(",")) {
                build_grid(line, grid);
            }

        }

        System.out.println("MAP ----");
        System.out.println(map);

        System.out.println("GRID -----");
        System.out.println(grid);
        
        System.out.println("sorted Fail Grid");
        for (ArrayList<Integer> list : fail_grid) {
            System.out.println(list);
        }
        int valid_rows = solve(map, grid, fail_grid);
        System.out.println("valid rows: " + valid_rows);


        scanner.close();
    }
    
    public static void build_map(String line, HashMap<Integer, ArrayList<Integer>> map) {
        int pipe_index = line.indexOf('|');
        int key = Integer.parseInt(line.substring(0, pipe_index));
        int dep = Integer.parseInt(line.substring(pipe_index+1, line.length()));
        
        if (map.containsKey(key)) {
            map.get(key).add(dep);
        } else {
            ArrayList<Integer> ints = new ArrayList<>();
            ints.add(dep);
            map.put(key, ints);        
        }   

    }

    public static void build_grid(String line, ArrayList<ArrayList<Integer>> grid) {
        ArrayList<Integer> row = new ArrayList<>();
        String row_strings[] = line.split(",");
        for (String s : row_strings) {
            row.add(Integer.parseInt(s));
        }
        grid.add(row);
    }

    // 2 | 3
    // 4 | 3
    // 1 3 2 4 5 
    public static int solve(HashMap<Integer, ArrayList<Integer>> map, ArrayList<ArrayList<Integer>> grid, 
                            ArrayList<ArrayList<Integer>> fail_grid) 
    {
        int total = 0;
        for (int i = 0; i < grid.size(); i++) { // iterate by row
            ArrayList<Integer> row = grid.get(i);
            boolean is_valid = true;
            for (int j = 1; j < row.size(); j++) { // iterate by elem
                Integer current = row.get(j);
                ArrayList<Integer> deps =  map.get(current);
                if ( deps != null) {
                    for (int k = 0; k < j; k++) { // iterate from 0 to elem
                        if (deps.contains(row.get(k))) {
                            // System.out.println(row);
                            fix_row(row, map, current, j, k);
                            is_valid = false;
                        }
                    } 
                }
            }
            if (!is_valid) {
                fail_grid.add(row);
                total += row.get(row.size()/2);
            }
        }
        return total;
    }

    public static void fix_row(ArrayList<Integer> row, HashMap<Integer, ArrayList<Integer>> map, Integer current, int current_index, int target_index) {
        // row.remove(current_index);
        // row.add(target_index, current);
        Collections.swap(row, current_index, target_index);
    }
}



