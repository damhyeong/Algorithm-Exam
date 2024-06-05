import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int N = Integer.parseInt(br.readLine());
        int[][] lines = new int[N][2];
        
        for (int i = 0; i < N; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            lines[i][0] = Integer.parseInt(st.nextToken());
            lines[i][1] = Integer.parseInt(st.nextToken());
        }
        
        // A 전봇대 기준으로 정렬
        quickSort(lines, 0, N - 1);
        
        // DP를 사용하여 LIS 계산
        int[] dp = new int[N];
        int max = 0;
        for (int i = 0; i < N; i++) {
            dp[i] = 1;
            for (int j = 0; j < i; j++) {
                if (lines[j][1] < lines[i][1]) {
                    dp[i] = Math.max(dp[i], dp[j] + 1);
                }
            }
            max = Math.max(max, dp[i]);
        }
        
        // 전체 전깃줄 수에서 LIS 길이를 빼서 최소 제거 수를 계산
        System.out.println(N - max);
    }

    // 기존 quickSort 로직을 그대로 사용
    public static void quickSort(int[][] arr, int start, int end) {
        if (start >= end) return;
        
        int pivot = start;
        int i = start;
        int j = end;
        
        while (i < j) {
            while (arr[pivot][0] < arr[j][0]) j--;
            while (i < j && arr[pivot][0] >= arr[i][0]) i++;
            swap(arr, i, j);
        }
        
        swap(arr, pivot, i);
        quickSort(arr, start, i - 1);
        quickSort(arr, i + 1, end);
    }
    
    public static void swap(int[][] arr, int i, int j) {
        int temp1 = arr[i][0];
        int temp2 = arr[i][1];
        arr[i][0] = arr[j][0];
        arr[i][1] = arr[j][1];
        arr[j][0] = temp1;
        arr[j][1] = temp2;
    }
}