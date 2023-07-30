
import java.util.*;
import java.io.*;

/**
문제
2차원 평면 위의 점 N개가 주어진다. 
좌표를 x좌표가 증가하는 순으로, x좌표가 같으면 y좌표가 증가하는 순서로 정렬한 다음 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 점의 개수 N (1 ≤ N ≤ 100,000)이 주어진다. 
둘째 줄부터 N개의 줄에는 i번점의 위치 xi와 yi가 주어진다. 
(-100,000 ≤ xi, yi ≤ 100,000) 좌표는 항상 정수이고, 위치가 같은 두 점은 없다.

출력
첫째 줄부터 N개의 줄에 점을 정렬한 결과를 출력한다.

예제 입력 1 
5
3 4
1 1
1 -1
2 2
3 3
예제 출력 1 
1 -1
1 1
2 2
3 3
3 4
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		
		Matrix[] matrix = new Matrix[N];
		
		StringTokenizer st;
		
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
	
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			
			Matrix m = new Matrix(x, y);
			matrix[i] = m;
		}
		
		Arrays.sort(matrix);
		
		for(int i = 0; i < N; i++) {
			bw.write(matrix[i] + "\n");
		}
		bw.flush();
		bw.close();
		br.close();
	}
}


class Matrix implements Comparable {
	public int x = 0;
	public int y = 0;
	
	public Matrix(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	@Override
	public int compareTo(Object o) {
		Matrix m = (Matrix) o;
		
		if(this.x > m.x)
			return 1;
		else if(this.x < m.x)
			return -1;
		else {
			if(this.y > m.y)
				return 1;
			else
				return -1;
		}
	}
	
	public String toString() {
		return this.x + " " + this.y;
	}
	
}
