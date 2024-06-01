import java.util.*;
import java.io.*;

/**
RGB거리

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.5 초 (추가 시간 없음)	128 MB	116772	65943	48981	55.559%

문제
---
RGB거리에는 집이 N개 있다. 

거리는 선분으로 나타낼 수 있고, 1번 집부터 N번 집이 순서대로 있다.

집은 빨강, 초록, 파랑 중 하나의 색으로 칠해야 한다. 

각각의 집을 빨강, 초록, 파랑으로 칠하는 비용이 주어졌을 때, 아래 규칙을 만족하면서 모든 집을 칠하는 비용의 최솟값을 구해보자.

1번 집의 색은 2번 집의 색과 같지 않아야 한다.

N번 집의 색은 N-1번 집의 색과 같지 않아야 한다.

i(2 ≤ i ≤ N-1)번 집의 색은 i-1번, i+1번 집의 색과 같지 않아야 한다.


입력
---
첫째 줄에 집의 수 N(2 ≤ N ≤ 1,000)이 주어진다. 

둘째 줄부터 N개의 줄에는 각 집을 빨강, 초록, 파랑으로 칠하는 비용이 1번 집부터 한 줄에 하나씩 주어진다. 

집을 칠하는 비용은 1,000보다 작거나 같은 자연수이다.

출력
---
첫째 줄에 모든 집을 칠하는 비용의 최솟값을 출력한다.

예제 입력 1 
3
26 40 83
49 60 57
13 89 99
예제 출력 1 
96
예제 입력 2 
3
1 100 100
100 1 100
100 100 1
예제 출력 2 
3
예제 입력 3 
3
1 100 100
100 100 100
1 100 100
예제 출력 3 
102
예제 입력 4 
6
30 19 5
64 77 64
15 19 97
4 71 57
90 86 84
93 32 91
예제 출력 4 
208
예제 입력 5 
8
71 39 44
32 83 55
51 37 63
89 29 100
83 58 11
65 13 15
47 25 29
60 66 19
예제 출력 5 
253
 */

public class Main {
	public static int[][] houses;
	public static int[][] costs;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		houses = new int[N][3];
		costs = new int[N][3];
		
		for(int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for(int j = 0; j < 3; j++)
				houses[i][j] = Integer.parseInt(st.nextToken());
		}
		
		costs[0][0] = houses[0][0];
		costs[0][1] = houses[0][1];
		costs[0][2] = houses[0][2];
		
		for(int i = 1; i < N; i++) {
			for(int j = 0; j < 3; j++) {
				costs[i][j] = getMinCosts(i, j);
			}
		}
		
		int result = Math.min(costs[N - 1][0], Math.min(costs[N - 1][1], costs[N - 1][2]));
		
		System.out.println(result);
	}
	
	public static int getMinCosts(int i, int j) {
		if(j == 0) 
			return (costs[i - 1][1] <= costs[i - 1][2]) ? costs[i - 1][1] + houses[i][j] : costs[i - 1][2] + houses[i][j];
		else if(j == 1) 
			return (costs[i - 1][0] <= costs[i - 1][2]) ? costs[i - 1][0] + houses[i][j] : costs[i - 1][2] + houses[i][j];
		else 
			return (costs[i - 1][0] <= costs[i - 1][1]) ? costs[i - 1][0] + houses[i][j] : costs[i - 1][1] + houses[i][j];
		
	}
}
