import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int N = Integer.parseInt(br.readLine());
        
        StringBuilder sb = new StringBuilder();
        for(int i = 1; i < 2 * N; i++) {
            int blank = abs(-1 * i + N);
            int star = -1 * abs(2 * (i - N)) + (2 * N - 1);
            for(int j = 0; j < blank; j++)
                sb.append(' ');
            for(int j = 0; j < star; j++)
                sb.append('*');
            
            sb.append("\n");
        }
        
        System.out.println(sb.toString());
    }
    public static int abs(int num){
        if(num < 0)
            return -1 * num;
        else
            return num;
    }
}