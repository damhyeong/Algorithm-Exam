
import java.util.*;
import java.io.*;

/**
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

문제
골드바흐의 추측: 2보다 큰 짝수는 두 소수의 합으로 나타낼 수 있다.
짝수 N을 두 소수의 합으로 나타내는 표현을 골드바흐 파티션이라고 한다. 
짝수 N이 주어졌을 때, 골드바흐 파티션의 개수를 구해보자. 
두 소수의 순서만 다른 것은 같은 파티션이다.

입력
첫째 줄에 테스트 케이스의 개수 T (1 ≤ T ≤ 100)가 주어진다. 
각 테스트 케이스는 한 줄로 이루어져 있고, 정수 N은 짝수이고, 2 < N ≤ 1,000,000을 만족한다.

출력
각각의 테스트 케이스마다 골드바흐 파티션의 수를 출력한다.

 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int T = Integer.parseInt(br.readLine());
		
		boolean[] checkPrime = new boolean[1000000];
		
		for(int i = 2; i < checkPrime.length; i++) {
			if(isPrime(i) == true)
				checkPrime[i] = true;
			else
				checkPrime[i] = false;
		}
		
		while(T --> 0) {
			int N = Integer.parseInt(br.readLine());
			
			int cnt = 0;
			for(int i = 2; i  <= (N / 2); i++) {
				if(checkPrime[i]) {
					if(checkPrime[N - i])
						cnt++;
				}
			}
			bw.write(Integer.toString(cnt) + "\n");
		}
		bw.flush();
		bw.close();
		br.close();
	}
	public static boolean isPrime(int num) {
		for(int i = 2; i * i <= num; i++) {
			if(num % i == 0)
				return false;
		}
		return true;
	}
}
