
import java.util.*;
import java.io.*;

/**
피보나치 수 2 다국어
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	92728	38066	31253	40.671%
문제
피보나치 수는 0과 1로 시작한다. 0번째 피보나치 수는 0이고, 1번째 피보나치 수는 1이다. 그 다음 2번째 부터는 바로 앞 두 피보나치 수의 합이 된다.

이를 식으로 써보면 Fn = Fn-1 + Fn-2 (n ≥ 2)가 된다.

n=17일때 까지 피보나치 수를 써보면 다음과 같다.

0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597

n이 주어졌을 때, n번째 피보나치 수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 n이 주어진다. n은 90보다 작거나 같은 자연수이다.

출력
첫째 줄에 n번째 피보나치 수를 출력한다.

예제 입력 1 
10
예제 출력 1 
55
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int n = Integer.parseInt(br.readLine());
		
		long[] fibonachi = new long[91];
		
		fibonachi[0] = 0; fibonachi[1] = 1; fibonachi[2] = 1;
		for(int i = 3; i <= 90; i++)
			fibonachi[i] = fibonachi[i - 1] + fibonachi[i - 2];
		
		bw.write(Long.toString(fibonachi[n]));
		bw.flush();
		bw.close();
		br.close();
	}

}
