
import java.util.*;
import java.io.*;

/**
단지번호붙이기
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	165751	73484	46562	42.209%
문제
<그림 1>과 같이 정사각형 모양의 지도가 있다. 
1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다. 
철수는 이 지도를 가지고 연결된 집의 모임인 단지를 정의하고, 단지에 번호를 붙이려 한다. 
여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다. 
대각선상에 집이 있는 경우는 연결된 것이 아니다. 
<그림 2>는 <그림 1>을 단지별로 번호를 붙인 것이다. 
지도를 입력하여 단지수를 출력하고, 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.

입력
첫 번째 줄에는 지도의 크기 N(정사각형이므로 가로와 세로의 크기는 같으며 5≤N≤25)이 입력되고, 그 다음 N줄에는 각각 N개의 자료(0혹은 1)가 입력된다.

출력
첫 번째 줄에는 총 단지수를 출력하시오. 
그리고 각 단지내 집의 수를 오름차순으로 정렬하여 한 줄에 하나씩 출력하시오.

예제 입력 1 
7
0110100
0110101
1110101
0000111
0100000
0111110
0111000
예제 출력 1 
3
7
8
9
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		List<ArrayList<Integer>> list = new ArrayList<>();
		boolean[][] isVisited = new boolean[N + 1][N + 1];
		
		List<Integer> countHouse = new ArrayList<>();
		
		for(int i = 0; i <= N; i++)
			list.add(new ArrayList<Integer>());
		
		for(int i = 1; i <= N; i++) {
			String houses = br.readLine();
			for(int j = 1; j <= N; j++) {
				char ch = houses.charAt(j - 1);
				if(ch == '1')
					list.get(i).add(j);
			}
		}
		
		
		// bfs 방식으로 푸는게 공부에 좋을듯
		for(int i = 1; i <= N; i++) {
			List<Integer> rowList = list.get(i);
			
			if(!rowList.isEmpty()) {
				for(int j = 0; j < rowList.size(); j++) {
					int xNum = rowList.get(j);
					if(isVisited[i][xNum])
						continue;
					int count = 0;
					Queue<Map<Integer, Integer>> queue = new LinkedList<>();
					Map<Integer, Integer> map = new HashMap<Integer, Integer>();
					map.put(i, xNum);
					queue.add(map);
					isVisited[i][xNum] = true;
					
					count++;
					
					while(!queue.isEmpty()) {
						Map<Integer, Integer> pollMap = queue.poll();
						
						// map의 keySet을 가져오는데, 어짜피 1개이다. 
						// iterator 가져온 뒤 next() 시 바로 y인 key 추출. 
						int y = pollMap.keySet().iterator().next();
						int x = pollMap.get(y);
						
						//동, 남, 서, 북 순으로 Queue에 추가한다.
						if(x + 1 <= N && !isVisited[y][x + 1] && list.get(y).contains(x + 1)) { // 동쪽 추가 
							Map<Integer, Integer> m = new HashMap<Integer, Integer>();
							m.put(y, x + 1);
							queue.add(m);
							isVisited[y][x + 1] = true;
							count++;
						}
						if(y + 1 <= N && !isVisited[y + 1][x] && list.get(y + 1).contains(x)) { // 남쪽 추가 
							Map<Integer, Integer> m = new HashMap<Integer, Integer>();
							m.put(y + 1, x);
							queue.add(m);
							isVisited[y + 1][x] = true;
							count++;
						}
						if(x - 1 >= 1 && !isVisited[y][x - 1] && list.get(y).contains(x - 1)) { // 서쪽 추가 
							Map<Integer, Integer> m = new HashMap<Integer, Integer>();
							m.put(y, x - 1);
							queue.add(m);
							isVisited[y][x - 1] = true;
							count++;
						}
						if(y - 1 >= 1 && !isVisited[y - 1][x] && list.get(y - 1).contains(x)) { // 북쪽 추가 
							Map<Integer, Integer> m = new HashMap<Integer, Integer>();
							m.put(y - 1, x);
							queue.add(m);
							isVisited[y - 1][x] = true;
							count++;
						}
					}
					countHouse.add(count);
				}
			}
		}
		Collections.sort(countHouse);
		bw.write(Integer.toString(countHouse.size()) + "\n");
		for(int i = 0; i < countHouse.size(); i++)
			bw.write(Integer.toString(countHouse.get(i)) + "\n");
		bw.flush();
		bw.close();
	}

}
