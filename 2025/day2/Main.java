import java.util.*;
import java.io.*;

public class Main {

    public static boolean invalidID(String idString) {
        int mid = idString.length() / 2;
        // System.out.println(idString.substring(0, mid) + " " + idString.substring(mid));
        return idString.substring(0, mid).equals(idString.substring(mid));
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner f = new Scanner(new File(args[0])).useDelimiter(",");
        long count = 0;
        while (f.hasNext()) {
            String rangeStr = f.next().strip();
            long rangeStart = Long.parseLong(
                                rangeStr.substring(0, 
                                rangeStr.indexOf('-')));
            long rangeEnd   = Long.parseLong(
                                rangeStr.substring(
                                rangeStr.indexOf('-') + 1));

            // System.out.printf("start: %d end: %d\n", rangeStart, rangeEnd);

            for (long id = rangeStart; id <= rangeEnd; id++) {
                String idString = String.valueOf(id);
                if (idString.length() % 2 == 0 && invalidID(idString)) {
                    System.out.println(idString);
                    count+= id;
                }
            }
        }
        System.out.println("answer: " + count);
        f.close();
    }
}