import java.util.*;
import java.io.*;

/**
다음 소수

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	31393	8280	6551	24.763%

문제
---
정수 n(0 ≤ n ≤ 4*109)가 주어졌을 때, 4 * 1_000_000_000
n보다 크거나 같은 소수 중 가장 작은 소수 찾는 프로그램을 작성하시오.

입력
---
첫째 줄에 테스트 케이스의 개수가 주어진다. 각 테스트 케이스는 한 줄로 이루어져 있고, 정수 n이 주어진다.

출력
---
각각의 테스트 케이스에 대해서 n보다 크거나 같은 소수 중 가장 작은 소수를 한 줄에 하나씩 출력한다.

예제 입력 1 
3
6
20
100
예제 출력 1 
7
23
101
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		
		StringBuilder sb = new StringBuilder();
		while(T-- > 0) {
			long input = Long.parseLong(br.readLine());
			long result = findPrimeNum(input);
			
			sb.append(result).append("\n");
		}
		System.out.println(sb.toString());
	}
	
	public static long findPrimeNum(long input) {
		if(input <= 2)
			return 2;
		
		long result = -1;
		while(true) {
			if(isPrimeNum(input)) {
				result = input;
				break;
			} else {
				input++;
			}
			
		}
		
		return result;
	}
	
	public static boolean isPrimeNum(long input) {
		boolean isPrime = true;
		
		for(long i = 2; i * i <= input; i++) {
			if(input % i == 0) {
				isPrime = false;
				break;
			}
		}
		return isPrime;
	}
}
