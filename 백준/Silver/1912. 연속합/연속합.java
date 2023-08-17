
import java.util.*;
import java.io.*;

/**
연속합
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초 (추가 시간 없음)	128 MB	129612	48032	34052	35.731%
문제
n개의 정수로 이루어진 임의의 수열이 주어진다. 
우리는 이 중 연속된 몇 개의 수를 선택해서 구할 수 있는 합 중 가장 큰 합을 구하려고 한다. 
단, 수는 한 개 이상 선택해야 한다.

예를 들어서 10, -4, 3, 1, 5, 6, -35, 12, 21, -1 이라는 수열이 주어졌다고 하자. 
여기서 정답은 12+21인 33이 정답이 된다.

입력
첫째 줄에 정수 n(1 ≤ n ≤ 100,000)이 주어지고 둘째 줄에는 n개의 정수로 이루어진 수열이 주어진다. 
수는 -1,000보다 크거나 같고, 1,000보다 작거나 같은 정수이다.

출력
첫째 줄에 답을 출력한다.

예제 입력 1 
10
10 -4 3 1 5 6 -35 12 21 -1
예제 출력 1 
33
예제 입력 2 
10
2 1 -4 3 4 -4 6 5 -5 1
예제 출력 2 
14
예제 입력 3 
5
-1 -2 -3 -4 -5
예제 출력 3 
-1
 */

public class Main {
	public static long[] sequence;
	public static long[] seqSum;
	public static int findIndex = 0;
	public static long maxSum;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int n = Integer.parseInt(br.readLine());
		
		sequence = new long[n];
		seqSum = new long[n];
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		sequence[0] = Integer.parseInt(st.nextToken());
		seqSum[0] = sequence[0];
		maxSum = seqSum[0];
		if(seqSum[0] < 0)
			seqSum[0] = 0;
		for(int i = 1; i < n; i++) {
			sequence[i] = Integer.parseInt(st.nextToken());
			
			seqSum[i] = sequence[i] + seqSum[i - 1];
			
			if(seqSum[i] <= 0) {
				// 음수만 나올 때를 가정한다. 
				if(seqSum[i] >= maxSum)
					maxSum = seqSum[i];
				
				// 합쳐진 수열의 합이 음수라면, 수열에는 전혀 필요없어진다. (ex - 합쳤을 때 무조건 작아지는 수) 
				// 따라서, 0으로 만들고 다음 수의 합을 위해 0으로 만들어 놓는다. 
				seqSum[i] = 0;
				continue;
			}
			if(maxSum <= seqSum[i])
				maxSum = seqSum[i];
		}
		bw.write(Long.toString(maxSum));
		bw.flush();
		bw.close();
		br.close();
	}

}
