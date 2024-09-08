import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        br.readLine();
        
        String str = br.readLine().trim();
        
        int sum = 0;
        
        for (int i = 0; i < str.length(); i++) {
            char chNum = str.charAt(i);
            
            sum += Character.getNumericValue(chNum);
        }
        
        System.out.println(sum);
    }
}