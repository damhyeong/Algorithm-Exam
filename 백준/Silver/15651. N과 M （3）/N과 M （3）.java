
import java.util.*;
import java.io.*;

/**
N과 M (3)
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	512 MB	58068	38713	29123	66.863%

예제 입력 1 
3 1
예제 출력 1 
1
2
3
예제 입력 2 
4 2
예제 출력 2 
1 1
1 2
1 3
1 4
2 1
2 2
2 3
2 4
3 1
3 2
3 3
3 4
4 1
4 2
4 3
4 4
예제 입력 3 
3 3
예제 출력 3 
1 1 1
1 1 2
1 1 3
1 2 1
1 2 2
1 2 3
1 3 1
1 3 2
1 3 3
2 1 1
2 1 2
2 1 3
2 2 1
2 2 2
2 2 3
2 3 1
2 3 2
2 3 3
3 1 1
3 1 2
3 1 3
3 2 1
3 2 2
3 2 3
3 3 1
3 3 2
3 3 3

문제
자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성하시오.

1부터 N까지 자연수 중에서 M개를 고른 수열
같은 수를 여러 번 골라도 된다.
입력
첫째 줄에 자연수 N과 M이 주어진다. (1 ≤ M ≤ N ≤ 7)

출력
한 줄에 하나씩 문제의 조건을 만족하는 수열을 출력한다. 중복되는 수열을 여러 번 출력하면 안되며, 각 수열은 공백으로 구분해서 출력해야 한다.

수열은 사전 순으로 증가하는 순서로 출력해야 한다.

 */

public class Main {
	public static char[] chStr;
	public static BufferedWriter bw;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken()); int M = Integer.parseInt(st.nextToken());
		chStr = new char[M];
		
		recursiveMethodGood(N, M, 1);
		bw.flush();
		bw.close();
	}
	public static void recursiveMethodGood(int N, int M, int m) throws IOException {
		if(m > M) {
			String str = "";
			for(int i = 0; i < M; i++) {
				str += new String(chStr[i] + " ");
			}
			bw.write(str + "\n");
			return;
		}
		
		for(int i = 1; i <= N; i++) {
			chStr[m - 1] = Integer.toString(i).charAt(0);
			recursiveMethodGood(N, M, m + 1);
		}
	}
}
