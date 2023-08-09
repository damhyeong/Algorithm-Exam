
import java.util.*;
import java.io.*;

/**
N과 M (2)
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	512 MB	64513	48166	34551	74.060%

예제 입력 1 
3 1
예제 출력 1 
1
2
3
예제 입력 2 
4 2
예제 출력 2 
1 2
1 3
1 4
2 3
2 4
3 4
예제 입력 3 
4 4
예제 출력 3 
1 2 3 4

문제
자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성하시오.

1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
고른 수열은 오름차순이어야 한다.
입력
첫째 줄에 자연수 N과 M이 주어진다. (1 ≤ M ≤ N ≤ 8)

출력
한 줄에 하나씩 문제의 조건을 만족하는 수열을 출력한다. 중복되는 수열을 여러 번 출력하면 안되며, 각 수열은 공백으로 구분해서 출력해야 한다.

수열은 사전 순으로 증가하는 순서로 출력해야 한다.
 */

public class Main {
	public static int N;
	public static int M;
	public static char[] chStr;
	public static Set<Integer> numMap;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken()); M = Integer.parseInt(st.nextToken());
		chStr = new char[M];
		numMap = new HashSet<Integer>();
		
		getNumbers(0, 0, bw);
		bw.flush();
		bw.close();
		br.close();
	}
	
	public static void getNumbers(int n, int m, BufferedWriter bw) throws IOException {
		if(m == (M - 1)) {
			if(n == 0)
				n = 1;
			// n으로부터, 아직 가지 않은 N까지 조사한다.
			for(int i = n; i <= N; i++) {
				
				boolean isTrue = true;
				chStr[m] = Integer.toString(i).charAt(0);
				
				// chStr[] 배열이 완성되었을 때, 수열의 조건을 만족하는지 조사한다.
				for(int j = 0; j < M - 1; j++) {
					if(!(Character.getNumericValue(chStr[j]) < Character.getNumericValue(chStr[j + 1]))) {
						isTrue = false;
						break;
					}
				}
				// 수열의 조건을 만족한다면, 숫자 배열을 BufferedWriter에게 전달한다. 
				if(isTrue) {
					for(int j = 0; j < M; j++) {
						bw.write(Character.toString(chStr[j]) + " ");
					}
					bw.newLine();
				}
				
			}
			return;
			
		}else {
			for(int i = n; i < N; i++) {
				chStr[m] = Integer.toString(i + 1).charAt(0); // 수열의 길이가 8 이하라 가능한 문법 
				getNumbers(n + 1, m + 1, bw);
			}
		}
	}
}
