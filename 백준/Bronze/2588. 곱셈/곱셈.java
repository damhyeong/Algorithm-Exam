
import java.util.*;
import java.io.*;

/**
문제
(세 자리 수) × (세 자리 수)는 다음과 같은 과정을 통하여 이루어진다.



(1)과 (2)위치에 들어갈 세 자리 자연수가 주어질 때 (3), (4), (5), (6)위치에 들어갈 값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 (1)의 위치에 들어갈 세 자리 자연수가, 둘째 줄에 (2)의 위치에 들어갈 세자리 자연수가 주어진다.

출력
첫째 줄부터 넷째 줄까지 차례대로 (3), (4), (5), (6)에 들어갈 값을 출력한다.
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		//StringTokenizer st = new StringTokenizer(br.readLine());
		
		int num_1 = Integer.parseInt(br.readLine());
		int num_2 = Integer.parseInt(br.readLine());
		
		String strNum_2 = Integer.toString(num_2);
		
		int[] numArr = new int[strNum_2.length()];
		
		for(int i = strNum_2.length() - 1; i >= 0; i--) {
			char num = strNum_2.charAt(i);
			numArr[i] =  num_1 * Character.getNumericValue(num);
		}
		System.out.printf("%d\n%d\n%d\n%d", numArr[2], numArr[1], numArr[0], num_1 * num_2);
	}

}
