
import java.util.*;
import java.io.*;

/**
약수
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	512 MB	59235	32867	28554	55.743%

예제 입력 1 
2
4 2
예제 출력 1 
8
예제 입력 2 
1
2
예제 출력 2 
4
예제 입력 3 
6
3 4 2 12 6 8
예제 출력 3 
24
예제 입력 4 
14
14 26456 2 28 13228 3307 7 23149 8 6614 46298 56 4 92596
예제 출력 4 
185192

문제
양수 A가 N의 진짜 약수가 되려면, N이 A의 배수이고, A가 1과 N이 아니어야 한다. 
어떤 수 N의 진짜 약수가 모두 주어질 때, N을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N의 진짜 약수의 개수가 주어진다. 이 개수는 50보다 작거나 같은 자연수이다. 
둘째 줄에는 N의 진짜 약수가 주어진다. 1,000,000보다 작거나 같고, 2보다 크거나 같은 자연수이고, 중복되지 않는다.

출력
첫째 줄에 N을 출력한다. N은 항상 32비트 부호있는 정수로 표현할 수 있다.

 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		// 사실 필요 없는 줄 
		int T = Integer.parseInt(br.readLine());
		
		long min = 1000001;
		long max = 1;
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		while(st.hasMoreTokens()) {
			long newNum = Long.parseLong(st.nextToken());
			min = (min >= newNum) ? newNum : min;
			max = (max <= newNum) ? newNum : max;
		}
		
		bw.write(Long.toString(min * max));
		bw.flush();
		bw.close();
		br.close();
	}

}
