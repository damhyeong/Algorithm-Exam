
import java.util.*;
import java.io.*;

/**
문제
M이상 N이하의 소수를 모두 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 자연수 M과 N이 빈 칸을 사이에 두고 주어진다. (1 ≤ M ≤ N ≤ 1,000,000) M이상 N이하의 소수가 하나 이상 있는 입력만 주어진다.

출력
한 줄에 하나씩, 증가하는 순서대로 소수를 출력한다.

예제 입력 1 
3 16
예제 출력 1 
3
5
7
11
13
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int M = Integer.parseInt(st.nextToken());
		int N = Integer.parseInt(st.nextToken());
		
		for(int i = M; i <= N; i++) {
			if(i == 1)
				continue;
			
			if(i <= 2) {
				bw.write(Integer.toString(2) + "\n");
				continue;
			}
			
			if(isPrime(i))
				bw.write(Integer.toString(i) + "\n");
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
