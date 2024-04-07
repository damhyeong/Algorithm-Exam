
import java.util.*;
import java.io.*;

/**
합

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	280455	179116	151476	64.106%

문제
n이 주어졌을 때, 1부터 n까지 합을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 n (1 ≤ n ≤ 10,000)이 주어진다.

출력
1부터 n까지 합을 출력한다.

예제 입력 1 
3
예제 출력 1 
6
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int num = Integer.parseInt(br.readLine());
		int total = 0;
		
		for(int i = 1; i <= num; i++) {
			total += i;
		}
		System.out.println(total);
	}

}
