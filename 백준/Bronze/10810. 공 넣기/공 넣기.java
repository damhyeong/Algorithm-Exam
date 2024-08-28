import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());
        
        int[] arr = new int[N]; // 바구니의 개수 N 
        
        for(int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            int start = Integer.parseInt(st.nextToken());
            int end = Integer.parseInt(st.nextToken());
            int ballNumber = Integer.parseInt(st.nextToken());
            
            insert(arr, start, end, ballNumber);
        }
            
        for(int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
    }
    
    // 공을 넣는 기능을 관심사에서 분리.
    public static void insert(int[] arr, int start, int end, int ballNumber){
        for(int i = start - 1; i < end; i++)
            arr[i] = ballNumber;
    }
}