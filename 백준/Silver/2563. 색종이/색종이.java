import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int loop = Integer.parseInt(br.readLine());
        
        // 정해진 도화지의 넓이는 100 * 100
        boolean[][] areas = new boolean[100][100];
        
        /*
         1 번째 - loop = 3
         2 번째 - loop = 2
         3 번째 - loop = 1
         4 번째 - loop = 0 XXXX
         즉, 후위 연산자를 통해 나중에 계산하는 것.
         */
        while(loop-- > 0) { // while(--loop >= 0) 도 동일한 로직.
            StringTokenizer st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            
            for(int i = x; i < x + 10; i++) {
                for (int j = y; j < y + 10; j++) {
                    areas[i][j] = true;
                }
            }
        }
        
        int black = 0;
        for(int i = 0; i < areas.length; i++) {
            for (int j = 0; j < areas[0].length; j++) {
                if (areas[i][j])
                    black++;
            }
        }
        System.out.println(black);
    }
}