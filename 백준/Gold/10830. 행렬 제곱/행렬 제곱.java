import java.util.*;
import java.io.*;

/**
행렬 제곱

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	39616	14232	11354	34.634%

문제
---
크기가 N*N인 행렬 A가 주어진다. 

이때, A의 B제곱을 구하는 프로그램을 작성하시오. 

수가 매우 커질 수 있으니, A^B의 각 원소를 1,000으로 나눈 나머지를 출력한다.


입력
---
첫째 줄에 행렬의 크기 N과 B가 주어진다. 

(2 ≤ N ≤  5, 1 ≤ B ≤ 100,000,000,000)

둘째 줄부터 N개의 줄에 행렬의 각 원소가 주어진다. 

행렬의 각 원소는 1,000보다 작거나 같은 자연수 또는 0이다.


출력
---
첫째 줄부터 N개의 줄에 걸쳐 행렬 A를 B제곱한 결과를 출력한다.


예제 입력 1 
2 5
1 2
3 4
예제 출력 1 
69 558
337 406
예제 입력 2 
3 3
1 2 3
4 5 6
7 8 9
예제 출력 2 
468 576 684
62 305 548
656 34 412
예제 입력 3 
5 10
1 0 0 0 1
1 0 0 0 1
1 0 0 0 1
1 0 0 0 1
1 0 0 0 1
예제 출력 3 
512 0 0 0 512
512 0 0 0 512
512 0 0 0 512
512 0 0 0 512
512 0 0 0 512
 */

public class Main {
	public static long[][] orgProcession;
	public static final long DIVIDE = 1_000;
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken()); long B = Long.parseLong(st.nextToken());
		
		orgProcession = new long[N][N];
		long[][] calProcession = new long[N][N];
		
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < N; j++) {
				long tempNum = Long.parseLong(st.nextToken());
				orgProcession[i][j] = tempNum;
				calProcession[i][j] = tempNum;
			}
		}
		
		calProcession = calculate(calProcession, B);
		
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < calProcession.length; i++) {
			for(int j = 0; j < calProcession[0].length; j++) {
				sb.append(calProcession[i][j]).append(" ");
			}
			sb.append("\n");
		}
		
		System.out.println(sb.toString());
	}
	
	// num은 몇 번 제곱되는지 말한다. 
	public static long[][] calculate(long[][] procession, long power) {
		// 기본 행렬 
		long[][] baseProcession = procession;
		// 단위 행렬 생성 - 행렬을 곱하였을 때, 본인의 행렬이 그대로 나올 수 있는 행렬 - 대각선으로 1을 채움. \ 모양으로.
		long[][] result = getIdentityProcession(procession.length);
		
		while(power > 0) {
			// 중간에 홀수가 나오거나, 나오지 않을 수도 있지만, 결국 지수인 power은 1을 거쳐야 한다.
			if(power % 2 == 1) {
				result = multipleBetweenProcession(result, baseProcession);
			}
			// baseProcession은 짝수 일 때, 지수를 반으로 나누며 **result** 에 곱해주기 위해 계속 자신을 곱한다. 
			baseProcession = multipleBetweenProcession(baseProcession, baseProcession);
			power /= 2;
		}
		
		return result;
	}
	
	public static long[][] multipleBetweenProcession(long[][] procession1, long[][] procession2) {
		
		long[][] newProcession = new long[procession1.length][procession2[0].length];
		
		int len1 = procession1.length;
		int len2 = procession2[0].length;
		
		for(int i = 0; i < len1; i++) {
			for(int j = 0; j < len2; j++) {
				newProcession[i][j] = getCellResult(procession1, i, procession2, j);
			}
		}
		
		return newProcession;
	}
	
	private static long getCellResult(long[][] procession1, int row, long[][] procession2, int column) {
		long result = 0;
		
		long[] arr1 = procession1[row];
		long[] arr2 = new long[procession2.length];
		for(int i = 0; i < arr2.length; i++)
			arr2[i] = procession2[i][column];
		
		for(int i = 0; i < arr1.length; i++)
			result = (result + (arr1[i] * arr2[i])) % DIVIDE;
		
		return result;
	}
	
	private static long[][] getIdentityProcession(int size){
		long[][] returnProcession = new long[size][size];
		for(int i = 0; i < size; i++)
			returnProcession[i][i] = 1;
		
		return returnProcession;
			
	}
}
