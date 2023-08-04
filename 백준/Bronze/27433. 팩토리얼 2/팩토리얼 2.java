
import java.util.*;
import java.io.*;

/**
팩토리얼 2
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	1024 MB	11386	5465	5001	49.940%

문제
0보다 크거나 같은 정수 N이 주어진다. 이때, N!을 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 정수 N(0 ≤ N ≤ 20)이 주어진다.

출력
첫째 줄에 N!을 출력한다.

예제 입력 1 
10
예제 출력 1 
3628800
예제 입력 2 
0
예제 출력 2 
1
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		long N = Long.parseLong(br.readLine());
		
		long result = factorial(N);
		bw.write(Long.toString(result));
		bw.flush();
		bw.close();
		br.close();
	}
	
	public static long factorial(long num) {
		if(num <= 1)
			return 1;
		else
			return num * factorial(num - 1);
	}
}
