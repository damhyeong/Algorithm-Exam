import java.util.*;
import java.io.*;

/**
행렬 곱셈

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	19453	13156	11436	68.747%

문제
---
N*M크기의 행렬 A와 M*K크기의 행렬 B가 주어졌을 때, 두 행렬을 곱하는 프로그램을 작성하시오.


입력
---
첫째 줄에 행렬 A의 크기 N 과 M이 주어진다.

둘째 줄부터 N개의 줄에 행렬 A의 원소 M개가 순서대로 주어진다. 

그 다음 줄에는 행렬 B의 크기 M과 K가 주어진다. 

이어서 M개의 줄에 행렬 B의 원소 K개가 차례대로 주어진다. 

N과 M, 그리고 K는 100보다 작거나 같고, 행렬의 원소는 절댓값이 100보다 작거나 같은 정수이다.


출력
---
첫째 줄부터 N개의 줄에 행렬 A와 B를 곱한 행렬을 출력한다. 

행렬의 각 원소는 공백으로 구분한다.


예제 입력 1 
3 2
1 2
3 4
5 6
2 3
-1 -2 0
0 0 3
예제 출력 1 
-1 -2 6
-3 -6 12
-5 -10 18
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		// 행렬의 크기 N, M 을 준다.
		int N = Integer.parseInt(st.nextToken()); int M = Integer.parseInt(st.nextToken());
		
		int[][] procession1 = new int[N][M];
		
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < M; j++) {
				procession1[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		st = new StringTokenizer(br.readLine());
		// 자세한 내용은 : https://ko.khanacademy.org/ 사이트의 "행렬의 곱셈이란?" 참조 - Khan Academy 사이트 
		st.nextToken(); // 행렬의 곱셈이 이루어지려면 어짜피 행렬1의 열 과 행렬2의 행 이 같아야 한다. (행렬1 열 개수 == 행렬2 행 개수)
		int K = Integer.parseInt(st.nextToken());
		
		
		int[][] procession2 = new int[M][K];
		
		for(int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < K; j++) {
				procession2[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		long[][] result = new long[N][K];
		
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < K; j++) {
				result[i][j] = getCellResult(procession1, i, procession2, j);
			}
		}
		
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < result.length; i++) {
			for(int j = 0; j < result[0].length; j++) {
				sb.append(result[i][j]).append(" ");
			}
			sb.append("\n");
		}
		
		System.out.println(sb.toString());
	}
	
	public static long getCellResult(int[][] procession1, int row, int[][] procession2, int column) {
		long result = 0;
		
		// 두 배열의 길이는 같음 - 행렬 곱셈의 법칙 
		int[] arr1 = procession1[row];
		
		int[] arr2 = new int[procession2.length]; // new int[arr1.length] 해도 상관은 없음. 
		for(int i = 0; i < arr2.length; i++)
			arr2[i] = procession2[i][column];
		
		// 계산 시작하기 
		for(int i = 0; i < arr1.length; i++) {
			result += arr1[i] * arr2[i];
		}
		
		return result;
	}
}
