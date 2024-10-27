import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());
        
        // 동적 크기의 배열을 힙 메모리에 저장한다. - N * M 크기 
        int[][] matrixA = new int[N][M];
        int[][] matrixB = new int[N][M];
        
        for(int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < M; j++) {
                matrixA[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        for(int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < M; j++) {
                matrixB[i][j] = Integer.parseInt(st.nextToken());
            }
        }
        
        // 따로 배열을 생성 할 필요 없이, matrixA 에 합을 저장하자.
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                matrixA[i][j] += matrixB[i][j];
            }
        }
        
        // 결과 출력
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                sb.append(matrixA[i][j]).append(" ");
            }
            sb.append("\n");
        }
        
        System.out.println(sb.toString());
    }
}