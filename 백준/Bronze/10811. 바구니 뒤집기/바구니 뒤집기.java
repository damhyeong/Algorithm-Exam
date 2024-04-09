import java.util.*;
import java.io.*;

/**
바구니 뒤집기

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	63809	33458	29641	53.145%

문제
도현이는 바구니를 총 N개 가지고 있고, 각각의 바구니에는 1번부터 N번까지 번호가 순서대로 적혀져 있다. 
바구니는 일렬로 놓여져 있고, 
가장 왼쪽 바구니를 1번째 바구니, 그 다음 바구니를 2번째 바구니, ..., 가장 오른쪽 바구니를 N번째 바구니라고 부른다. 

도현이는 앞으로 M번 바구니의 순서를 역순으로 만들려고 한다. 
도현이는 한 번 순서를 역순으로 바꿀 때, 순서를 역순으로 만들 범위를 정하고, 
그 범위에 들어있는 바구니의 순서를 역순으로 만든다.

바구니의 순서를 어떻게 바꿀지 주어졌을 때, 
M번 바구니의 순서를 역순으로 만든 다음, 바구니에 적혀있는 번호를 가장 왼쪽 바구니부터 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 N (1 ≤ N ≤ 100)과 M (1 ≤ M ≤ 100)이 주어진다.

둘째 줄부터 M개의 줄에는 바구니의 순서를 역순으로 만드는 방법이 주어진다. 
방법은 i j로 나타내고, 왼쪽으로부터 i번째 바구니부터 j번째 바구니의 순서를 역순으로 만든다는 뜻이다. 
(1 ≤ i ≤ j ≤ N)

도현이는 입력으로 주어진 순서대로 바구니의 순서를 바꾼다.

출력
모든 순서를 바꾼 다음에, 가장 왼쪽에 있는 바구니부터 바구니에 적혀있는 순서를 공백으로 구분해 출력한다.

예제 입력 1 
5 4
1 2
3 4
1 4
2 2
예제 출력 1 
3 4 1 2 5
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken()); // 바구니 개수 - 바구니에는 1~N까지 번호가 적혀 있다. 
		int M = Integer.parseInt(st.nextToken()); // 바구니를 역순으로 만들 횟수.
		
		int[] buckets = new int[N];
		// Arrays.setAll 함수를 이용하여, buckets의 모든 요소에 대하여 적용 할 람다 함수를 기입한다.
		Arrays.setAll(buckets, (index) -> index + 1);
		
		while(M-- > 0) { // (5 > 0, 4 > 0, 3 > 0, 2 > 0, 1 > 0) 5번 루프 | ex- "--M"이라면 (4 > 0, 3 > 0, 2 >0, 1 > 0) 총 4번 루
			st = new StringTokenizer(br.readLine());
			
			int i = Integer.parseInt(st.nextToken()) - 1; // 바꿀 바구니 초기 번호 
			int j = Integer.parseInt(st.nextToken()) - 1; // 바꿀 바구니 마지막 번호
			int temp; // 서로 번호를 바꾸기 위해 필요한 임시 값 저장소.
			
			while(i < j) {
				temp = buckets[i];
				buckets[i] = buckets[j];
				buckets[j] = temp;
				i++; j--; // 시작과 종료 지점이 같거나, 엇갈릴 때 까지.
			}
		}
		
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < buckets.length; i++) {
			sb.append(buckets[i] + " ");
		}
		System.out.println(sb.toString());
	}

}
