import java.util.*;
import java.io.*;

/**
오븐 시계

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	280344	107512	91121	38.205%


문제

훈제오리구이를 시작하는 시각과 오븐구이를 하는 데 필요한 시간이 분단위로 주어졌을 때, 
오븐구이가 끝나는 시각을 계산하는 프로그램을 작성하시오.

입력
첫째 줄에는 현재 시각이 나온다. 현재 시각은 
시 A (0 ≤ A ≤ 23) 와 분 B (0 ≤ B ≤ 59) 가 
정수로 빈칸을 사이에 두고 순서대로 주어진다. 

두 번째 줄에는 요리하는 데 필요한 시간 
C (0 ≤ C ≤ 1,000)   가 분 단위로 주어진다.

출력
첫째 줄에 종료되는 시각의 시와 분을 공백을 사이에 두고 출력한다. (단, 시는 0부터 23까지의 정수, 분은 0부터 59까지의 정수이다. 디지털 시계는 23시 59분에서 1분이 지나면 0시 0분이 된다.)

예제 입력 1 
14 30
20
예제 출력 1 
14 50
예제 입력 2 
17 40
80
예제 출력 2 
19 0
예제 입력 3 
23 48
25
예제 출력 3 
0 13
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int cHour = Integer.parseInt(st.nextToken()); // 현재 시각 
		int cMin = Integer.parseInt(st.nextToken()); // 현재 분 
		int workMinute = Integer.parseInt(br.readLine()); // 몇 분 간 요리하는지.
		
		int wHour = workMinute / 60; // 일 할 시간 
		int wMin = workMinute % 60;  // 일 할 분 
		
		// 현재 분 과 일해야 하는 분이 60 이상이라면, 1 시간을 추가해야 한다. -- 여기서 추가 1시간에 대한 것은 끝난다.
		wHour = ((cMin + wMin) < 60) ? wHour : wHour + 1;
		cMin = ((cMin + wMin) < 60) ? (cMin + wMin) : ((cMin + wMin) % 60);
		
		
		// 현재 시각과 요리하는 시각을 더한다. -- 위의 개념 (몇 일, 몇 달 등등..)이 없으므로, 한 줄로 끝난다. 
		cHour = ((cHour + wHour) < 24) ? (cHour + wHour) : ((cHour + wHour) % 24);
		
		StringBuilder sb = new StringBuilder();
		sb.append(cHour); sb.append(" "); sb.append(cMin);
		
		System.out.println(sb.toString());
	}

}
