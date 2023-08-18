
import java.util.*;
import java.io.*;

/**
1로 만들기
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.15 초 (하단 참고)	128 MB	269227	90531	57877	32.676%
문제
정수 X에 사용할 수 있는 연산은 다음과 같이 세 가지 이다.

X가 3으로 나누어 떨어지면, 3으로 나눈다.
X가 2로 나누어 떨어지면, 2로 나눈다.
1을 뺀다.
정수 N이 주어졌을 때, 위와 같은 연산 세 개를 적절히 사용해서 1을 만들려고 한다. 연산을 사용하는 횟수의 최솟값을 출력하시오.

입력
첫째 줄에 1보다 크거나 같고, 10^6보다 작거나 같은 정수 N이 주어진다.

출력
첫째 줄에 연산을 하는 횟수의 최솟값을 출력한다.

예제 입력 1 
2
예제 출력 1 
1
예제 입력 2 
10
예제 출력 2 
3
힌트
10의 경우에 10 → 9 → 3 → 1 로 3번 만에 만들 수 있다.
 */

public class Main {
	public static int[] dp;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int X = Integer.parseInt(br.readLine());
		
		dp = new int[X + 1];
		
		int result = getSequence(X);
		
		bw.write(Integer.toString(result));
		bw.flush();
		bw.close();
		br.close();
	}
	public static int getSequence(int x) {
		
		if(x == 1)
			return 0;
		if(x == 2)
			return 1;
		if(x == 3)
			return 1;
		
		if(x >= 4) {
			dp[1] = 0;
			dp[2] = 1;
			dp[3] = 1;
		}
		/*
		 상황 1 : 3으로 나누어 떨어진다면, 3으로 나눈다.
		 상황 2 : 2 로 나누어 떨어진다면, 2로 나눈다.
		 상황 3 : 1을 뺀다.
		 But, 10의 경우, 2로 나누어 떨어지지만, 먼저 1을 뺀 뒤, 3으로 나눈다.
		 */
		for(int i = 4; i <= x; i++) {
			int min = Integer.MAX_VALUE;
			
			// 현재 숫자에서 1을 뺀 숫자가 3으로 나눠질 경우, 2로 나누는 것보다 더 작아지므로, 중간에 계산을 넣는다. 
			if(i % 6 == 0) {
				dp[i] = Math.min(dp[i - 1], Math.min(dp[i / 2], dp[i / 3])) + 1;
			}else if (i % 3 == 0)
				dp[i] = Math.min(dp[i / 3], dp[i - 1]) + 1;
			else if (i % 2 == 0)
				dp[i] = Math.min(dp[i / 2], dp[i - 1]) + 1;
			else
				dp[i] = dp[i - 1] + 1;
		}
		return dp[x];
	}
}
