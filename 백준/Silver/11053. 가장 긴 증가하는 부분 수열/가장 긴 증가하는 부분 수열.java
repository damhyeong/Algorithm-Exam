import java.util.*;
import java.io.*;

/**
가장 긴 증가하는 부분 수열 

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	168582	67722	44926	38.074%

문제
----
수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.

예를 들어, 수열 A = {10, 20, 10, 30, 20, 50} 인 경우에 가장 긴 증가하는 부분 수열은 A = {10, 20, 10, 30, 20, 50} 이고, 길이는 4이다.

입력
----
첫째 줄에 수열 A의 크기 N (1 ≤ N ≤ 1,000)이 주어진다.

둘째 줄에는 수열 A를 이루고 있는 A_i가 주어진다. (1 ≤ A_i ≤ 1,000)

출력
----
첫째 줄에 수열 A의 가장 긴 증가하는 부분 수열의 길이를 출력한다.

예제 입력 1 
6
10 20 10 30 20 50
예제 출력 1 
4
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		int[] arr = new int[N + 1];
		int[] dp = new int[N + 1];
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		for(int i = 1; i < N + 1; i++)
			arr[i] = Integer.parseInt(st.nextToken());
		
		arr[0] = 0; dp[0] = 0;
		
		for(int i = 1; i < N + 1; i++) {
			int tempResult = Integer.MIN_VALUE;
			for(int j = 0; j < i; j++)
				tempResult = (arr[j] < arr[i] && tempResult < dp[j]) ? dp[j] : tempResult;
			
			dp[i] = tempResult + 1;
		}
		
		int max = Integer.MIN_VALUE;
		for(int i = 0; i <= N; i++)
			max = max < dp[i] ? dp[i] : max;
		
		System.out.println(max);
	}

}
