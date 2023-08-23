
import java.util.*;
import java.io.*;

/**
수 찾기
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	220446	66733	44427	29.710%
문제
N개의 정수 A[1], A[2], …, A[N]이 주어져 있을 때, 이 안에 X라는 정수가 존재하는지 알아내는 프로그램을 작성하시오.

입력
첫째 줄에 자연수 N(1 ≤ N ≤ 100,000)이 주어진다. 
다음 줄에는 N개의 정수 A[1], A[2], …, A[N]이 주어진다. 
다음 줄에는 M(1 ≤ M ≤ 100,000)이 주어진다. 
다음 줄에는 M개의 수들이 주어지는데, 이 수들이 A안에 존재하는지 알아내면 된다. 
모든 정수의 범위는 -231 보다 크거나 같고 231보다 작다.

출력
M개의 줄에 답을 출력한다. 존재하면 1을, 존재하지 않으면 0을 출력한다.

예제 입력 1 
5
4 1 5 2 3
5
1 3 7 9 5
예제 출력 1 
1
1
0
0
1
 */

public class Main {
	public static int[] number;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		
		number = new int[N];
		StringTokenizer st = new StringTokenizer(br.readLine());
		for(int i = 0; i < N; i++) {
			number[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(number);
		
		int M = Integer.parseInt(br.readLine());
		st = new StringTokenizer(br.readLine());
		for(int i = 0; i < M; i++) {
			if(getBinarySearch(Integer.parseInt(st.nextToken()), 0, number.length - 1)) {
				bw.write("1\n");
			} else {
				bw.write("0\n");
			}
		}
		bw.flush();
		bw.close();
		br.close();
	}
	
	public static boolean getBinarySearch(int num, int sIndex, int lIndex) {
		if(sIndex <= lIndex) {
			int mIndex = (sIndex + lIndex) / 2;
			
			if(number[mIndex] == num)
				return true;
			else if(number[mIndex] < num) {
				return getBinarySearch(num, mIndex + 1, lIndex);
			} else if(number[mIndex] > num){
				return getBinarySearch(num, sIndex, mIndex - 1);
			}
		} 
		return false;	
	}
}
