
import java.util.*;
import java.io.*;

/**
문제
N개의 수가 주어졌을 때, 이를 오름차순으로 정렬하는 프로그램을 작성하시오.

입력
첫째 줄에 수의 개수 N(1 ≤ N ≤ 1,000,000)이 주어진다. 둘째 줄부터 N개의 줄에는 수가 주어진다. 이 수는 절댓값이 1,000,000보다 작거나 같은 정수이다. 수는 중복되지 않는다.

출력
첫째 줄부터 N개의 줄에 오름차순으로 정렬한 결과를 한 줄에 하나씩 출력한다.

예제 입력 1 
5
5
4
3
2
1
예제 출력 1 
1
2
3
4
5
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		
		int[] arr = new int[N];
		
		for(int i = 0; i < N; i++) {
			arr[i] = Integer.parseInt(br.readLine());
		}
		
		Arrays.sort(arr);
		
		for(int i = 0; i < arr.length; i++) {
			bw.write(arr[i] + "\n");
		}
		
		/*
		for(int i = 0; i < N - 1; i++) {
			int minIndex = i;
			for(int j = i + 1; j < N; j++) {
				if(arr[minIndex] >= arr[j])
					minIndex = j;
			}
			if(i != minIndex) {
				int temp = arr[i];
				arr[i] = arr[minIndex];
				arr[minIndex] = temp;
			}
			bw.write(arr[i] + "\n");
			bw.flush();
		}
		bw.write(Integer.toString(arr[N - 1]));
		*/
		bw.flush();
		
		bw.close();
		br.close();
	}

}
