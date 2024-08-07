import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        // 무한히 반복한다.
        while(true) {
            // 하나의 줄을 읽고, 토큰으로 분리할 유틸리티 클래스 선언 
            StringTokenizer st = new StringTokenizer(br.readLine());
            
            int A = Integer.parseInt(st.nextToken());
            int B = Integer.parseInt(st.nextToken());
            
            // 루프 탈출 조건
            if(A == 0 && B == 0)
                break;
            
            // 출력 
            System.out.println(A + B);
        }
    }
}