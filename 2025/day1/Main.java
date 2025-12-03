import java.io.*;
import java.util.*;
import java.math.*;;

public class Main {
    public static void main(String[] args) throws FileNotFoundException{
        Scanner file = new Scanner(new File(args[0]));
        int pos = 50;
        int count = 0;
        while (file.hasNextLine()) {
            String line = file.nextLine();
            char dir = line.charAt(0);
            int distance = Integer.parseInt(
                           line.substring(1).strip());
            
            int nextLocation;
            if (dir == 'L') {
                nextLocation = pos - distance;
                System.out.printf("%d-%d=%d\n", pos, distance, nextLocation);
            } else {
                nextLocation = pos + distance;
                System.out.printf("%d+%d=%d\n", pos, distance, nextLocation);
            }

            if (args[1] == "part 1") {
                pos = nextLocation >= 100
                    ? nextLocation % 100 
                    : nextLocation < 0 
                        ? nextLocation % -100 < 0 
                            ? nextLocation % -100 + 100 
                            : nextLocation % -100 
                    : nextLocation;

                if (pos==0) {
                    count++;
                }
     
            } else {
                if (nextLocation >= 100) {
                    // if (pos != 0)
                        count += nextLocation / 100;
                    pos = nextLocation % 100;
                    } else if (nextLocation < 0) {
                        if (pos != 0)
                            count+= Math.abs(Math.floorDiv(nextLocation, 100));
                        pos = Math.floorMod(nextLocation, 100);
                    } else {
                        pos = nextLocation;
                    }

                    if (pos == 0)
                        count++;
            } 
        }
        System.out.println("answer: " + count);
        file.close();
    }
}