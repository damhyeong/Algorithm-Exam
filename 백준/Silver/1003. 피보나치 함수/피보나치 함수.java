
import java.util.*;
import java.io.*;

/**
피보나치 함수
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.25 초 (추가 시간 없음)	128 MB	197571	59432	46780	32.613%
문제
다음 소스는 N번째 피보나치 수를 구하는 C++ 함수이다.

int fibonacci(int n) {
    if (n == 0) {
        printf("0");
        return 0;
    } else if (n == 1) {
        printf("1");
        return 1;
    } else {
        return fibonacci(n‐1) + fibonacci(n‐2);
    }
}
fibonacci(3)을 호출하면 다음과 같은 일이 일어난다.

fibonacci(3)은 fibonacci(2)와 fibonacci(1) (첫 번째 호출)을 호출한다.
fibonacci(2)는 fibonacci(1) (두 번째 호출)과 fibonacci(0)을 호출한다.
두 번째 호출한 fibonacci(1)은 1을 출력하고 1을 리턴한다.
fibonacci(0)은 0을 출력하고, 0을 리턴한다.
fibonacci(2)는 fibonacci(1)과 fibonacci(0)의 결과를 얻고, 1을 리턴한다.
첫 번째 호출한 fibonacci(1)은 1을 출력하고, 1을 리턴한다.
fibonacci(3)은 fibonacci(2)와 fibonacci(1)의 결과를 얻고, 2를 리턴한다.
1은 2번 출력되고, 0은 1번 출력된다. N이 주어졌을 때, fibonacci(N)을 호출했을 때, 0과 1이 각각 몇 번 출력되는지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 테스트 케이스의 개수 T가 주어진다.

각 테스트 케이스는 한 줄로 이루어져 있고, N이 주어진다. N은 40보다 작거나 같은 자연수 또는 0이다.

출력
각 테스트 케이스마다 0이 출력되는 횟수와 1이 출력되는 횟수를 공백으로 구분해서 출력한다.

예제 입력 1 
3
0
1
3
예제 출력 1 
1 0
0 1
1 2
예제 입력 2 
2
6
22
예제 출력 2 
5 8
10946 17711
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int T = Integer.parseInt(br.readLine());
		
		int[][] dp = new int[41][2];
		
		dp[0][0] = 1; dp[0][1] = 0; 
		dp[1][0] = 0; dp[1][1] = 1;
		dp[2][0] = 1; dp[2][1] = 1;
		dp[3][0] = 1; dp[3][1] = 2;
		dp[4][0] = 2; dp[4][1] = 3;
		for(int i = 5; i <= 40; i++) {
			for(int j = 0; j < 2; j++) {
				dp[i][j] = dp[i - 1][j] + dp[i - 2][j];
			}
		}
		
		while(T --> 0) {
			int N = Integer.parseInt(br.readLine());
			bw.write(Integer.toString(dp[N][0]) + " " + Integer.toString(dp[N][1]) + "\n");
		}
		bw.flush();
		bw.close();
		br.close();
	}

}
