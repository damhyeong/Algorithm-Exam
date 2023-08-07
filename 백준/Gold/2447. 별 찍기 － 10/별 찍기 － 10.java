
import java.util.*;
import java.io.*;

/**
별 찍기 - 10
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	68234	37345	27878	54.631%
문제
재귀적인 패턴으로 별을 찍어 보자. N이 3의 거듭제곱(3, 9, 27, ...)이라고 할 때, 크기 N의 패턴은 N×N 정사각형 모양이다.

크기 3의 패턴은 가운데에 공백이 있고, 가운데를 제외한 모든 칸에 별이 하나씩 있는 패턴이다.

***
* *
***
N이 3보다 클 경우, 크기 N의 패턴은 공백으로 채워진 가운데의 (N/3)×(N/3) 정사각형을 크기 N/3의 패턴으로 둘러싼 형태이다. 
예를 들어 크기 27의 패턴은 예제 출력 1과 같다.

입력
첫째 줄에 N이 주어진다. N은 3의 거듭제곱이다. 
즉 어떤 정수 k에 대해 N=3k이며, 이때 1 ≤ k < 8이다.

출력
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

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		char[][] startChar = new char[1][1];
		startChar[0][0] = '*';
		char[][] result = drawStart(N, 3, startChar);
		
		for(int i = 0; i < result[0].length; i++) {
			bw.write(new String(result[i]) + "\n");
			bw.flush();
		}
		bw.close();
		br.close();
	}
	
	public static char[][] drawStart(int N, int n, char[][] preChar){
		char[][] stars = new char[n][n];
		int emptyIndex = n / 2;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(i == 1 && j == 1) {
					int iIndex = i * n / 3;
					int jIndex = j * n / 3;
					for(int x = 0; x < preChar.length; x++) {
						for(int y = 0; y < preChar.length; y++) {
							stars[iIndex + x][jIndex + y] = ' ';
						}
					}
					
				} else {
					int iIndex = i * n / 3;
					int jIndex = j * n / 3;
					for(int x = 0; x < preChar.length; x++) {
						for(int y = 0; y < preChar.length; y++) {
							stars[iIndex + x][jIndex + y] = preChar[x][y];
						}
					}
				}
			}
		}
		
		if(n != N) {
			return drawStart(N, n * 3, stars);
		} else
			return stars;
	}
}
