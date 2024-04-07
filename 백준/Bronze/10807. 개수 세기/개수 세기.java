import java.util.*;
import java.io.*;

/**
개수 세기

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	121637	74784	63736	62.463%

문제
총 N개의 정수가 주어졌을 때, 정수 v가 몇 개인지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 정수의 개수 N(1 ≤ N ≤ 100)이 주어진다. 
둘째 줄에는 정수가 공백으로 구분되어져있다. 
셋째 줄에는 찾으려고 하는 정수 v가 주어진다. 
입력으로 주어지는 정수와 v는 -100보다 크거나 같으며, 100보다 작거나 같다.

출력
첫째 줄에 입력으로 주어진 N개의 정수 중에 v가 몇 개인지 출력한다.

예제 입력 1 
11
1 4 1 2 4 2 4 2 3 4 4
2
예제 출력 1 
3
예제 입력 2 
11
1 4 1 2 4 2 4 2 3 4 4
5
예제 출력 2 
0
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine()); // 읽음 
		
		StringTokenizer st = new StringTokenizer(br.readLine()); // 읽고 토큰 분리기 
		
		int findNum = Integer.parseInt(br.readLine());
		
		int count = 0;
		
		for(int i = 0; i < N; i++) {
			count = (Integer.parseInt(st.nextToken()) == findNum) ? count + 1 : count;
		}
		
		System.out.println(count);
		
	}
	
	
}
