
import java.util.*;
import java.io.*;

/**
2×n 타일링 2
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	65598	39070	31405	58.980%
문제
2×n 직사각형을 1×2, 2×1과 2×2 타일로 채우는 방법의 수를 구하는 프로그램을 작성하시오.

아래 그림은 2×17 직사각형을 채운 한가지 예이다.

입력
첫째 줄에 n이 주어진다. (1 ≤ n ≤ 1,000)

출력
첫째 줄에 2×n 크기의 직사각형을 채우는 방법의 수를 10,007로 나눈 나머지를 출력한다.

예제 입력 1 
2
예제 출력 1 
3
예제 입력 2 
8
예제 출력 2 
171
예제 입력 3 
12
예제 출력 3 
2731
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		int n = Integer.parseInt(br.readLine());
		int[] dp = new int[n + 1];
		int[] arr = new int[n + 1];
		
		if(n == 1)
			bw.write("1");
		else if(n == 2)
			bw.write("3");
		else {
			dp[1] = 1; arr[1] = 1;
			dp[2] = 4; arr[2] = 3;
			for(int i = 3, j = 1; i <= n; i++, j++) {
				arr[i] = arr[i - 1] + (2 * arr[i - 2]);
				arr[i] %= 10007;
			}
			bw.write(Integer.toString(arr[n] % 10007));
		}
		bw.flush();
		bw.close();
		br.close();
	}

}
