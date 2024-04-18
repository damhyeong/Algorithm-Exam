import java.util.*;
import java.io.*;

/**
달팽이는 올라가고 싶다 성공다국어
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.25 초 (추가 시간 없음)	128 MB	251609	80014	63592	31.269%

문제
땅 위에 달팽이가 있다. 이 달팽이는 높이가 V미터인 나무 막대를 올라갈 것이다.

달팽이는 낮에 A미터 올라갈 수 있다. 하지만, 밤에 잠을 자는 동안 B미터 미끄러진다. 또, 정상에 올라간 후에는 미끄러지지 않는다.

달팽이가 나무 막대를 모두 올라가려면, 며칠이 걸리는지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 세 정수 A, B, V가 공백으로 구분되어서 주어진다. (1 ≤ B < A ≤ V ≤ 1,000,000,000)

출력
첫째 줄에 달팽이가 나무 막대를 모두 올라가는데 며칠이 걸리는지 출력한다.

예제 입력 1 
2 1 5
예제 출력 1 
4
예제 입력 2 
5 1 6
예제 출력 2 
2
예제 입력 3 
100 99 1000000000
예제 출력 3 
999999901
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int A = Integer.parseInt(st.nextToken()); // 낮에 A미터 올라간다. 
		int B = Integer.parseInt(st.nextToken()); // 밤에 B미터 미끄러진다.
		int V = Integer.parseInt(st.nextToken()); // 정상은 V미터이다. 
		
		int dayPerM = A - B;
		
		int tempV = V - B;
		
		int result = 0;
		
		if(A == V) {
			result = 1;
		} else if(tempV % dayPerM == 0) {
			result = tempV / dayPerM;
		} else {
			result = (tempV / dayPerM) + 1;
		}
		
		System.out.println(result);
	}

}
