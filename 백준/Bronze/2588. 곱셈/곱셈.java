
import java.util.*;
import java.io.*;

/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	386425	181013	151333	46.911%
문제
(세 자리 수) × (세 자리 수)는 다음과 같은 과정을 통하여 이루어진다.



(1)과 (2)위치에 들어갈 세 자리 자연수가 주어질 때 (3), (4), (5), (6)위치에 들어갈 값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 (1)의 위치에 들어갈 세 자리 자연수가, 둘째 줄에 (2)의 위치에 들어갈 세자리 자연수가 주어진다.

출력
첫째 줄부터 넷째 줄까지 차례대로 (3), (4), (5), (6)에 들어갈 값을 출력한다.

예제 입력 1 
472
385
예제 출력 1 
2360
3776
1416
181720
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		
		Integer num1 = Integer.parseInt(br.readLine());
		Integer num2 = Integer.parseInt(br.readLine());
		
		Integer copyNum2 = num2;
		Integer mulNum = -1;
		
		while(copyNum2 != 0) {
			// (2) 의 가장 낮은 숫자부터 추출한다.
			mulNum = copyNum2 % 10;
			
			// 그 다음 낮은 숫자를 추출하기 위해서 10으로 나눈다.
			copyNum2 /= 10;
			
			// (2) 숫자에서 추출된 가장 낮은 숫자를 (1) 과 곱하여 (3, 4, 5) 를 차례대로 얻는다) 
			sb.append(mulNum * num1); sb.append("\n");
		}
		
		// (6) 은 num1과 num2를 곱해주기만 하면 된다. (최종값)
		sb.append(num1 * num2);
		System.out.println(sb);
	}

}
