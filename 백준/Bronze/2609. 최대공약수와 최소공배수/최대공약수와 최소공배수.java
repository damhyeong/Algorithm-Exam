
import java.util.*;
import java.io.*;

/**
최대공약수와 최소공배수
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	98284	56719	46063	57.973%
문제
두 개의 자연수를 입력받아 최대 공약수와 최소 공배수를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에는 두 개의 자연수가 주어진다. 이 둘은 10,000이하의 자연수이며 사이에 한 칸의 공백이 주어진다.

출력
첫째 줄에는 입력으로 주어진 두 수의 최대공약수를, 둘째 줄에는 입력으로 주어진 두 수의 최소 공배수를 출력한다.

예제 입력 1 
24 18
예제 출력 1 
6
72
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int num1 = Integer.parseInt(st.nextToken());
		int num2 = Integer.parseInt(st.nextToken());
		int bNum, sNum;
		
		if(num1 >= num2) {
			bNum = num1;
			sNum = num2;
		}else {
			bNum = num2;
			sNum = num1;
		}
		
		int biggestDivNum = runMethod1(bNum, sNum);
		int smallestMulNum = (bNum * sNum) / biggestDivNum;
		bw.write(Integer.toString(biggestDivNum) + "\n");
		bw.write(Integer.toString(smallestMulNum));
		bw.flush();
		bw.close();
		br.close();
	}
	public static int runMethod1(int big, int small) {
		if(big % small == 0)
			return small;
		
		return runMethod1(small, big % small);
	}
}
