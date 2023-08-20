import java.util.*;
import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        
        int n = Integer.parseInt(br.readLine());
        
        if(n % 2 == 0)
            bw.write(Integer.toString(n) + " is even");
        else
            bw.write(Integer.toString(n) + " is odd");
        bw.flush();
        bw.close();
        br.close();
    }
}