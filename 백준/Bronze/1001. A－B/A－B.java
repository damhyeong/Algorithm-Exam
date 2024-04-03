
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	432661	295673	248464	69.599%
문제
두 정수 A와 B를 입력받은 다음, A-B를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 A와 B가 주어진다. (0 < A, B < 10)

출력
첫째 줄에 A-B를 출력한다.

예제 입력 1 
3 2
예제 출력 1 
1
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		/** 
		 st.nextElement()는 기본 분산자(delim) " " 공백을 가지고 String 형태를 Object로 return 한 것이다.
		 따라서, Return 된 Object를 다시 DownCasting(String) 한다면, 정상적으로 운용이 가능하다. 
		 StringTokenizer Class의 nextElement()는 Object Type을 반환하지만, 
		 StringTokenizer.nextElement() { return this.nextToken } 이다.
		 */
		Integer a = Integer.parseInt((String)st.nextElement());
		Integer b = Integer.parseInt(st.nextToken());
		
		System.out.println(a - b);
	}

}
