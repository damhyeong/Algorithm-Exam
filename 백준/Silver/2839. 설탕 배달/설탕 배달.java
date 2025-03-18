import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        // 배달해야 할 총 설탕의 KG
        int N = Integer.parseInt(br.readLine());
        
        // DP 를 위한 1 차원 배열 - 최대 입력값까지 생성.
        int[] dp = new int[5001];
        
        // 10 KG 까지 최소값을 저장.
        dp[0] = 0;
        dp[1] = -1;
        dp[2] = -1;
        dp[3] = 1;
        dp[4] = -1;
        dp[5] = 1;
        dp[6] = 2;
        dp[7] = -1;
        dp[8] = 2;
        dp[9] = 3;
        dp[10] = 2;
        
        // 미리 KG 에 따른 최소값을 저장해 두기 위한 반복문 
        for(int i = 11; i <= 5000; i++) {
            dp[i] = -1;
            
            // 현재 인덱스가 현재 KG 을 의미한다.
            int currKG = i;
            
            // 5KG 몫 저장
            int KG5 = currKG / 5;
            
            // 음수가 아닐 때 까지 진행. - 최대 5KG 봉지 수에서 하나씩 줄여가며 체크
            while (currKG >= 0) {
                // 5KG 봉지를 빼고 남은 설탕 무게.
                int remain = i - (KG5 * 5);
                
                // 현재 남은 설탕에서 3으로 나누어진다면,
                if(remain % 3 == 0) {
                    // 현재 5KG 설탕 봉지 + 3KG 설탕 봉지가 최소 값이다.
                    dp[i] = KG5 + (remain / 3);
                    break;
                }
                
                // 딱 나누어지지 않기 때문에, 5KG 봉지를 하나 뺀다.
                KG5--;
            }
        }
        
        // 최소값까지 이미 계산해 놓은 상황에서, 주어진 "N" 키로를 바로 출력한다.
        System.out.println(dp[N]);
    }
}