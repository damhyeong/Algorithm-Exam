import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        // 블랙 피스 
        int[] pieces = {1, 1, 2, 2, 2, 8};
        
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < pieces.length; i++) {
            int piece = Integer.parseInt(st.nextToken());
            sb.append(pieces[i] - piece).append(" ");
        }
        
        System.out.println(sb.toString());
    }
}