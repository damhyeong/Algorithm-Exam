import java.util.*;
import java.io.*;

/**
N-Queen

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
10 초	128 MB	116867	56171	36372	46.565%

문제
N-Queen 문제는 크기가 N × N인 체스판 위에 퀸 N개를 서로 공격할 수 없게 놓는 문제이다.

N이 주어졌을 때, 퀸을 놓는 방법의 수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N이 주어진다. (1 ≤ N < 15)

출력
첫째 줄에 퀸 N개를 서로 공격할 수 없게 놓는 경우의 수를 출력한다.

예제 입력 1 
8
예제 출력 1 
92
 */

public class Main {
	public static int[] arr;
	public static int N;
	public static int count = 0;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		
		arr = new int[N];
		
		recursive(N, 0);
		
		System.out.println(count);
	}
	public static void recursive(int N, int deep) {
		if(deep == N) {
			count++;
			return;
		}
		
		for(int i = 0; i < N; i++) {
			arr[deep] = i;
			if(checkOkay(deep, i))
				recursive(N, deep + 1);
		}
	}
	
	public static boolean checkOkay(int deep, int num) {
		for(int i = 0; i < deep; i++) {
			if(arr[i] == arr[deep])
				return false;
			else if(Math.abs(arr[deep] - arr[i]) == Math.abs(deep - i))
				return false;
		}
		return true;
	}
}
