
import java.util.*;
import java.io.*;
import java.math.*;

/**
팩토리얼 0의 개수
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	67455	32197	26826	47.491%
문제
N!에서 뒤에서부터 처음 0이 아닌 숫자가 나올 때까지 0의 개수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N이 주어진다. (0 ≤ N ≤ 500)

출력
첫째 줄에 구한 0의 개수를 출력한다.

예제 입력 1 
10
예제 출력 1 
2
예제 입력 2 
3
예제 출력 2 
0
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		BigInteger bInt = new BigInteger("1");
		
		for(int i = N; i > 1; i--) {
			bInt = bInt.multiply(new BigInteger(Integer.toString(i)));
		}
		String strNum = bInt.toString();
		
		int cnt = 0;
		int index = strNum.length() - 1;
		while(true) {
			if(strNum.charAt(index) != '0')
				break;
			cnt++; index--;
		}
		
		bw.write(Integer.toString(cnt));
		bw.flush();
		bw.close();
		br.close();
	}

}
