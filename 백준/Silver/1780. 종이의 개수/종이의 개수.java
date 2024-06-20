import java.util.*;
import java.io.*;

/**
종이의 개수

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	256 MB	46638	28253	21188	59.723%

문제
---
N×N크기의 행렬로 표현되는 종이가 있다. 

종이의 각 칸에는 -1, 0, 1 중 하나가 저장되어 있다. 

우리는 이 행렬을 다음과 같은 규칙에 따라 적절한 크기로 자르려고 한다.


만약 종이가 모두 같은 수로 되어 있다면 이 종이를 그대로 사용한다.

(1)이 아닌 경우에는 종이를 같은 크기의 종이 9개로 자르고, 각각의 잘린 종이에 대해서 (1)의 과정을 반복한다.

이와 같이 종이를 잘랐을 때, -1로만 채워진 종이의 개수, 0으로만 채워진 종이의 개수, 1로만 채워진 종이의 개수를 구해내는 프로그램을 작성하시오.

입력
---
첫째 줄에 N(1 ≤ N ≤ 3^7, N은 3^k 꼴)이 주어진다. 

다음 N개의 줄에는 N개의 정수로 행렬이 주어진다.

출력
---
첫째 줄에 -1로만 채워진 종이의 개수를, 
둘째 줄에 0으로만 채워진 종이의 개수를, 
셋째 줄에 1로만 채워진 종이의 개수를 출력한다.

예제 입력 1 
9
0 0 0 1 1 1 -1 -1 -1
0 0 0 1 1 1 -1 -1 -1
0 0 0 1 1 1 -1 -1 -1
1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0
0 1 -1 0 1 -1 0 1 -1
0 -1 1 0 1 -1 0 1 -1
0 1 -1 1 0 -1 0 1 -1
예제 출력 1 
10
12
11
 */

public class Main {
	public static int cnt1 = 0;
	public static int cnt2 = 0;
	public static int cnt3 = 0;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		int[][] numbers = new int[N][N];
		
		for(int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for(int j = 0; j < N; j++) {
				numbers[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		countEachNumbers(numbers, 0, 0, numbers.length);
		
		System.out.println(cnt1);
		System.out.println(cnt2);
		System.out.println(cnt3);
	}
	
	public static void countEachNumbers(int[][] numbers, int sY, int sX, int size) {
		
		if(size == 1 || isSame(numbers, sY, sX, size)) {
			int num = getNum(numbers, sY, sX);
			
			if(num == -1)
				cnt1++;
			else if(num == 0)
				cnt2++;
			else
				cnt3++;
			
			return;
		}
		
		for(int i = 0; i < 3; i++) {
			int startY = sY + (size / 3) * i;
			for(int j = 0; j < 3; j++) {
				int startX = sX + (size / 3) * j;
				countEachNumbers(numbers, startY, startX, size / 3);
			}
		}
	}
	
	public static boolean isSame(int[][] numbers, int sY, int sX, int size) {
		int compareNum = numbers[sY][sX];
		boolean isSame = true;
		
		for(int i = sY; i < sY + size; i++) {
			for(int j = sX; j < sX + size; j++) {
				if(numbers[i][j] != compareNum) {
					isSame = false;
					break;
				}
			}
		}
		
		return isSame;
	}
	
	public static int getNum(int[][] numbers, int i, int j) {
		return numbers[i][j];
	}
}
