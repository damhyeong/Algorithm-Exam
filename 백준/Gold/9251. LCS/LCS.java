import java.util.*;
import java.io.*;

/**
LCS

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.1 초 (하단 참고)	256 MB	89063	36901	27033	40.809%

문제
---
LCS(Longest Common Subsequence, 최장 공통 부분 수열)문제는 두 수열이 주어졌을 때, 

모두의 부분 수열이 되는 수열 중 가장 긴 것을 찾는 문제이다.


예를 들어, ACAYKP와 CAPCAK의 LCS는 ACAK가 된다.

입력
---
첫째 줄과 둘째 줄에 두 문자열이 주어진다. 문자열은 알파벳 대문자로만 이루어져 있으며, 최대 1000글자로 이루어져 있다.

출력
---
첫째 줄에 입력으로 주어진 두 문자열의 LCS의 길이를 출력한다.

예제 입력 1 
ACAYKP
CAPCAK
예제 출력 1 
4
 */


/**
이는 부분집합에 대한 이해도가 필요하며, 2차원 dp배열을 이용하여 풀어야 한다.
현재 풀어진 문제는 0.2초 내를 위한 간단한 코드이지만, 다른 방식도 존재 할 것이라고 생각한다. 

힌트 : 
1. 각 최대 부분수열은 순서가 유지되어야 한다.
2. 1번째 문자열에서 Y, 두 번째 문자열에서 K가 선택되었다면, {A, C, A, Y}, {C, A, P, C, A, K} 간의 최대 수열을 의미한다.
3. 처음에 {A}, {C} | {A}, {C, A} | {A}, {C, A, P} | .... | {A}, {C, A, P, C, A, K} 간의 최대 수열을 구한다고 생각하면 된다.
4. 그 다음은 {A, C} , {C} | {A, C} , {C, A} | ..... 이런식으로 비교한다. 
5. 이에 대한 점화식을 구하여 dp 배열로 구현하는데, 해석하는 것이 꽤나 어려울 것이다. 
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String str1 = br.readLine().trim();
		String str2 = br.readLine().trim();
		
		// str1을 char 배열화시켜 최적화.
		char[] chStr1 = str1.toCharArray();
		
		// str2를 char 배열화시켜 최적화.
		char[] chStr2 = str2.toCharArray();
		
		int max = 0;
		
		int[][] dp = new int[chStr1.length + 1][chStr2.length + 1];
		
		for(int i = 0; i < chStr1.length; i++) {
			for(int j = 0; j < chStr2.length; j++) {
				
				if(chStr1[i] == chStr2[j]) {
					dp[i + 1][j + 1] = dp[i][j] + 1;
				} else {
					dp[i + 1][j + 1] = Math.max(dp[i][j + 1], dp[i + 1][j]);
				}
				max = (max < dp[i + 1][j + 1]) ? dp[i + 1][j + 1] : max;
			}
		}
		
		
		System.out.println(max);
	}

}