import java.util.*;
import java.io.*;

/**
최댓값

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	316928	145934	120658	45.477%

문제
9개의 서로 다른 자연수가 주어질 때, 
이들 중 최댓값을 찾고 그 최댓값이 몇 번째 수인지를 구하는 프로그램을 작성하시오.

예를 들어, 서로 다른 9개의 자연수

3, 29, 38, 12, 57, 74, 40, 85, 61

이 주어지면, 이들 중 최댓값은 85이고, 이 값은 8번째 수이다.

입력
첫째 줄부터 아홉 번째 줄까지 한 줄에 하나의 자연수가 주어진다. 
주어지는 자연수는 100 보다 작다.

출력
첫째 줄에 최댓값을 출력하고, 둘째 줄에 최댓값이 몇 번째 수인지를 출력한다.

예제 입력 1 
3
29
38
12
57
74
40
85
61
예제 출력 1 
85
8
 */

public class Main {
	public static int[] array;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int[] numInts = new int[9];
		array = new int[9];
		
		for(int i = 0; i < 9; i++) {
			numInts[i] = Integer.parseInt(br.readLine());
			array[i] = numInts[i];
		}
		
		quickSort(0, array.length - 1);
		
		int maxValue = array[array.length - 1];
		
		StringBuilder sb = new StringBuilder();
		sb.append(maxValue + "\n");
		
		for(int i = 0; i < array.length; i++) {
			if(maxValue == numInts[i]) {
				sb.append(i + 1);
				break;
			}
		}
		System.out.println(sb.toString());
	}
	
	public static void quickSort(int lIdx, int rIdx) {
		// 길이가 1 이하면 비교 할 필요가 없다.
		if(rIdx - lIdx <= 0)
			return;
		
		int pivot = lIdx; // 왼쪽, 오른쪽 탐색 시 값의 비교를 위한 피봇 값.
		int i = lIdx, j = rIdx;
		int temp;
		
		while(i <= j) {
			
			while(i <= rIdx && array[pivot] >= array[i]) {
				i++;
			}
			
			while(array[pivot] < array[j]) {
				j--;
			}
			
			if(i < j) {
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			
			
		}
		
		temp = array[j];
		array[j] = array[pivot];
		array[pivot] = temp;
		
		// 위의 루프가 끝난다면, j가 새로운 재귀 함수의 기준이 된다. 
		quickSort(lIdx, j - 1);
		quickSort(j + 1, rIdx);
	}
}
