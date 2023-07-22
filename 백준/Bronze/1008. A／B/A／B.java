
import java.util.*;
import java.io.*;

/**
문제
두 정수 A와 B를 입력받은 다음, A/B를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 A와 B가 주어진다. (0 < A, B < 10)

출력
첫째 줄에 A/B를 출력한다. 실제 정답과 출력값의 절대오차 또는 상대오차가 10-9 이하이면 정답이다.
 */
public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		
		int share = a / b;
		int left = a % b;
		
		System.out.printf("%d", share);
		
		if(left != 0) {
			System.out.printf(".");
			for(int i = 0; i < 20; i++) {
				left *= 10;
				System.out.printf("%d", (left / b));
				if(left % b == 0)
					break;
				left %= b;
			}
		}
		
	}

}
