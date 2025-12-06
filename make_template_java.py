template = '''\
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner f = new Scanner(new File(args[0]))
        
        while (scanner.hasNext()) {
            System.out.println(scanner.nextLine());
        }
        f.close();   
    }
}\
'''

file = open('Main.java', 'w')
file.write(template)
file.close()

print('Success!, Main.java created')

