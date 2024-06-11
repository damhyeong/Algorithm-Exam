import java.util.*;
import java.io.*;

/**
나머지 합 실패
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	50253	14106	10165	26.502%
문제
수 N개 A1, A2, ..., AN이 주어진다. 이때, 연속된 부분 구간의 합이 M으로 나누어 떨어지는 구간의 개수를 구하는 프로그램을 작성하시오.

즉, Ai + ... + Aj (i ≤ j) 의 합이 M으로 나누어 떨어지는 (i, j) 쌍의 개수를 구해야 한다.

입력
첫째 줄에 N과 M이 주어진다. (1 ≤ N ≤ 10^6, 2 ≤ M ≤ 10^3) || (1 <= N <= 1_000_000, 2 <= M <= 1_000)

둘째 줄에 N개의 수 A1, A2, ..., AN이 주어진다. (0 ≤ Ai ≤ 10^9) || (0 <= Ai <= 1_000_000_000)

출력
첫째 줄에 연속된 부분 구간의 합이 M으로 나누어 떨어지는 구간의 개수를 출력한다.

예제 입력 1 
5 3
1 2 3 1 2
예제 출력 1 
7
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());
		
		long[] arr = new long[N];
		long[] remain = new long[M];
		
		st = new StringTokenizer(br.readLine());
		
		arr[0] = Long.parseLong(st.nextToken()) % (long)M;
		remain[(int) arr[0]]++;
		
		for(int i = 1; i < N; i++) {
			arr[i] = (arr[i - 1] + Integer.parseInt(st.nextToken())) % (long)M;
			remain[(int) arr[i]]++;
		}
		
		long count = 0;
		count += remain[0];
		
		for(int i = 0; i < M; i++) {
			
			if(remain[i] > 1) {
				long result = (remain[i] * (remain[i] - 1)) / 2;
				count += result;
			}
		}
		
		System.out.println(count);
	}

}
