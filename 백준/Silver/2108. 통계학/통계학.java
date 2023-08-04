
import java.util.*;
import java.io.*;

/**
통계학
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	256 MB	145972	34099	27314	25.874%

예제 입력 1 
5
1
3
8
-2
2
예제 출력 1 
2
2
1
10
예제 입력 2 
1
4000
예제 출력 2 
4000
4000
4000
0
예제 입력 3 
5
-1
-2
-3
-1
-2
예제 출력 3 
-2
-2
-1
2
예제 입력 4 
3
0
0
-1
예제 출력 4 
0
0
0
1
(0 + 0 + (-1)) / 3 = -0.333333... 이고 이를 첫째 자리에서 반올림하면 0이다. -0으로 출력하면 안된다.

문제
수를 처리하는 것은 통계학에서 상당히 중요한 일이다. 
통계학에서 N개의 수를 대표하는 기본 통계값에는 다음과 같은 것들이 있다. 
단, N은 홀수라고 가정하자.

산술평균 : N개의 수들의 합을 N으로 나눈 값
중앙값 : N개의 수들을 증가하는 순서로 나열했을 경우 그 중앙에 위치하는 값
최빈값 : N개의 수들 중 가장 많이 나타나는 값
범위 : N개의 수들 중 최댓값과 최솟값의 차이
N개의 수가 주어졌을 때, 네 가지 기본 통계값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 수의 개수 N(1 ≤ N ≤ 500,000)이 주어진다. 단, N은 홀수이다. 
그 다음 N개의 줄에는 정수들이 주어진다. 
입력되는 정수의 절댓값은 4,000을 넘지 않는다.

출력
첫째 줄에는 산술평균을 출력한다. 
소수점 이하 첫째 자리에서 반올림한 값을 출력한다.

둘째 줄에는 중앙값을 출력한다.

셋째 줄에는 최빈값을 출력한다. 
여러 개 있을 때에는 최빈값 중 두 번째로 작은 값을 출력한다.

넷째 줄에는 범위를 출력한다.
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		int N = Integer.parseInt(br.readLine());
		int n = N;
		
		// 정렬 후 중앙값 출력을 위한 배열 
		int[] arr = new int[N];
		
		// 최빈값을 알기 위한 HashMap 선언 
		HashMap<Integer, Integer> countNum = new HashMap<>();
		
		int sum = 0;
		
		int min = Integer.parseInt(br.readLine());
		int max = min;
		arr[0] = min;
		countNum.put(min, 1);
		sum += min;
		for(int i = 1; i < N; i++) {
			int newNum = Integer.parseInt(br.readLine());
			sum += newNum;
			min = (min >= newNum) ? newNum : min;
			max = (max <= newNum) ? newNum : max;
			arr[i] = newNum;
			
			if(countNum.containsKey(newNum))
				countNum.put(newNum, countNum.get(newNum) + 1);
			else
				countNum.put(newNum, 1);
		}
		
		
		//첫째 줄에는 산술평균을 출력한다. 
		bw.write(Integer.toString(Math.round(sum / (float)N)) + "\n");
		//소수점 이하 첫째 자리에서 반올림한 값을 출력한다.
		
		//둘째 줄에는 중앙값을 출력한다.
		Arrays.sort(arr);
		bw.write(Integer.toString(arr[N/2]) + "\n");
		
		//셋째 줄에는 최빈값을 출력한다.
		Iterator iter = countNum.keySet().iterator();
		int maxCnt = countNum.get((int)iter.next());
		while(iter.hasNext()) {
			int newNum = countNum.get((int)iter.next());
			if(maxCnt <= newNum)
				maxCnt = newNum;
		}
		// 같은 최솟값들을 담아두기 위한 List 선언. 추후 정렬하여 두 번째로 작은 값 출력 예정. 
		LinkedList<Integer> maxKeyList = new LinkedList<Integer>();
		
		iter = countNum.keySet().iterator();
		while(iter.hasNext()) {
			int key = (int)iter.next();
			int newNum = countNum.get(key);
			if(newNum == maxCnt) {
				maxKeyList.add(key);
			}
		}
		
		maxKeyList.sort(new Comparator<Integer>() {
			public int compare(Integer n1, Integer n2) {
				
				return n1 - n2;
			}
		});
		
		if(maxKeyList.size() == 1)
			bw.write(Integer.toString(maxKeyList.get(0)) + "\n");
		else
			bw.write(Integer.toString(maxKeyList.get(1)) + "\n");
		
		//여러 개 있을 때에는 최빈값 중 두 번째로 작은 값을 출력한다.
		
		//넷째 줄에는 범위를 출력한다.
		bw.write(Integer.toString(max - min) + "\n");
		
		bw.flush();
		bw.close();
		br.close();
	}

}
