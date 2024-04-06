import java.util.*;
import java.io.*;

/**
알람 시계

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	473412	178836	147699	37.761%


문제

바로 "45분 일찍 알람 설정하기"이다.

이 방법은 단순하다. 원래 설정되어 있는 알람을 45분 앞서는 시간으로 바꾸는 것이다.

현재 상근이가 설정한 알람 시각이 주어졌을 때, 창영이의 방법을 사용한다면, 이를 언제로 고쳐야 하는지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 두 정수 H와 M이 주어진다. 
(0 ≤ H ≤ 23, 0 ≤ M ≤ 59) 
그리고 이것은 현재 상근이가 설정한 알람 시간 H시 M분을 의미한다.

입력 시간은 24시간 표현을 사용한다. 
24시간 표현에서 
하루의 시작은 0:0(자정)이고, 
끝은 23:59(다음날 자정 1분 전)이다. 
시간을 나타낼 때, 불필요한 0은 사용하지 않는다.

출력
첫째 줄에 상근이가 창영이의 방법을 사용할 때, 설정해야 하는 알람 시간을 출력한다. (입력과 같은 형태로 출력하면 된다.)

예제 입력 1 
10 10
예제 출력 1 
9 25
예제 입력 2 
0 30
예제 출력 2 
23 45
예제 입력 3 
23 40
예제 출력 3 
22 55
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int hour = Integer.parseInt(st.nextToken());
		int min = Integer.parseInt(st.nextToken());
		
		// 현재 시각의 분이 45보다 작다면 hour -1 한다.
		if(min - 45 < 0) {
			min = 60 + (min - 45);
			
			if(hour == 0) {
				hour = 23;
			} else {
				hour -= 1;
			}
		} else {
			min -= 45;
		}
		
		StringBuilder sb = new StringBuilder();
		sb.append(hour); sb.append(" "); sb.append(min);
		
		System.out.println(sb.toString());
	}

}
