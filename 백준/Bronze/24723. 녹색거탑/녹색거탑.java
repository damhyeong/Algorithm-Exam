
import java.util.*;
import java.io.*;

/**
녹색거탑의 정상에서는 매년 NAVER가 개최하는 개발자 컨퍼런스 DEVIEW가 열린다.
 이 DEVIEW에 참여하면, 코딩에 깊은 깨달음을 얻어 코딩괴물이 될 수 있다고 전해진다. 
 그리고 코딩괴물은 녹색거탑의 정상에서 내려온다. 예전부터 전해 내려오는 D2 비전서에 의하면, 
 코딩괴물이 녹색거탑의 정상에서 내려오는 경우의 수를 파악한 사람은, 개발자 컨퍼런스 DEVIEW에 참여할 수 있다 한다. 
 그리고 DEVIEW에 참여해 본인도 코딩괴물이 될 수 있다!

녹색거탑은 위 그림과 같이 규칙적으로 쌓여있다.

그림의 시야에 보이지 않는 블록은 없다.
그림의 시야에 보이는 블록의 윗면만 이용해 녹색거탑을 내려올 수 있다.
녹색거탑이 
$N$층이면, 총 
$N$개의 블록을 이용한 최단 경로로만 내려온다.
녹색거탑을 내려올 때는 정상에서 시작해 노란색 바닥까지, 항상 인접한 아래층의 블록으로만 내려온다.
녹색거탑을 정복하고 DEVIEW에 참여하자.

입력
녹색거탑의 높이를 나타내는 정수 
$N$이 주어진다. (
$1 \leq N \leq 5$)

출력
녹색거탑의 정상에서 바닥으로 내려오는 경우의 수를 출력한다.

예제 입력 1 
1
예제 출력 1 
2


 
$1$층짜리 녹색거탑을 내려오는 경우의 수는 위와 같이 
$2$가지다.

예제 입력 2 
2
예제 출력 2 
4


 
$2$층짜리 녹색거탑을 내려오는 경우의 수는 위와 같이 
$4$가지다.
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		
		int result = 1;
		for(int i = 0; i < N; i++)
			result *= 2;
		
		bw.write(Integer.toString(result));
		bw.flush();
		bw.close();
		br.close();
		
	}

}
