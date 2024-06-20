import java.util.*;
import java.io.*;

/**
곱셈

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.5 초 (추가 시간 없음)	128 MB	128629	36365	26434	27.223%

문제
---
자연수 A를 B번 곱한 수를 알고 싶다. 

단 구하려는 수가 매우 커질 수 있으므로, 이를 C로 나눈 나머지를 구하는 프로그램을 작성하시오.

입력
---
첫째 줄에 A, B, C가 빈 칸을 사이에 두고 순서대로 주어진다. 

A, B, C는 모두 2,147,483,647 이하의 자연수이다.

출력
---
첫째 줄에 A를 B번 곱한 수를 C로 나눈 나머지를 출력한다.

예제 입력 1 
10 11 12
예제 출력 1 
4
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		long A = Long.parseLong(st.nextToken()); 
		long B = Long.parseLong(st.nextToken());
		long C = Long.parseLong(st.nextToken());
		
		long result = getMulty(A, B, C);
		
		System.out.println(result);
	}
	
	public static long getMulty(long mulNum, long times, long divide) {
		if(times == 0) 
			return 1;
		else if(times == 1)
			return mulNum % divide;
		
		long midTimes = times / 2;

		if(times % 2 == 0) {
			long tempResult = getMulty(mulNum, midTimes, divide) % divide;
			return (tempResult * tempResult) % divide; 
		} else {
			long tempResult = getMulty(mulNum, midTimes, divide) % divide;
			return (tempResult * ((tempResult * mulNum) % divide)) % divide;
		}
	}
}
