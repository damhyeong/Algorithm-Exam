
import java.util.*;
import java.io.*;

/**
문제
예제를 보고 규칙을 유추한 뒤에 별을 찍어 보세요.

입력
첫째 줄에 N(1 ≤ N ≤ 100)이 주어진다.

출력
첫째 줄부터 2×N-1번째 줄까지 차례대로 별을 출력한다.

예제 입력 1 
5
예제 출력 1 
    *
   ***
  *****
 *******
*********
 *******
  *****
   ***
    *
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		StringBuilder sb = new StringBuilder();
		
		for(int i = 0, j = 2 * (n - 1); i < (2 * n - 1); i++, j--) {
			if(i <= j) {
				for(int x = 0; x < n - (i + 1); x++)
					sb.append(" ");
				for(int x = 0; x < 2 * i + 1; x++) {
					sb.append("*");
				}
				sb.append("\n");
			} else {
				for(int x = 0; x < n - (j + 1); x++)
					sb.append(" ");
				for(int x = 0; x < 2 * j + 1; x++) {
					sb.append("*");
				}
				sb.append("\n");
			}
		}
		System.out.print(sb);
	}

}
