
import java.util.*;
import java.io.*;

/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	512 MB	186327	74992	68298	40.856%
문제
꼬마 정민이는 이제 A + B 정도는 쉽게 계산할 수 있다. 이제 A + B + C를 계산할 차례이다!

입력
첫 번째 줄에 A, B, C (1 ≤ A, B, C ≤ 1012)이 공백을 사이에 두고 주어진다.

출력
A+B+C의 값을 출력한다.

예제 입력 1 
77 77 7777
예제 출력 1 
7931
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		Long A = Long.parseLong((String) st.nextElement());
		Long B = Long.parseLong((String) st.nextElement());
		Long C = Long.parseLong((String) st.nextElement());
		
		System.out.println((A + B + C));
	}

}
