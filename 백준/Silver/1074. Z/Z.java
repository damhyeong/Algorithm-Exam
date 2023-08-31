
import java.util.*;
import java.io.*;

/**
Z
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.5 초 (추가 시간 없음)	512 MB	69970	27760	20725	40.393%

예제 입력 1 
2 3 1
예제 출력 1 
11
예제 입력 2 
3 7 7
예제 출력 2 
63
예제 입력 3 
1 0 0
예제 출력 3 
0
예제 입력 4 
4 7 7
예제 출력 4 
63
예제 입력 5 
10 511 511
예제 출력 5 
262143
예제 입력 6 
10 512 512
예제 출력 6 
786432

문제
한수는 크기가 2^N × 2^N인 2차원 배열을 Z모양으로 탐색하려고 한다. 
예를 들어, 2×2배열을 왼쪽 위칸, 오른쪽 위칸, 왼쪽 아래칸, 오른쪽 아래칸 순서대로 방문하면 Z모양이다.

N > 1인 경우, 배열을 크기가 2^N-1 × 2^N-1로 4등분 한 후에 재귀적으로 순서대로 방문한다.

다음 예는 2^2 × 2^2 크기의 배열을 방문한 순서이다.

N이 주어졌을 때, r행 c열을 몇 번째로 방문하는지 출력하는 프로그램을 작성하시오.

다음은 N=3일 때의 예이다.

입력
첫째 줄에 정수 N, r, c가 주어진다.

출력
r행 c열을 몇 번째로 방문했는지 출력한다.

제한
1 ≤ N ≤ 15
0 ≤ r, c < 2^N
 */

public class Main {
	public static int r;
	public static int c;
	public static BufferedWriter bw;
	public static boolean isEnd = false;
	public static int count = 0;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken()); // 2^N
		r = Integer.parseInt(st.nextToken()); // 행 
		c = Integer.parseInt(st.nextToken()); // 열 
		
		int twoN = 1;
		for(int i = 0; i < N; i++)
			twoN *= 2;
		N = twoN;
		
		// map = new int[N][N];
		// int cnt = 0;
		
		recursive(0, 0, N);
		
		bw.flush();
		bw.close();
		br.close();
	}
	public static void recursive(int startX, int startY, int len) throws IOException {
		if(len == 1) {
			if(startX == c && startY == r) {
				bw.write(Integer.toString(count));
				isEnd = true;
			}
			count++;
			return;
		}
		if(isEnd) {
			return;
		}
		int newLen = len / 2;
		
        // 검색하는 행과 열이 그 자리에 없다면, 재귀를 통해 다시 자기 자신을 호출할 필요가 없다.
        // 왜냐면 그렇게 해도 정답은 나오지만, 메모리 초과로 통과를 절대로 못하기 때문이다...
		if((startX <= c && c < startX + newLen) 
				&& (startY <= r && r < startY + newLen))
			recursive(startX, startY, newLen);
		else 
			count += newLen * newLen;// 재귀를 통하여 count 해야 할 양을 여기서 바로 더하여 계산을 줄인다.
		if((startX + newLen <= c && c < startX + newLen + newLen) 
				&& (startY <= r && r < startY + newLen))
			recursive(startX + newLen, startY, newLen);
		else
			count += newLen * newLen;
		if((startX <= c && c < startX + newLen) 
				&& (startY + newLen <= r && r < startY + newLen + newLen))
			recursive(startX, startY + newLen, newLen);
		else
			count += newLen * newLen;
		if((startX + newLen <= c && c < startX + newLen + newLen) 
				&& (startY + newLen <= r && r < startY + newLen + newLen))
			recursive(startX + newLen, startY + newLen, newLen);
		else
			count += newLen * newLen;
	}
}
