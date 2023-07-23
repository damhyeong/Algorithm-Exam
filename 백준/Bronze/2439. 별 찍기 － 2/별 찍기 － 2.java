
import java.util.*;
import java.io.*;

/**
문제
첫째 줄에는 별 1개, 둘째 줄에는 별 2개, N번째 줄에는 별 N개를 찍는 문제

하지만, 오른쪽을 기준으로 정렬한 별(예제 참고)을 출력하시오.

입력
첫째 줄에 N(1 ≤ N ≤ 100)이 주어진다.

출력
첫째 줄부터 N번째 줄까지 차례대로 별을 출력한다.

예제 입력 1 
5

예제 출력 1 
    *
   **
  ***
 ****
*****
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int t = Integer.parseInt(st.nextToken());
		StringBuilder sb = new StringBuilder();
		
		for(int i = 0; i < t; i++) {
			for(int j = t - 1; j >= 0; j--) {
				if(j <= i)
					sb.append('*');
				else
					sb.append(' ');
			}
			sb.append('\n');
		}
		System.out.print(sb);
	}

}
