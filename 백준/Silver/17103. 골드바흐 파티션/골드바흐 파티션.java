import java.util.*;
import java.io.*;

/**
골드바흐 파티션

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.5 초	512 MB	29083	10782	8268	35.043%

문제
---
골드바흐의 추측: 2보다 큰 짝수는 두 소수의 합으로 나타낼 수 있다.

짝수 N을 두 소수의 합으로 나타내는 표현을 골드바흐 파티션이라고 한다. 

짝수 N이 주어졌을 때, 골드바흐 파티션의 개수를 구해보자. 

두 소수의 순서만 다른 것은 같은 파티션이다.

입력
---
첫째 줄에 테스트 케이스의 개수 T (1 ≤ T ≤ 100)가 주어진다. 

각 테스트 케이스는 한 줄로 이루어져 있고, 정수 N은 짝수이고, 2 < N ≤ 1,000,000을 만족한다.

출력
---
각각의 테스트 케이스마다 골드바흐 파티션의 수를 출력한다.

예제 입력 1 
5
6
8
10
12
100
예제 출력 1 
1
1
2
1
6
 */

public class Main {
	public static boolean[] isPrime;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		isPrime = new boolean[10000001];
		
		for(int i = 2; i < isPrime.length; i++) {
			if(isPrime[i])
				continue;
			for(int j = i + i; j < 1000001; j += i)
				isPrime[j] = true;
		}
		
		int T = Integer.parseInt(br.readLine());
		
		StringBuilder sb = new StringBuilder();
		while(T-- > 0) {
			// input은 무조건 짝수로 결정되어있음.
			int input = Integer.parseInt(br.readLine());
			
			int count = getCount(input);
			
			sb.append(count).append("\n");
		}
		
		System.out.println(sb.toString());
	}
	
	public static int getCount(int input) {
		int count = 0;
		
		for(int i = 2; i <= input / 2; i++) {
			if(isPrime[i] || isPrime[input - i])
				continue;
			
			count++;
		}
		
		return count;
	}
	
	public static boolean isPrime(int number) {
		if(number == 2)
			return true;
		
		boolean isPrime = true;
		for(int i = 2; i * i <= number; i++) {
			if(number % i == 0) {
				isPrime = false;
				break;
			}
		}
		return isPrime;
	}
}
