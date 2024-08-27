import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int N = Integer.parseInt(br.readLine());
        
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        int min = Integer.parseInt(st.nextToken());
        int max = min;
        
        for(int i = 1; i < N; i++) {
            int num = Integer.parseInt(st.nextToken());
            min = (min > num) ? num : min;
            max = (max < num) ? num : max;
        }
        
        System.out.println(min + " " + max);
    }
}