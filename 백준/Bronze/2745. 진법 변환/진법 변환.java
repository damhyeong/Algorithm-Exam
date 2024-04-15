import java.util.*;
import java.io.*;

/**
진법 변환

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	53492	26222	22328	48.722%

문제
B진법 수 N이 주어진다. 
이 수를 10진법으로 바꿔 출력하는 프로그램을 작성하시오.

10진법을 넘어가는 진법은 숫자로 표시할 수 없는 자리가 있다. 
이런 경우에는 다음과 같이 알파벳 대문자를 사용한다.

A: 10, B: 11, ..., F: 15, ..., Y: 34, Z: 35

입력
첫째 줄에 N과 B가 주어진다. 
(2 ≤ B ≤ 36)

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
		
		String orgStr = st.nextToken();
		int ruleNum = Integer.parseInt(st.nextToken());
		
		int result = 0;  // 결과는 항상 10억보다 작다고 말함. 
		int notation = orgStr.length() - 1; // 지수표시 
		for(int i = 0; i < orgStr.length(); i++) {
			char ch = orgStr.charAt(i);
			int realVal;
			
			if('A' <= ch && ch <= 'Z') { // 숫자 대신 알파벳이 나올 경우 치환하기.
				realVal = ch - 'A' + 10;
			} else { // 숫자이다. 
				realVal = ch - '0';
			}
			
			int mulNotation = 1;
			for(int j = 0; j < notation; j++)
				mulNotation *= ruleNum;
			
			notation--;
			
			result += realVal * mulNotation;
		}
		
		System.out.println(result);
	}

}
