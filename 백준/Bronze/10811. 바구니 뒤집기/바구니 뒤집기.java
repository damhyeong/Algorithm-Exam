import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());
        
        int[] arr = new int[N];
        
        for(int i = 0; i < N; i++)
            arr[i] = i + 1;
        
        // M 번 순회 시작 
        for(int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            
            // I 번 부터 J 번 까지 바구니 역순으로 만들어라.
            int I = Integer.parseInt(st.nextToken());
            int J = Integer.parseInt(st.nextToken());
            
            // 역순을 기억할 임시 저장소 생성 - 1, 3번 바구니면 3개 생성
            int[] tempArr = new int[J - I + 1]; 
            
            // j 는 바구니 역순 접근, x 는 0 부터 시작하는 삽입 용도 
            for(int j = J - 1, x = 0; j >= I - 1; j--, x++)
                tempArr[x] = arr[j];
            
            // j 는 기본 배열의 삽입 용도, 임시 배열은 0 부터 시작하게끔 만듬.
            for(int j = I - 1; j <= J - 1; j++)
                arr[j] = tempArr[j - (I - 1)];
        }
        
        // 최종 출력은 공백과 함께다. 
        for(int i = 0; i < N; i++)
            System.out.print(arr[i] + " ");
    }
}