
import java.util.*;
import java.io.*;

/**
이항 계수 1
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	54035	34995	30227	64.668%
문제
자연수 
N과 정수 
K가 주어졌을 때 이항 계수 
{N}를 구하는 프로그램을 작성하시오.
{k}

입력
첫째 줄에 
N과 
K가 주어진다. (1 ≤ N ≤ 10, 0 ≤ K ≤ N)

출력
 
{N}
{k}를 출력한다.

예제 입력 1 
5 2
예제 출력 1 
10
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken()); int K = Integer.parseInt(st.nextToken());
		int result = factorial(N) / (factorial(N - K) * factorial(K));
		bw.write(Integer.toString(result));
		bw.flush();
		bw.close();
		br.close();
	}

	public static int factorial(int num) {
		int result = 1;
		for(int i = num; i > 0; i--) {
			result *= i;
		}
		return result;
	}
}
