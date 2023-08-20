
import java.util.*;
import java.io.*;

/**
부녀회장이 될테야
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.5 초 (추가 시간 없음)	128 MB	93752	52286	44535	56.992%
문제
평소 반상회에 참석하는 것을 좋아하는 주희는 이번 기회에 부녀회장이 되고 싶어 각 층의 사람들을 불러 모아 반상회를 주최하려고 한다.

이 아파트에 거주를 하려면 조건이 있는데, 
“a층의 b호에 살려면 자신의 아래(a-1)층의 1호부터 b호까지 사람들의 수의 합만큼 사람들을 데려와 살아야 한다” 
는 계약 조항을 꼭 지키고 들어와야 한다.

아파트에 비어있는 집은 없고 모든 거주민들이 이 계약 조건을 지키고 왔다고 가정했을 때,
 주어지는 양의 정수 k와 n에 대해 k층에 n호에는 몇 명이 살고 있는지 출력하라. 
 단, 아파트에는 0층부터 있고 각층에는 1호부터 있으며, 0층의 i호에는 i명이 산다.

입력
첫 번째 줄에 Test case의 수 T가 주어진다. 그리고 각각의 케이스마다 입력으로 첫 번째 줄에 정수 k, 두 번째 줄에 정수 n이 주어진다

출력
각각의 Test case에 대해서 해당 집에 거주민 수를 출력하라.

제한
1 ≤ k, n ≤ 14
예제 입력 1 
2
1
3
2
3
예제 출력 1 
6
10
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int T = Integer.parseInt(br.readLine());
		
		int[][] dp = new int[15][15];
		
		for(int i = 1; i <= 14; i++) {
			dp[0][i] = i;
		}
		for(int i = 1; i <= 14; i++) {
			for(int j = 1; j <= 14; j++) {
				int sum = 0;
				for(int k = 1; k <= j; k++) {
					sum += dp[i - 1][k];
				}
				dp[i][j] = sum;
			}
		}
		
		while(T --> 0) {
			int k = Integer.parseInt(br.readLine());
			int n = Integer.parseInt(br.readLine());
			bw.write(Integer.toString(dp[k][n]) + "\n");
		}
		bw.flush();
		bw.close();
		br.close();
	}

}
