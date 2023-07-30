
import java.util.*;
import java.io.*;

/**
문제
수직선 위에 N개의 좌표 X1, X2, ..., XN이 있다. 이 좌표에 좌표 압축을 적용하려고 한다.

Xi를 좌표 압축한 결과 X'i의 값은 Xi > Xj를 만족하는 서로 다른 좌표 Xj의 개수와 같아야 한다.

X1, X2, ..., XN에 좌표 압축을 적용한 결과 X'1, X'2, ..., X'N를 출력해보자.

입력
첫째 줄에 N이 주어진다.

둘째 줄에는 공백 한 칸으로 구분된 X1, X2, ..., XN이 주어진다.

출력
첫째 줄에 X'1, X'2, ..., X'N을 공백 한 칸으로 구분해서 출력한다.

제한
1 ≤ N ≤ 1,000,000
-10의 9승 ≤ Xi ≤ 10의 9승 
예제 입력 1 
5
2 4 -10 4 -9
예제 출력 1 
2 3 0 3 1
예제 입력 2 
6
1000 999 1000 999 1000 999
예제 출력 2 
1 0 1 0 1 0
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		// 기존 값을 저장하기 위한 arr 배열 선언. 
		int[] arr = new int[N];
		// 중복 값을 삭제하고, 중복되지 않는 수가 몇 개인지 파악하기 위한 linkedSet 선언.
		LinkedHashSet<Integer> linkedSet = new LinkedHashSet<Integer>();
		
		for(int i = 0; i < N; i++) {
			int num = Integer.parseInt(st.nextToken());
			arr[i] = num;
			linkedSet.add(num);
		}
		
		// linkArr로 정렬하기 위해 중복되지 않은 수 만큼의 배열 선언 
		int[] linkArr = new int[linkedSet.size()];
		
		// Set의 Iterator 빼내기.
		Iterator iter = linkedSet.iterator();
		
		int k = 0;
		
		// 중복되지 않은 값을 linkArr에 저장.
		while(iter.hasNext()) {
			linkArr[k++] = (int) iter.next();
		}
		
		// linkArr로 정렬. => 만약 중복되지 않은 수가 4개라면, linkArr의 크기도 4이다. 
		Arrays.sort(linkArr);
		
		// 각 숫자에 좌표 압축을 위한 숫자 할당. => 키는 숫자이며, 연결된 밸류도 숫자이다.
		// 만약 -951, 100, 500 순으로 linkArr가 계산되었다면, (-951, 0), (100, 1), (500, 2)로 매핑된다. 
		HashMap<Integer, Integer> numMap = new HashMap<>();
		// 위의 설명을 이행하기 위한 반복문 
		for(int i = 0; i < linkArr.length; i++) {
			numMap.put(linkArr[i], i);
		}
		
		// 좌표 압축을 위해 매핑해 놓은 압축좌표를 출력하고, 한 칸 띈다.
		for(int i = 0; i < N; i++) {
			bw.write(numMap.get(arr[i]) + " ");
		}
		bw.flush();
		bw.close();
		br.close();
		// 제발 시간초과만 안되라..... 
	}

}
