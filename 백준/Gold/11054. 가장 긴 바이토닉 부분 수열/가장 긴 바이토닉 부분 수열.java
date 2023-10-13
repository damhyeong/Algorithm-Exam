
import java.util.*;
import java.io.*;

/**
가장 긴 바이토닉 부분 수열
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	49104	25132	19644	50.722%
문제
수열 S가 어떤 수 Sk를 기준으로 S1 < S2 < ... Sk-1 < Sk > Sk+1 > ... SN-1 > SN을 만족한다면, 
그 수열을 바이토닉 수열이라고 한다.

예를 들어, {10, 20, 30, 25, 20}과 {10, 20, 30, 40}, {50, 40, 25, 10} 은 바이토닉 수열이지만,  
{1, 2, 3, 2, 1, 2, 3, 2, 1}과 {10, 20, 30, 40, 20, 30} 은 바이토닉 수열이 아니다.

수열 A가 주어졌을 때, 그 수열의 부분 수열 중 바이토닉 수열이면서 가장 긴 수열의 길이를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 수열 A의 크기 N이 주어지고, 둘째 줄에는 수열 A를 이루고 있는 Ai가 주어진다. 
(1 ≤ N ≤ 1,000, 1 ≤ Ai ≤ 1,000)

출력
첫째 줄에 수열 A의 부분 수열 중에서 가장 긴 바이토닉 수열의 길이를 출력한다.

예제 입력 1 
10
1 5 2 1 4 3 4 5 2 1
예제 출력 1 
7
힌트
예제의 경우 {1 5 2 1 4 3 4 5 2 1}이 가장 긴 바이토닉 부분 수열이다.
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		int[] arr = new int[N + 1];
		int[] dpUp = new int[N + 1];
		int[] dpDn = new int[N + 1];
		int[] dpTotal = new int[N + 1];
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		for(int i = 1; i <= N; i++) 
			arr[i] = Integer.parseInt(st.nextToken());
		
		// 오름차순 dp배열 구하기 
		for(int i = 1; i <= N; i++) {
			dpUp[i] = 1; // 최초일 수도 있으므로, 디폴트 값 1 설정. 
			for(int j = 1; j < i; j++) {
				if(arr[j] < arr[i] && dpUp[i] < dpUp[j] + 1) {
					dpUp[i] = dpUp[j] + 1;
				}
			}
		}
		
		// 내림차순 dp배열 구하기 
		for(int i = N; i >= 1; i--) {
			dpDn[i] = 1;
			for(int j = N; j > i; j--) {
				if(arr[j] < arr[i] && dpDn[i] < dpDn[j] + 1) {
					dpDn[i] = dpDn[j] + 1;
				}
			}
		}
		
		// 오름차순과 내림차순 dp배열이 모두 구해졌으므로, 각 위치의 dpUp + dpDn - 1 하면 최댓값이 나올 것이다. 
		int max = -1;
		for(int i = 1; i <= N; i++) {
			dpTotal[i] = dpUp[i] + dpDn[i] - 1; // i 부분이 하나 겹치므로 빼준다. 
			
			if(max < dpTotal[i])
				max = dpTotal[i];
		}
		
		
		bw.write(Integer.toString(max));
		bw.flush();
		bw.close();
		br.close();
	}

}
