
import java.util.*;
import java.io.*;

/**
동전 0
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	127789	67715	52011	52.158%
문제
준규가 가지고 있는 동전은 총 N종류이고, 각각의 동전을 매우 많이 가지고 있다.

동전을 적절히 사용해서 그 가치의 합을 K로 만들려고 한다. 이때 필요한 동전 개수의 최솟값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 주어진다. (1 ≤ N ≤ 10, 1 ≤ K ≤ 100,000,000)

둘째 줄부터 N개의 줄에 동전의 가치 Ai가 오름차순으로 주어진다. (1 ≤ Ai ≤ 1,000,000, A1 = 1, i ≥ 2인 경우에 Ai는 Ai-1의 배수)

출력
첫째 줄에 K원을 만드는데 필요한 동전 개수의 최솟값을 출력한다.

예제 입력 1 
10 4200
1
5
10
50
100
500
1000
5000
10000
50000
예제 출력 1 
6
예제 입력 2 
10 4790
1
5
10
50
100
500
1000
5000
10000
50000
예제 출력 2 
12
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken()); int K = Integer.parseInt(st.nextToken());
		
		int[] price = new int[N];
		for(int i = 0; i < N; i++) {
			price[i] = Integer.parseInt(br.readLine());
		}
		
		int cnt = 0;
		while(K != 0) {
			if(K / price[N - 1] >= 1) {
				cnt += K / price[N - 1];
			}
			K %= price[N - 1];
			N--;
		}
		bw.write(Integer.toString(cnt));
		bw.flush();
		bw.close();
		br.close();
	}

}
