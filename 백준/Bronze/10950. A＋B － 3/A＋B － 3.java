
import java.util.*;
import java.io.*;

/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	304928	177715	148456	58.413%

문제
두 정수 A와 B를 입력받은 다음, A+B를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 테스트 케이스의 개수 T가 주어진다.

각 테스트 케이스는 한 줄로 이루어져 있으며, 각 줄에 A와 B가 주어진다. (0 < A, B < 10)

출력
각 테스트 케이스마다 A+B를 출력한다.

예제 입력 1 
5
1 1
2 3
3 4
9 8
5 2
예제 출력 1 
2
5
7
17
7
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int loop = Integer.parseInt(br.readLine());
		
		/**
		 * 1. loop > 0 비교 당시, loop 는 처음 입력된 값이랑 동일하다.
		 * 2. loop > 0 비교 후, loop -= 1 가 실행된다.
		 * 3. "--"은 변수의 앞, 뒤 어디에 쓰이는지에 따라 실행 우선순위가 결정된다.
		 * 4. "--"가 앞에 배치될 경우, loop -= 1 실행 후 loop > 0을 비교한다.
		 * 5. "--"가 뒤에 배치될 경우, loop > 0 비교 후 loop -= 1이 실행된다.
		 * 6. 즉, "--"의 위치에 따라 loop의 값은 선 반영, 후 반영으로 나눠진다. 
		 * 7. 하지만, 입력된 loop의 연산자 "--"가 앞, 뒤 이던, 똑같은 루프 개수를 가진다.
		 */
		
		StringBuilder sb = new StringBuilder();
		while(loop-- > 0) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int A = Integer.parseInt(st.nextToken());
			int B = Integer.parseInt(st.nextToken());
			sb.append(A + B); sb.append("\n");
		}
		System.out.println(sb.toString());
	}

}
