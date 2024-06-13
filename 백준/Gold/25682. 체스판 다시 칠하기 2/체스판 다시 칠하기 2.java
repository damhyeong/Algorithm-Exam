import java.util.*;
import java.io.*;

/**
체스판 다시 칠하기 2

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	7979	3131	2341	38.327%

문제
---
지민이는 자신의 저택에서 MN개의 단위 정사각형으로 나누어져 있는 M×N 크기의 보드를 찾았다. 

어떤 정사각형은 검은색으로 칠해져 있고, 나머지는 흰색으로 칠해져 있다. 

지민이는 이 보드를 잘라서 K×K 크기의 체스판으로 만들려고 한다.


체스판은 검은색과 흰색이 번갈아서 칠해져 있어야 한다. 

구체적으로, 각 칸이 검은색과 흰색 중 하나로 색칠되어 있고, 변을 공유하는 두 개의 사각형은 다른 색으로 칠해져 있어야 한다. 

따라서 이 정의를 따르면 체스판을 색칠하는 경우는 두 가지뿐이다. 하나는 맨 왼쪽 위 칸이 흰색인 경우, 하나는 검은색인 경우이다.


보드가 체스판처럼 칠해져 있다는 보장이 없어서, 지민이는 K×K 크기의 체스판으로 잘라낸 후에 몇 개의 정사각형을 다시 칠해야겠다고 생각했다. 

당연히 K×K 크기는 아무데서나 골라도 된다. 

지민이가 다시 칠해야 하는 정사각형의 최소 개수를 구하는 프로그램을 작성하시오.

입력
---
첫째 줄에 정수 N, M, K가 주어진다. 

둘째 줄부터 N개의 줄에는 보드의 각 행의 상태가 주어진다. 

B는 검은색이며, W는 흰색이다.

출력
---
첫째 줄에 지민이가 잘라낸 K×K 보드를 체스판으로 만들기 위해 다시 칠해야 하는 정사각형 개수의 최솟값을 출력한다.

제한
---
1 ≤ N, M ≤ 2000
1 ≤ K ≤ min(N, M)


예제 입력 1 
4 4 3
BBBB
BBBB
BBBW
BBWB
예제 출력 1 
2

dp 연습 :

0 1 2 3
1 2 3 4
2 3 4 4
3 4 4 4

예제 입력 2 
8 8 8
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBBBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
예제 출력 2 
1

예제 입력 3 
10 13 10
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
WWWWWWWWWWBWB
WWWWWWWWWWBWB
예제 출력 3 
30

예제 입력 4 
9 23 9
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBWWWWWWWW
예제 출력 4 
40
 */


public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer numbers = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(numbers.nextToken());
		int M = Integer.parseInt(numbers.nextToken());
		int K = Integer.parseInt(numbers.nextToken());
		
		char[][] board = new char[N + 1][M + 1];
		
		for(int i = 1; i < N + 1; i++) {
			char[] chs = br.readLine().trim().toCharArray();
			for(int j = 1; j < M + 1; j++) {
				board[i][j] = chs[j - 1];
			}
		}
		
		int min = Integer.MAX_VALUE;
		
		for(int OE = 0; OE < 2; OE++) {
			// 시작이 'W' or 'B'이다. OE는 Odd or Even의 약자로 해놨다.
			int[][] cntCng = new int[N + 1][M + 1];
			
			for(int i = 1; i < N + 1; i++) {
				for(int j = 1; j < M + 1; j++) {
					// i 와 j의 위치, 그리고 'W' 시작인지 'B' 시작인지는 OE로 결정한다.
					char expChar = ((i + j + OE) % 2 == 0) ? 'W' : 'B';
					
					// 예상 문자가 주어진 보드와 같다면, 바꿀 필요가 없으므로 0, 아니라면 하나를 더 바꿔야 하므로 1을 추가한다.
					cntCng[i][j] = expChar == board[i][j] ? 0 : 1;
					
					// cntCng[i][j] 계산은 위에서 완료했으므로, 나머지 부분을 더하고, 겹친 부분을 제외한다. 
					cntCng[i][j] += cntCng[i - 1][j] + cntCng[i][j - 1] - cntCng[i - 1][j - 1];
				}
			}
			
			for(int i = K; i < N + 1; i++) {
				for(int j = K; j < M + 1; j++) {
					int tempCnt = cntCng[i][j] - (cntCng[i - K][j] + cntCng[i][j - K] - cntCng[i - K][j - K]);
					min = min > tempCnt ? tempCnt : min;
				}
			}
		}
		
		System.out.println(min);
	}
}
