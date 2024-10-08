import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int[] arr = new int[42];
        
        for(int i = 0; i < 10; i++) {
            int tempResult = Integer.parseInt(br.readLine()) % 42;
            arr[tempResult]++;
        }
        
        int count = 0;
        for(int i = 0; i < arr.length; i++)
            if(arr[i] != 0)
                count++;
        
        System.out.println(count);
    }
}