
import java.util.*;
import java.io.*;

/*
N-Queen 실패
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
10 초	128 MB	97212	46692	30312	46.763%
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
	public static int cnt = 0;
	public static int[] queenPlaced;
	public static int N;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		N = Integer.parseInt(br.readLine());
		queenPlaced = new int[N];
		
		getNumOfQueen(0);
		
		bw.write(Integer.toString(cnt));
		bw.flush();
		bw.close();
		br.close();
	}
	public static void getNumOfQueen(int deep) {
		if(N == deep) {
			cnt++;
			return;
		}else {
			for(int i = 0; i < N; i++) {
				queenPlaced[deep] = i;
				if(possibleToPlace(deep))
					getNumOfQueen(deep + 1);
				
			}
		}
	}
	public static boolean possibleToPlace(int col) {
		for(int i = 0; i < col; i++) {
			if(queenPlaced[i] == queenPlaced[col])
				return false;
			else if(Math.abs(queenPlaced[col] - queenPlaced[i]) == Math.abs(col - i))
				return false;
		}
		return true;
	}
}
