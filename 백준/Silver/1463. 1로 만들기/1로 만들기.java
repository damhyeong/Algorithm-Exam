import java.util.*;
import java.io.*;

/**
1로 만들기

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.15 초 (하단 참고)	128 MB	313432	107308	68411	33.020%

문제
---
정수 X에 사용할 수 있는 연산은 다음과 같이 세 가지 이다.

X가 3으로 나누어 떨어지면, 3으로 나눈다.
X가 2로 나누어 떨어지면, 2로 나눈다.
1을 뺀다.

정수 N이 주어졌을 때, 위와 같은 연산 세 개를 적절히 사용해서 1을 만들려고 한다. 

연산을 사용하는 횟수의 최솟값을 출력하시오.

입력
---
첫째 줄에 1보다 크거나 같고, 10^6보다 작거나 같은 정수 N이 주어진다.

출력
---
첫째 줄에 연산을 하는 횟수의 최솟값을 출력한다.

예제 입력 1 
2
예제 출력 1 
1

예제 입력 2 
10
예제 출력 2 
3

힌트
-----
10의 경우에 10 → 9 → 3 → 1 로 3번 만에 만들 수 있다.
 */

/**
	2 : 2 -> 1
	3 : 3 -> 1
	4 : 4 -> 2 -> 1 or 4 -> 3 -> 1
	5 : 5 -> 4 -> 2 -> 1 or 5 -> 4 -> 3 -> 1
	6 : 6 -> 2 -> 1 or 6 -> 3 -> 1
	7 : 7 -> 6 -> 3 -> 1 or 7 -> 6 -> 2 -> 1
	8 : 8 -> 4 -> 2 -> 1 or 8 -> 4 -> 3 -> 1
	9 : 9 -> 3 -> 1
	10 : 10 -> 9 -> 3 -> 1
	
	
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		
		
		
		int[] temp = new int[11];
		temp[2] = 1;
		temp[3] = 1;
		temp[4] = 2;
		temp[5] = 3;
		temp[6] = 2;
		temp[7] = 3;
		temp[8] = 3;
		temp[9] = 2;
		temp[10] = 3;
		
		if(N <= 10) {
			System.out.println(temp[N]);
		} else {
			int[] arr = new int[N + 1];
			
			for(int i = 0; i < temp.length; i++) {
				arr[i] = temp[i];
			}
			
			for(int i = 11; i <= N; i++) {
				// -1을 했을 때를 먼저 상정한다. 추후 중복 if문을 피하기 위함.
				int result = arr[i - 1];
				
				// 3으로 나눌 수 있는가?
				if(i % 3 == 0)
					result = result >= arr[i / 3] ? arr[i / 3] : result;
				
				// 2로 나눌 수 있는가?
				if(i % 2 == 0)
					result = result >= arr[i / 2] ? arr[i / 2] : result;
				
				arr[i] = result + 1;
			}
			
			System.out.println(arr[N]);
		}
	}

}
