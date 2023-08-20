import java.util.*;
import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        
        String str = br.readLine();
        for(int i = 0; i < str.length(); i++) {
            bw.write(str.charAt(i));
            bw.newLine();
        }
        bw.flush();
        bw.close();
        br.close();
    }
}