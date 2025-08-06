import java.io.*;
import java.util.HashSet;
import java.util.Objects;
import java.util.Scanner;
// import java.awt.Point;
public class Main{
     
    public static void main(String[] args) throws IOException {
        Point origin = new Point();
        HashSet<Point> points = new HashSet<>();
        points.add(origin);
        FileReader input = new FileReader("test.txt");
        int c;
        Point santa = new Point();
        Point robo = new Point();
        int i = 0;
        while((c = input.read()) != -1) {
            // System.out.print((char)c);
            Point z;
            if (i % 2 == 0) {
                update((char)c, santa);
                z = new Point(santa.x, santa.y);
            } else {
                update((char)c, robo);
                z = new Point(robo.x, robo.y);
            }

            points.add(z); 
            i++;
        }
        input.close();

        System.out.println(points.size());

        // for (Point p : points) {
        //     System.out.println(p);
        // }
    }

    public static void update(char c, Point p) {
        switch (c) {
            case '<':
                p.x -= 1;
                break;
            case '^':
                p.y += 1;
                break;
            case '>':
                p.x += 1;
                break;
            case 'v':
                p.y -= 1;
                break;
            default: break;
        }
    }
}

public class Point {
    int x, y;
    
    Point() {
        this.x = 0;
        this.y = 0;
    } 
    Point(int x, int y) {
        this.x = x; 
        this.y = y;
    }

    public String toString() {
        return String.format("X: %d  Y: %d", this.x, this.y);
    }

    public boolean equals(Object obj) {
        Point p = (Point) obj;
        if (this.x == p.x && this.y == p.y) return true;
        else return false;
    }

    public int hashCode() {
        return Objects.hash(this.x, this.y);
    }

    public void add(Point p) {
        this.x += p.x;
        this.y += p.y;
    }

}