import java.util.*;
import java.io.*;
import java.math.*;

public class Main {

    public record Point(long x, long y, long z) {}
    public record Triplet(long d, int i, int j) implements Comparable<Triplet> {
        
        @Override
        public int compareTo(Triplet o) {
            return Long.compare(this.d, o.d);
        }
    }

    public static long dist(Point p1, Point p2) {
        return (long) Math.pow(p1.x-p2.x, 2) + 
                (long) Math.pow(p1.y-p2.y, 2) + 
                (long) Math.pow(p1.z-p2.z, 2);
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner f = new Scanner(new File(args[0]));
        ArrayList<Point> boxes = new ArrayList<>(); 
        while (f.hasNext()) {
            String values[] = f.nextLine().split(",");
            boxes.add(new Point(Integer.parseInt(values[0]), 
                                Integer.parseInt(values[1]), 
                                Integer.parseInt(values[2])));
        }
        f.close();

        Solution.solveP1Sort(boxes);
    }

    class Solution {

        static HashSet<Integer> getCircuitContainingBox(ArrayList<HashSet<Integer>> circuits, Integer index) {
            for (HashSet<Integer> circuit : circuits) {
                if (circuit.contains(index))
                    return circuit;
            }
            return null;
        }

        static void solveP1Sort(ArrayList<Point>boxes) {
            ArrayList<Triplet> dists = new ArrayList<>();
            for (int i = 0; i < boxes.size(); ++i) {
                for (int j = i+1; j < boxes.size(); ++j) {
                    //System.out.println(boxes.get(i) + " " + boxes.get(j) + " " + distance(boxes.get(i), boxes.get(j)));
                    dists.add(new Triplet(dist(boxes.get(i), boxes.get(j)), i, j));
                }
            }

            Collections.sort(dists, null);
            // for (Triplet t : dists) {
            //     System.out.println(t);
            // }
            ArrayList<HashSet<Integer>> circuits = new ArrayList<>();

            int n = 1000;
            for (int k = 0; k < n; k++) {
                Triplet t = dists.get(k);
                // System.out.println(boxes.get(t.i) + " " + boxes.get(t.j));
                HashSet<Integer> c1 = getCircuitContainingBox(circuits, t.i);
                HashSet<Integer> c2 = getCircuitContainingBox(circuits, t.j);
                // if (c1 != null) {
                //     System.out.println("c1 " + c1);
                // } else if (c2 != null) {
                //     System.out.println("c2 " + c2);
                // }

                if (c1 == null && c2 == null) {
                    circuits.add(new HashSet<Integer>(Arrays.asList(t.i, t.j)));
                } else if (c1 != null && c2 == null) {
                    c1.add(t.j);
                } else if (c2 != null && c1 == null) {
                    c2.add(t.i);
                } else  if (c1 != null && c2 != null && !c1.equals(c2)) {
                    c1.addAll(c2);
                    circuits.remove(c2);
                }
            }

            Comparator<HashSet<Integer>> customComparator = new Comparator<HashSet<Integer>>() {
                public int compare(HashSet<Integer> s1, HashSet<Integer> s2) {
                    return -Integer.compare(s1.size(), s2.size());
                }
            };

            Collections.sort(circuits, customComparator);

            // for (HashSet<Integer> circuit : circuits) {
            //     System.out.println(circuit);
            // }

            System.out.println(circuits.get(0).size()*circuits.get(1).size()*circuits.get(2).size());

        }
    }
}