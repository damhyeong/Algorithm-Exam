import java.util.*;
import java.io.*;

/**
소수

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	148731	59026	49661	39.416%

문제
자연수 M과 N이 주어질 때 M이상 N이하의 자연수 중 소수인 것을 모두 골라 이들 소수의 합과 최솟값을 찾는 프로그램을 작성하시오.

예를 들어 M=60, N=100인 경우 60이상 100이하의 자연수 중 소수는 61, 67, 71, 73, 79, 83, 89, 97 총 8개가 있으므로, 
이들 소수의 합은 620이고, 최솟값은 61이 된다.

입력
입력의 첫째 줄에 M이, 둘째 줄에 N이 주어진다.

M과 N은 10,000이하의 자연수이며, M은 N보다 작거나 같다.

출력
M이상 N이하의 자연수 중 소수인 것을 모두 찾아 첫째 줄에 그 합을, 둘째 줄에 그 중 최솟값을 출력한다. 

단, M이상 N이하의 자연수 중 소수가 없을 경우는 첫째 줄에 -1을 출력한다.

예제 입력 1 
60
100
예제 출력 1 
620
61
예제 입력 2 
64
65
예제 출력 2 
-1
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int M = Integer.parseInt(br.readLine());
		int N = Integer.parseInt(br.readLine());
		
		long sum = 0;
		int min = Integer.MAX_VALUE;
		
		for(int i = M; i <= N; i++) {
			int num = i; // 소수인지 아닌지 판별할 수.
			
			// 예외 수 - 1, 2 
			if(num == 1) { // 1은 소수가 아니다. 
				continue;
			} else if(num == 2) { // 2는 소수이다. 
				sum += 2;
				min = (min >= num) ? num : min;
				continue;
			}
			
			// 본격적인 소수 판별 
			boolean isPrimeNum = true;
			for(int j = 2; j <= (num / 2) + 1; j++) {
				if(num % j == 0) { // num이 소수가 아니라면 
					isPrimeNum = false;
					break;
				}
			}
			
			// 소수가 맞다면 
			if(isPrimeNum) {
				min = (min >= num) ? num : min;
				sum += num;
			}
		}
		
		if(min == Integer.MAX_VALUE)
			System.out.println("-1");
		else {
			System.out.println(sum);
			System.out.println(min);
		}
	}

}
