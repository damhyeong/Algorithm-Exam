
import java.util.*;
import java.io.*;

/**
로봇 청소기
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	512 MB	55750	30296	20475	53.761%
문제
로봇 청소기와 방의 상태가 주어졌을 때, 청소하는 영역의 개수를 구하는 프로그램을 작성하시오.

로봇 청소기가 있는 방은 
N x M 크기의 직사각형으로 나타낼 수 있으며, 
1 x 1 크기의 정사각형 칸으로 나누어져 있다. 
각각의 칸은 벽 또는 빈 칸이다.
청소기는 바라보는 방향이 있으며, 이 방향은 동, 서, 남, 북 중 하나이다. 
방의 각 칸은 좌표 (r, c)로 나타낼 수 있고, 
가장 북쪽 줄의 가장 서쪽 칸의 좌표가 (0, 0), 
가장 남쪽 줄의 가장 동쪽 칸의 좌표가 (N-1, M-1)이다. 
즉, 좌표 (r, c)는 북쪽에서 (r+1)번째에 있는 줄의 서쪽에서 (c+1)번째 칸을 가리킨다. 
처음에 빈 칸은 전부 청소되지 않은 상태이다.

로봇 청소기는 다음과 같이 작동한다.

1. 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다.

2. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우,
1. 바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
2. 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다.

3. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 있는 경우,
1. 반시계 방향으로 90도 회전한다.
2. 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다.
3. 1번으로 돌아간다.

입력
첫째 줄에 방의 크기 N과 M이 입력된다. 
(3 <= N, M <= 50)  

둘째 줄에 처음에 로봇 청소기가 있는 칸의 좌표 (r, c)와 처음에 로봇 청소기가 바라보는 방향 d가 입력된다. 
d가 0인 경우 북쪽, 1인 경우 동쪽, 2인 경우 남쪽, 3인 경우 서쪽을 바라보고 있는 것이다.

셋째 줄부터 N개의 줄에 각 장소의 상태를 나타내는 N x M개의 값이 한 줄에 M개씩 입력된다. 
i번째 줄의 j번째 값은 칸 (i, j)의 상태를 나타내며, 이 값이 
0인 경우 (i, j)가 청소되지 않은 빈 칸이고, 
1인 경우 (i, j)에 벽이 있는 것이다. 
방의 가장 북쪽, 가장 남쪽, 가장 서쪽, 가장 동쪽 줄 중 하나 이상에 위치한 모든 칸에는 벽이 있다. 
로봇 청소기가 있는 칸은 항상 빈 칸이다.

출력
로봇 청소기가 작동을 시작한 후 작동을 멈출 때까지 청소하는 칸의 개수를 출력한다.

예제 입력 1 
3 3
1 1 0
1 1 1
1 0 1
1 1 1
예제 출력 1 
1
예제 입력 2 
11 10
7 4 0
1 1 1 1 1 1 1 1 1 1
1 0 0 0 0 0 0 0 0 1
1 0 0 0 1 1 1 1 0 1
1 0 0 1 1 0 0 0 0 1
1 0 1 1 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 1 0 1
1 0 0 0 0 0 1 1 0 1
1 0 0 0 0 0 1 1 0 1
1 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1
예제 출력 2 
57
 */

public class Main {
	public static int[][] room;
	public static int r;
	public static int c;
	public static int d;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken()); int M = Integer.parseInt(st.nextToken());
		room = new int[N][M];
		
		st = new StringTokenizer(br.readLine());
		r = Integer.parseInt(st.nextToken()); // 현재 줄 
		c = Integer.parseInt(st.nextToken()); // 현재 행 
		d = Integer.parseInt(st.nextToken()); // 현재 방향 
		
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < M; j++) {
				// 1일 경우 벽, 0일 경우 청소안한 구역
				room[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		/*
		1. 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다.

		2. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우,
		1. 바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
		2. 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다.
		
		3. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 있는 경우,
		1. 반시계 방향으로 90도 회전한다.
		2. 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다.
		3. 1번으로 돌아간다.
		 */
		int cnt = 0;
		while(true) {
			//현재 칸이 청소되지 않은 경우, 청소한다. 
			if(room[r][c] == 0) {
				// 2는 청소 한 구역으로 하자. 
				room[r][c] = 2;
				cnt++;
			}
			
			if(!isTrashAround()) { // 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우
				// 바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한칸 후진하고 1번으로 돌아간다. 
				if(!isBehindWall()) {
					move(false);
					continue;
				}else // 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다. 
					break;
			} else { // 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 있는 경우 
				// 반시계 방향이므로 음수가 되는 즉시 바로 3으로 변경. 아니라면 그냥 d - 1. 
				d = d - 1 < 0 ? 3 : d - 1;
				
				if(isTrashForward())
					move(true);
				else
					continue;
			}
		}
		bw.write(Integer.toString(cnt));
		bw.flush();
		bw.close();
	}
	public static boolean isTrashAround() {
		return (room[r - 1][c] == 0)
				|| (room[r + 1][c] == 0)
				|| (room[r][c - 1] == 0)
				|| (room[r][c + 1] == 0);
	}
	public static boolean isBehindWall() {
		if(d == 0)  // 북쪽 
			return room[r + 1][c] == 1 ? true : false;
		else if(d == 1)  // 동쪽 
			return room[r][c - 1] == 1 ? true : false;
		else if(d == 2)  // 남쪽 
			return room[r - 1][c] == 1 ? true : false;
		else  // 서쪽 
			return room[r][c + 1] == 1 ? true : false;
		
	}
	public static void move(boolean isForward) {
		if(d == 0) // 북쪽 
			r = isForward ? r - 1 : r + 1;
		else if(d == 1) // 동쪽 
			c = isForward ? c + 1 : c - 1;
		else if(d == 2) // 남쪽 
			r = isForward ? r + 1 : r - 1;
		else // 서쪽 
			c = isForward ? c - 1 : c + 1;
	}
	public static boolean isTrashForward() {
		if(d == 0)  // 북쪽 
			return room[r - 1][c] == 0 ? true : false;
		else if(d == 1)  // 동쪽 
			return room[r][c + 1] == 0 ? true : false;
		else if(d == 2)  // 남쪽 
			return room[r + 1][c] == 0 ? true : false;
		else  // 서쪽 
			return room[r][c - 1] == 0 ? true : false;
	}
}
