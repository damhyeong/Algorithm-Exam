import java.util.*;
import java.io.*;

/**
쉬운 계단 수

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	149600	48374	35359	30.729%

문제
----
45656이란 수를 보자.

이 수는 인접한 모든 자리의 차이가 1이다. 이런 수를 계단 수라고 한다.

N이 주어질 때, 길이가 N인 계단 수가 총 몇 개 있는지 구해보자. 0으로 시작하는 수는 계단수가 아니다.

입력
----
첫째 줄에 N이 주어진다. N은 1보다 크거나 같고, 100보다 작거나 같은 자연수이다.

출력
----
첫째 줄에 정답을 1,000,000,000으로 나눈 나머지를 출력한다.

예제 입력 1 
1
예제 출력 1 
9
예제 입력 2 
2
예제 출력 2 
17

 */

/**
	N = 1 일 경우, 1, 2, 3, 4, 5, 6, 7, 8, 9 => 총 9개
	N = 2 일 경우, 10, 12, 21, 23, 32, 34, 43, 45, 54, 56, 65, 67, 76, 78, 87, 89, 98 => 17
 */

public class Main {
	public static final long DIVIDE = 1_000_000_000;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		long[][] costs = new long[N][10];
		
		for(int i = 1; i < 10; i++)
			costs[0][i] = 1;
		
		for(int i = 1; i < N; i++) {
			for(int j = 0; j < 10; j++) {
				if(j == 0) {
					costs[i][j] = costs[i - 1][1] % DIVIDE;
				} else if(j == 9) {
					costs[i][j] = costs[i - 1][8] % DIVIDE;
				} else {
					costs[i][j] = (costs[i - 1][j - 1] % DIVIDE) + (costs[i - 1][j + 1] % DIVIDE);
				}
			}
		}
		
		long result = 0;
		
		for(int i = 0; i < 10; i++) {
			result = (result + costs[N - 1][i]) % DIVIDE;
		}
		
		System.out.println(result);
	}

}
