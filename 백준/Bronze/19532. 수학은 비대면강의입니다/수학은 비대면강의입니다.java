import java.util.*;
import java.io.*;

/**
수학은 비대면강의입니다

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초 (추가 시간 없음)	1024 MB	34399	17419	15353	51.319%

문제
-----
수현이는 4차 산업혁명 시대에 살고 있는 중학생이다. 
코로나 19로 인해, 수현이는 버추얼 학교로 버추얼 출석해 버추얼 강의를 듣고 있다. 
수현이의 버추얼 선생님은 문자가 2개인 연립방정식을 해결하는 방법에 대해 강의하고, 다음과 같은 문제를 숙제로 냈다.

--------------------------
다음 연릭방정식에서 x와 y의 값을 계산하시오.

		/ ax + by = c
		|
		\ dx + ey = f

--------------------------

각 칸에는 -999 이상 999 이하의 정수만 입력 할 수 있다.

입력
-----
정수 a, b, c, d, e, f 가 공백으로 구분되어 차례대로 주어진다. 
( -999 <= a, b, c, d, e, f <= 999 )

문제에서 언급한 방정식을 만족하는 ( x, y )가 유일하게 존재하고, 
이 때 x 와 y 가 각각 -999 이상 999 이하의 정수인 경우만 입력으로 주어짐이 보장된다.

출력
-----
문제의 답인 x 와 y 를 구분해 출력한다. 

예제 입력 1 
1 3 -1 4 1 7
예제 출력 1 
2 -1
예제 입력 2 
2 5 8 3 -4 -11
예제 출력 2 
-1 2

이 문제의 의도 :
--------------
a, b, c | d, e, f 의 등식을 이용하여 x, y를 -999 ~ +999 까지 루프를 돌려 강제로 x, y 값을 구할 수 있다.
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		int e = Integer.parseInt(st.nextToken());
		int f = Integer.parseInt(st.nextToken());
		
		int resultX = -1000, resultY = 0;
		for(int x = -999; x <= 999; x++) {
			for(int y = -999; y <= 999; y++) {
				
				boolean f1 = ((a * x + b * y) == c) ? true : false;
				boolean f2 = ((d * x + e * y) == f) ? true : false;
				
				if(f1 && f2) {
					resultX = x;
					resultY = y;
					break;
				}
			}
			if(resultX != -1000)
				break;
		}
		System.out.println(resultX + " " + resultY);
	}

}
