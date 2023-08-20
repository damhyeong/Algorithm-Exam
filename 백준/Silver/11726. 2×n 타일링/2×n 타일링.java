
import java.util.*;
import java.io.*;

/**
2×n 타일링
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	150070	57748	42799	36.399%
문제
2×n 크기의 직사각형을 1×2, 2×1 타일로 채우는 방법의 수를 구하는 프로그램을 작성하시오.

아래 그림은 2×5 크기의 직사각형을 채운 한 가지 방법의 예이다.



입력
첫째 줄에 n이 주어진다. (1 ≤ n ≤ 1,000)

출력
첫째 줄에 2×n 크기의 직사각형을 채우는 방법의 수를 10,007로 나눈 나머지를 출력한다.

예제 입력 1 
2
예제 출력 1 
2
예제 입력 2 
9
예제 출력 2 
55
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int n = Integer.parseInt(br.readLine());
		int[] dp = new int[1001];
		
		dp[1] = 1; dp[2] = 2; dp[3] = 3; dp[4] = 5;
		for(int i = 5; i <= 1000; i++) {
			dp[i] = (dp[i - 1]) + (dp[i - 2]);
			dp[i] %= 10007;
		}
		
		bw.write(Integer.toString(dp[n]));
		bw.flush();
		bw.close();
		br.close();
	}

}
