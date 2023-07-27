
import java.util.*;
import java.io.*;

/**
문제
세 점이 주어졌을 때, 축에 평행한 직사각형을 만들기 위해서 필요한 네 번째 점을 찾는 프로그램을 작성하시오.

입력
세 점의 좌표가 한 줄에 하나씩 주어진다. 좌표는 1보다 크거나 같고, 1000보다 작거나 같은 정수이다.

출력
직사각형의 네 번째 점의 좌표를 출력한다.

예제 입력 1 
5 5
5 7
7 5
예제 출력 1 
7 7
예제 입력 2 
30 20
10 10
10 20
예제 출력 2 
30 10
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		HashMap<Integer, Integer> xMap = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> yMap = new HashMap<Integer, Integer>();
		StringTokenizer st;
		
		for(int i = 0; i < 3; i++) {
			st = new StringTokenizer(br.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			xMap.put(x, (xMap.get(x) == null) ? 1 : xMap.get(x) + 1);
			yMap.put(y, (yMap.get(y) == null) ? 1 : yMap.get(y) + 1);
		}
		
		StringBuilder sb = new StringBuilder();
		
		for(int key : xMap.keySet()) {
			if(xMap.get(key).equals(1)) {
				sb.append(key + " ");
				break;
			}
		}
		for(int key : yMap.keySet()) {
			if(yMap.get(key).equals(1)) {
				sb.append(key);
				break;
			}
		}
		
		System.out.println(sb);
	}

}
