import java.util.*;
import java.io.*;

/**
이항 계수 3

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	30070	11011	8127	39.891%

문제
---
자연수 N 과 정수 K 가 주어졌을 때, 이항 계수 ( N ) 를 1,000,000,007 로 나눈 나머지를 구하는 프로그램을 작성하시오.
                                    ( K )

입력
---
첫째 줄에 N 과 K 가 주어진다. ( 1 <= N <= 4,000,000   &&   0 <= K <= N )

출력
---
( N ) 를 1,000,000,007 로 나눈 나머지를 출력한다.
( K )
 
	이항계수 계산법 ==> N! / K! * (N - K)!

예제 입력 1 
5 2
예제 출력 1 
10
 */

/*
 * 해당 문제를 풀기 위한 선제 지식이 필요하다.
 * 1. 나머지에 대한 기초적 지식 - 깊이 들어갈 필요 없음
 * 2. 모듈로 연산에 대한 이해 - 모듈로 연산자, 모듈로 덧셈과 뺄셈, 모듈로 곱셈, 모듈로 거듭제곱법, 빠른 모듈로 거듭제곱법, **모듈로 역수**
 * 
 * 모듈로 연산은 덧셈, 뺄셈, 곱셈, 거듭제곱의 연산이 가능하지만, (나누기) 연산에서는 적용되지 않는다.
 * 따라서, 모듈로 역수라는 개념을 정확히 알고 있어야 계산이 가능하다.
 * 이 문제에서는 나머지 연산을 소수로 주기에 항상 서로소이지만, 수가 10억이 조금 넘기에, 
 * 모듈로 역수를 통해 "1" 이 나오는 수를 찾아야 한다.
 * 모듈로 역수 연산을 통해 "1"이 나오는 계산은 iter과 같은 연산으로는 찾기 버거울 수 있기에, 유클리드 호제법을 통한 빠른 연산이 필요하다.
 * 
 * 여태껏 재귀를 통해 풀었건만, 분할 정복이라는 의미는 정확히 "큰 문제를 작은 문제로 분할하여 푼다" 라는 것을 깨닫게 되었다.
 * 왜 골드 1인지 이해가 간다. - 컴퓨터 공학에 필요한 기초수학을 인지하고 있어야 풀수 있기 때문.
 */

public class Main {
	
	public static final long DIVIDE = 1_000_000_007;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		long N = Long.parseLong(st.nextToken()); 
		long K = Long.parseLong(st.nextToken());
		
		long[] arr = new long[(int)N + 1];
		arr[0] = 1;
		
		for(int i = 1; i <= N; i++) 
			arr[i] = (arr[i - 1] * (long)i) % DIVIDE;
		
		long result1 = arr[(int)N];
		
		long tempResult2 = (arr[(int)K] * arr[(int)(N - K)]) % DIVIDE;
		long result2 = (result1 * getModInverse(tempResult2, DIVIDE)) % DIVIDE;
		
		System.out.println(result2);
	}
	
	/**
	 * 페르마의 소정리를 이용하여 모듈러의 역원을 구하는 과정.
	 * 모듈러 계산에서는 기본적으로 나누기 연산자가 존재하지 않는다.
	 * 따라서, 모듈러 계산에서 나누기와 같은 의미를 가진 모듈러 역원을 이용하게 된다.
	 * (x * x^-1 = 1)(mod p) == 모듈러 역원
	 * (x^p-1 = 1)(mod p) == 페르마의 소정리 - 조건: p는 소수이며, x 와 p는 서로소이다. 
	 * 
	 * 모듈러의 역원은 방정식 같은 개념은 아니지만, 페르마의 소정리는 증명으로 이해하지 말고, 방정식으로 기억해야 한다.
	 * 
	 * 그렇다면, 모듈러 역원의 의미와 페르마의 소정리는 어떻게 결합될 수 있을까?
	 * 먼저 페르마의 소정리에서 시작해야 한다.
	 * 
	 * x^p-1 = 1 이다. 물론 (mod p) 에서.
	 * 그런데, 이 식은 (x * x^p - 2 = 1 (mod p)) 로 변형된다.
	 * 
	 * x^p-1에서 x를 하나 빼서 x * x^p-2 로 만드니까, 모듈러의 역원인 (x * x^-1 = 1) 이 완성되었다.
	 * 
	 * 따라서, 모듈러의 역원인 x^p-2 의 (mod p) 값을 구하는 과정인 셈이다.
	 * 
	 * 하지만, 주어진 p의 값은 10억 7이다.
	 * 이를 일일히 곱하는 것은 매우 큰 시간이 걸릴 것이다.
	 * 
	 * 따라서, 지수의 값이 된 p-2(10억 5) 를 계속해서 절반으로 나누어 x^-1 값인 x^p-2 값을 구하는 것이다.
	 * 
	 * @param 기반 수 
	 * @param 지수 
	 * @return 모듈러의 역원 값 
	 */
	public static long getModInverse(long num1, long num2) {
		long res = 1;
		long x = num1;
		long y = num2 - 2;
		long p = num2;
		
		// 지수가 남아있다면 계속 진행.
		while(y > 0) {
			if(y % 2 == 1)
				res = (res * x) % p;
			y /= 2;
			x = (x * x) % p;
		}
		return res;
	}
}
