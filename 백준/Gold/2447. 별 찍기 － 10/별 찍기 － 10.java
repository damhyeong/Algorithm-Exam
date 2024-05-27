import java.util.*;
import java.io.*;

/**
별 찍기 - 10

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	75783	42166	31430	55.477%

문제
---
재귀적인 패턴으로 별을 찍어 보자. 

N이 3의 거듭제곱(3, 9, 27, ...)이라고 할 때, 크기 N의 패턴은 N×N 정사각형 모양이다.

크기 3의 패턴은 가운데에 공백이 있고, 가운데를 제외한 모든 칸에 별이 하나씩 있는 패턴이다.

***
* *
***
*
N이 3보다 클 경우, 크기 N의 패턴은 공백으로 채워진 가운데의 (N/3)×(N/3) 정사각형을 크기 N/3의 패턴으로 둘러싼 형태이다. 

예를 들어 크기 27의 패턴은 예제 출력 1과 같다.

입력
---
첫째 줄에 N이 주어진다. 

N은 3의 거듭제곱이다. 

즉 어떤 정수 k에 대해 N=3k이며, 이때 1 ≤ k < 8이다.

출력
---
첫째 줄부터 N번째 줄까지 별을 출력한다.

예제 입력 1 
27
예제 출력 1 
***************************
* ** ** ** ** ** ** ** ** *
***************************
***   ******   ******   ***
* *   * ** *   * ** *   * *
***   ******   ******   ***
***************************
* ** ** ** ** ** ** ** ** *
***************************
*********         *********
* ** ** *         * ** ** *
*********         *********
***   ***         ***   ***
* *   * *         * *   * *
***   ***         ***   ***
*********         *********
* ** ** *         * ** ** *
*********         *********
***************************
* ** ** ** ** ** ** ** ** *
***************************
***   ******   ******   ***
* *   * ** *   * ** *   * *
***   ******   ******   ***
***************************
* ** ** ** ** ** ** ** ** *
***************************
 */

public class Main {
	public static char[][] stars;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		stars = new char[N][N];
		pickStar(N, 0, 0, true);
		
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < stars.length; i++) {
			sb.append(new String(stars[i])).append("\n");
		}
		
		System.out.println(sb.toString());
	}
	
	public static void pickStar(int N, int x, int y, boolean isLight) {
		if(!isLight) {
			for(int i = x; i < x + N; i++) {
				for(int j = y; j < y + N; j++) {
					stars[i][j] = ' ';
				}
			}
		} else {
			if(N == 1) {
				stars[x][y] = '*';
			} else {
				int divThr = N / 3;
				pickStar(divThr, x, y, true);
				pickStar(divThr, x + divThr, y, true);
				pickStar(divThr, x + divThr * 2, y, true);
				
				pickStar(divThr, x, y + divThr, true);
				pickStar(divThr, x + divThr, y + divThr, false);
				pickStar(divThr, x + divThr * 2, y + divThr, true);
				
				pickStar(divThr, x, y + divThr * 2, true);
				pickStar(divThr, x + divThr, y + divThr * 2, true);
				pickStar(divThr, x + divThr * 2, y + divThr * 2, true);
			}
		}
	}
}
