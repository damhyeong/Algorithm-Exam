
import java.util.*;
import java.io.*;

/**
문제
2022 연세대학교 미래캠퍼스 슬기로운 코딩생활에 
 N명의 학생들이 응시했다.

이들 중 점수가 가장 높은 
 k명은 상을 받을 것이다. 이 때, 상을 받는 커트라인이 몇 점인지 구하라.

커트라인이란 상을 받는 사람들 중 점수가 가장 가장 낮은 사람의 점수를 말한다.

입력
첫째 줄에는 응시자의 수 N과 
상을 받는 사람의 수 k가 공백을 사이에 두고 주어진다.

둘째 줄에는 각 학생의 점수 
x가 공백을 사이에 두고 주어진다.

출력
상을 받는 커트라인을 출력하라.

제한
1 <= N <= 1,000
1 <= k <= N
0 <= x <= 10,000

예제 입력 1 
5 2
100 76 85 93 98
예제 출력 1 
98
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken()); // 응시자의 수 
		int k = Integer.parseInt(st.nextToken()); // 상을 받는 사람의 수 
		
		int[] arr = new int[N];
		
		st = new StringTokenizer(br.readLine());
		
		for(int i = 0; i < N; i++) 
			arr[i] = Integer.parseInt(st.nextToken());
		
		for(int i = 0; i < N - 1; i++) {
			int maxIndex = i;
			for(int j = i + 1; j < N; j++) {
				if(arr[maxIndex] <= arr[j])
					maxIndex = j;
			}
			if(i != maxIndex) {
				int temp = arr[i];
				arr[i] = arr[maxIndex];
				arr[maxIndex] = temp;
			}
		}
		String str = Integer.toString(arr[k - 1]);
		bw.write(str);
		bw.flush();
		bw.close();
		br.close();
	}

}
