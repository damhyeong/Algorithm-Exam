
import java.util.*;
import java.io.*;

/**
퇴사
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	512 MB	84155	42642	27956	49.747%

예제 입력 1 
7
3 10
5 20
1 10
1 20
2 15
4 40
2 200
예제 출력 1 
45
예제 입력 2 
10
1 1
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
예제 출력 2 
55
예제 입력 3 
10
5 10
5 9
5 8
5 7
5 6
5 10
5 9
5 8
5 7
5 6
예제 출력 3 
20
예제 입력 4 
10
5 50
4 40
3 30
2 20
1 10
1 10
2 20
3 30
4 40
5 50
예제 출력 4 
90

문제
상담원으로 일하고 있는 백준이는 퇴사를 하려고 한다.

오늘부터 N+1일째 되는 날 퇴사를 하기 위해서, 남은 N일 동안 최대한 많은 상담을 하려고 한다.

백준이는 비서에게 최대한 많은 상담을 잡으라고 부탁을 했고, 비서는 하루에 하나씩 서로 다른 사람의 상담을 잡아놓았다.

각각의 상담은 상담을 완료하는데 걸리는 기간 Ti와 상담을 했을 때 받을 수 있는 금액 Pi로 이루어져 있다.

N = 7인 경우에 다음과 같은 상담 일정표를 보자.
--------------------------------------------
 	1일	2일	3일	4일	5일	6일	7일
Ti	3	5	1	1	2	4	2
Pi	10	20	10	20	15	40	200
--------------------------------------------

1일에 잡혀있는 상담은 총 3일이 걸리며, 상담했을 때 받을 수 있는 금액은 10이다. 
5일에 잡혀있는 상담은 총 2일이 걸리며, 받을 수 있는 금액은 15이다.

상담을 하는데 필요한 기간은 1일보다 클 수 있기 때문에, 모든 상담을 할 수는 없다. 
예를 들어서 1일에 상담을 하게 되면, 2일, 3일에 있는 상담은 할 수 없게 된다. 
2일에 있는 상담을 하게 되면, 3, 4, 5, 6일에 잡혀있는 상담은 할 수 없다.

또한, N+1일째에는 회사에 없기 때문에, 6, 7일에 있는 상담을 할 수 없다.

퇴사 전에 할 수 있는 상담의 최대 이익은 1일, 4일, 5일에 있는 상담을 하는 것이며, 이때의 이익은 10+20+15=45이다.

상담을 적절히 했을 때, 백준이가 얻을 수 있는 최대 수익을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N (1 ≤ N ≤ 15)이 주어진다.

둘째 줄부터 N개의 줄에 Ti와 Pi가 공백으로 구분되어서 주어지며, 1일부터 N일까지 순서대로 주어진다. (1 ≤ Ti ≤ 5, 1 ≤ Pi ≤ 1,000)

출력
첫째 줄에 백준이가 얻을 수 있는 최대 이익을 출력한다.

해석 : 
	* Top - Down 방식으로 가야할 것이다.
	* 맨 뒤 인덱스부터 시작해서, N을 넘는 기간은 일단 dp[i] = 0으로 만든다.
	* arr[3] 이 3일이 걸린다면, dp[6] + arr[3] 과 max(dp[4], dp[5]) 중 큰 것을 dp[3]에 넣는다.
	* 이러한 과정을 i = 1 까지 하고 난 후, max를 따로 계산한다. -> 항상 마지막이 큰 배열이 아니다.  
	
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		
		int[][] arr = new int[N + 1][2];
		int[] dp = new int[N + 1];
		
		for(int i = 1; i <= N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine().trim());
			
			// 일하는 날짜  
			arr[i][0] = Integer.parseInt(st.nextToken());
			
			// 돈 
			arr[i][1] = Integer.parseInt(st.nextToken());
		}
		
		for(int i = N; i >= 1; i--) {
			// 퇴사 기간을 넘겨버리면 의미가 없다. 
			if(arr[i][0] + i > N + 1) {
				dp[i] = 0;
				if(i <= N - 1)
					dp[i] = dp[i + 1];
				continue;
			} else if(arr[i][0] + i == N + 1) {
				if(N == i) {
					dp[i] = arr[i][1];
					continue;
				}
				dp[i] = Math.max(arr[i][1], dp[i + 1]);
				continue;
			}
			// 비교해야 할 1번째 수. 
			int num1 = arr[i][1] + dp[arr[i][0] + i];
			
			// 비교 배열 중간 dp[] 배열 원소 중 더 큰게 있을 수도 있으므로, 탐색할 인덱스 설정. 
			int fIndex = arr[i][0] + 1;
			int lIndex = arr[i][0] + i;
			
			// 일하지 못하는 기간 중 가장 큰 수 추출 
			
			int num2 = dp[i + 1];
			
			// i 일에 일하는 것 -> num1 과 i 일을 포기하고 그 사이에 존재하는 일을 할 때 중 더 효율이 큰 것을 dp에 넣는다. 
			dp[i] = num1 >= num2 ? num1 : num2;
		}
		
		int max = -1;
		for(int i = 1; i < N + 1; i++) {
			max = dp[i] >= max ? dp[i] : max;
		}
		bw.write(Integer.toString(max));
		bw.flush();
		bw.close();
		br.close();
	}

}
