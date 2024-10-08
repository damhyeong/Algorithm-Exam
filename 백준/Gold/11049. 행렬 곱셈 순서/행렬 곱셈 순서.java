import java.util.*;
import java.io.*;

/**
행렬 곱셈 순서

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	37599	16908	12190	43.828%

문제
---
크기가 N×M인 행렬 A와 M×K인 B를 곱할 때 필요한 곱셈 연산의 수는 총 N×M×K번이다. 

행렬 N개를 곱하는데 필요한 곱셈 연산의 수는 행렬을 곱하는 순서에 따라 달라지게 된다.

예를 들어, 

A의 크기가 5×3이고, B의 크기가 3×2, C의 크기가 2×6인 경우에,

행렬의 곱 ABC를 구하는 경우를 생각해보자.


AB를 먼저 곱하고 C를 곱하는 경우 (AB)C에 필요한 곱셈 연산의 수는 5×3×2 + 5×2×6 = 30 + 60 = 90번이다.

BC를 먼저 곱하고 A를 곱하는 경우 A(BC)에 필요한 곱셈 연산의 수는 3×2×6 + 5×3×6 = 36 + 90 = 126번이다.

5 3
3 2
2 6

같은 곱셈이지만, 곱셈을 하는 순서에 따라서 곱셈 연산의 수가 달라진다.

행렬 N개의 크기가 주어졌을 때, 모든 행렬을 곱하는데 필요한 곱셈 연산 횟수의 최솟값을 구하는 프로그램을 작성하시오. 

입력으로 주어진 행렬의 순서를 바꾸면 안 된다.


입력
---
첫째 줄에 행렬의 개수 N(1 ≤ N ≤ 500)이 주어진다.

둘째 줄부터 N개 줄에는 행렬의 크기 r과 c가 주어진다. 

(1 ≤ r, c ≤ 500)

항상 순서대로 곱셈을 할 수 있는 크기만 입력으로 주어진다.


출력
---
첫째 줄에 입력으로 주어진 행렬을 곱하는데 필요한 곱셈 연산의 최솟값을 출력한다. 

정답은 2^31-1 보다 작거나 같은 자연수이다. 

또한, 최악의 순서로 연산해도 연산 횟수가 2^31-1보다 작거나 같다.

Example :

AB : AB

ABC : 

1. (AB)C
2. A(BC)
3. 


예제 입력 1 
3
5 3
3 2
2 6
예제 출력 1 
90

예제 입력 2 - 내가 만듬 
5
5 3
3 2
2 6
6 8
8 2
예제 출력 2
?

 */

/**
백준 11066 과 동일한 dp 문제, 하지만, dp임에도 n^3 문제...
이전의 기록을 토대로 

	5	3	2	6
0	0	0	30	90
1		0	0	36
2			0	0
3				0


예시 :  1 3 2 4 3 5 4 6 5 7 6 8



1	3	2	4	3	5	4	6	5	7	6	8
0	0	6	14	26	41	61	85	115	150	192	240	
0	0	0	24	60	105	165	237	327	432	558	702	
0	0	0	0	24	54	94	142	202	272	356	452	
0	0	0	0	0	60	140	236	356	496	664	856	
0	0	0	0	0	0	60	132	222	327	453	597	
0	0	0	0	0	0	0	120	270	445	655	895	
0	0	0	0	0	0	0	0	120	260	428	620	
0	0	0	0	0	0	0	0	0	210	462	750	
0	0	0	0	0	0	0	0	0	0	210	450	
0	0	0	0	0	0	0	0	0	0	0	336	
0	0	0	0	0	0	0	0	0	0	0	0	
0	0	0	0	0	0	0	0	0	0	0	0

-------

예시 : 8 6 7 5 6 4 5 3 4 2 3 1 

11
8 6
6 7
7 5
5 6
6 4
4 5
5 3
3 4
4 2
2 3
3 1

0	336	616	856	1048	1208	1328	1424	1488	1536	1560	
0	0	210	390	534		654		744		816		864		900		918	
0	0	0	210	378		518		623		707		763		805		826	
0	0	0	0	120		220		295		355		395		425		440	
0	0	0	0	0		120		210		282		330		366		384	
0	0	0	0	0		0		60		108		140		164		176	
0	0	0	0	0		0		0		60		100		130		145	
0	0	0	0	0		0		0		0		24		42		51	
0	0	0	0	0		0		0		0		0		24		36	
0	0	0	0	0		0		0		0		0		0		6	
0	0	0	0	0		0		0		0		0		0		0

예시 : 8 6 7 5

A : 8 6
B : 6 7
C : 7 5

1. (AB)C = (8 * 6 * 7) + (8 * 7 * 5) = 616

2. A(BC) = (6 * 7 * 5) + (8 * 6 * 5) = (210) + (240) = 450

 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		int[][] matrix = new int[N][2];
		
		for(int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			
			int r = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			
			matrix[i][0] = r;
			matrix[i][1] = c;
		}
		
		int[][] sum = new int[N][N];
		
		for(int i = 0; i < N; i++) {
			int point = matrix[i][0];
			for(int j = i + 1; j < N; j++) {
				sum[i][j] = sum[i][j - 1] + (point * matrix[j][0] * matrix[j][1]);
			}
		}
		
		int[][] dp = new int[N][N];
		
		for(int len = 2; len < N + 1; len++) {
			int i = 0, j = len - 1;
			while(j < N) {
				if(len == 2) {
					dp[i][j] = sum[i][j];
				} else {
					// Exam-01 의 알고리즘 차용하면 된다.
					// 이해하고 작성하자 .
					
					// 최소값 할당을 위함.
					dp[i][j] = Integer.MAX_VALUE;
					
					/* 범위값 설정부터 어떻게 해야 할 듯 i < j 에서 무언가 하나 +-1 될듯.
					for(int x = i; x < j; x++) {
						dp[i][j] = Math.min(dp[i][j], sum[i][j] + dp[i][x] + dp[x + 1][j]);
					}
					*/
					for(int k = i; k < j; k++) {
						int mat = matrix[i][0] * matrix[k][1] * matrix[j][1];
						dp[i][j] = Math.min(dp[i][j], dp[i][k] + dp[k + 1][j] + mat);
					}
				}
				
				
				i++;j++;
			}
		}
		
		System.out.println(dp[0][dp.length - 1]);
	}

}
