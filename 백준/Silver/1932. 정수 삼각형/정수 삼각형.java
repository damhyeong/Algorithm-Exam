
import java.util.*;
import java.io.*;

/**
정수 삼각형 다국어
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	82938	47871	36121	59.303%
문제
        7
      3   8
    8   1   0
  2   7   4   4
4   5   2   6   5
위 그림은 크기가 5인 정수 삼각형의 한 모습이다.

맨 위층 7부터 시작해서 아래에 있는 수 중 하나를 선택하여 아래층으로 내려올 때, 
이제까지 선택된 수의 합이 최대가 되는 경로를 구하는 프로그램을 작성하라. 
아래층에 있는 수는 현재 층에서 선택된 수의 대각선 왼쪽 또는 대각선 오른쪽에 있는 것 중에서만 선택할 수 있다.

삼각형의 크기는 1 이상 500 이하이다. 
삼각형을 이루고 있는 각 수는 모두 정수이며, 범위는 0 이상 9999 이하이다.

입력
첫째 줄에 삼각형의 크기 n(1 ≤ n ≤ 500)이 주어지고, 둘째 줄부터 n+1번째 줄까지 정수 삼각형이 주어진다.

출력
첫째 줄에 합이 최대가 되는 경로에 있는 수의 합을 출력한다.

예제 입력 1 
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
예제 출력 1 
30
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int n = Integer.parseInt(br.readLine());
		
		int[][] mapping = new int[n][n];
		int[][] sumMap = new int[n][n];
		
		StringTokenizer st;
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			
			int jIndex = 0;
			while(st.hasMoreTokens()) 
				mapping[i][jIndex++] = Integer.parseInt(st.nextToken());
			
		}
		
		sumMap[0][0] = mapping[0][0];
		for(int i = 1; i < n; i++) {
			for(int j = 0; j < n; j++) {
				// 세가지로 분류 - (j인덱스가 0일 경우, 보통, 윗줄의 j인덱스가 0일 경우.)
				
				// 왼쪽 끝일경우, 연결된 요소가 하나이다. 
				if(j == 0) {
					sumMap[i][j] = sumMap[i - 1][j] + mapping[i][j];
					continue;
				}
				
				// 오른쪽 끝 요소일 경우, 위와 같이 하나만 연결된다.
				if(sumMap[i - 1][j] == 0) {
					sumMap[i][j] = sumMap[i - 1][j - 1] + mapping[i][j];
					break;
				}
				
				// 양 끝에 위치한 요소가 아닐 경우, 두 가지 경로 중 최대값을 얻을 수 있는 경로를 선택한다. 
				int num1 = sumMap[i - 1][j - 1] + mapping[i][j];
				int num2 = sumMap[i - 1][j] + mapping[i][j];
				
				int maxNum = (num1 >= num2) ? num1 : num2;
				sumMap[i][j] = maxNum;
			}
		}
		
		int max = -1;
		for(int i = 0; i < n; i++) {
			if(max <= sumMap[n - 1][i])
				max = sumMap[n - 1][i];
		}
		bw.write(Integer.toString(max));
		bw.flush();
		bw.close();
		br.close();
	}
	
}
