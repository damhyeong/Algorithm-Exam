
import java.util.*;
import java.io.*;

/**
문제
B진법 수 N이 주어진다. 이 수를 10진법으로 바꿔 출력하는 프로그램을 작성하시오.

10진법을 넘어가는 진법은 숫자로 표시할 수 없는 자리가 있다. 이런 경우에는 다음과 같이 알파벳 대문자를 사용한다.

A: 10, B: 11, ..., F: 15, ..., Y: 34, Z: 35

입력
첫째 줄에 N과 B가 주어진다. (2 ≤ B ≤ 36)

B진법 수 N을 10진법으로 바꾸면, 항상 10억보다 작거나 같다.

출력
첫째 줄에 B진법 수 N을 10진법으로 출력한다.

예제 입력 1 
ZZZZZ 36
예제 출력 1 
60466175
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		String preStr = st.nextToken();
		int n = Integer.parseInt(st.nextToken());
		
		LinkedList<Long> tenList = new LinkedList<Long>();
		
		for(int i = 0; i < preStr.length(); i++) {
			char preChar = preStr.charAt(i);
			long newNum;
			if('0' <= preChar && preChar <= '9') {
				newNum = (Character.getNumericValue(preChar));
			}else {
				newNum = (10 + preStr.charAt(i) - 'A');
			}
			
			tenList.add(newNum);
			
			for(int j = 0; j < tenList.size() - 1; j++) {
				tenList.set(j, tenList.get(j) * n);
			}
		}
		long sum = 0;
		for(int i = 0; i < tenList.size(); i++) {
			sum += tenList.get(i);
		}
		System.out.println(sum);
	}

}
