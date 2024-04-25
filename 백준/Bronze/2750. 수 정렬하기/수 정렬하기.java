import java.util.*;
import java.io.*;

/**
수 정렬하기

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	205356	117553	80799	58.151%

문제
N개의 수가 주어졌을 때, 이를 오름차순으로 정렬하는 프로그램을 작성하시오.

입력
첫째 줄에 수의 개수 N(1 ≤ N ≤ 1,000)이 주어진다. 
둘째 줄부터 N개의 줄에는 수가 주어진다. 

이 수는 절댓값이 1,000보다 작거나 같은 정수이다. 수는 중복되지 않는다.

출력
첫째 줄부터 N개의 줄에 오름차순으로 정렬한 결과를 한 줄에 하나씩 출력한다.

예제 입력 1 
5
5
2
3
4
1
예제 출력 1 
1
2
3
4
5
 */

public class Main {
	public static int[] arr;
	public static int[] copyArr;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int len = Integer.parseInt(br.readLine());
		
		arr = new int[len];
		copyArr = new int[len]; // for merge sort.
		
		for(int i = 0; i < len; i++)
			arr[i] = Integer.parseInt(br.readLine());
		
		// selectionSort();
		// bubbleSort();
		// quickSort(0, arr.length - 1);
		mergeSort(arr);
		
		
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < arr.length; i++)
			sb.append(arr[i] + "\n");
		
		System.out.println(sb.toString());
	}
	
	public static void selectionSort() {
		for(int i = 0; i < arr.length; i++) {
			int minIndex = i;
			for(int j = i; j < arr.length; j++) 
				minIndex = (arr[minIndex] >= arr[j]) ? j : minIndex;
			
			int temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
		}
	}
	
	public static void bubbleSort() {
		
		for(;;) {
			boolean isBreak = true;
			
			for(int i = 1; i < arr.length; i++) {
				if(arr[i - 1] > arr[i]) {
					isBreak = false;
					int temp = arr[i - 1];
					arr[i - 1] = arr[i];
					arr[i] = temp;
				}
			}
			
			if(isBreak)
				break;
		}
	}
	
	public static void quickSort(int start, int end) {
		if(end - start <= 0)
			return;
		
		int pivot = start;
		int i = start; int j = end;
		
//		System.out.println("radix : " + pivot + ", i : " + i + ", j : " + j);
		
		while(i < j) {
			while(j >= start && arr[pivot] <= arr[j]) {
				j--;
			}
			j = (j < start) ? start : j;
			
			while(i < j && arr[pivot] >= arr[i]) {
				i++;
			}
			i = (i > end) ? end : i;
			
//			System.out.println("before swap -- i : " + i + ", j : " + j);
//			System.out.println("before swap -- arr[i] : " + arr[i] + ", arr[j] : " + arr[j]);
//			
			
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		
//		System.out.println("after loop -- i : " + i + ", j : " + j);
//		System.out.println("after loop -- arr[i] : " + arr[i] + ", arr[j] : " + arr[j]);
		
		int temp = arr[pivot];
		arr[pivot] = arr[i];
		arr[i] = temp;
		
		quickSort(start, i - 1); quickSort(i + 1, end);
	}
	
	public static void mergeSort(int[] arr) {
		if(arr.length <= 1)
			return;
		
		int middle = arr.length / 2;
		
		int[] LArr = new int[middle];
		int[] RArr = new int[arr.length - middle];
		
		int count = 0;
		for(int i = 0; i < LArr.length; i++)
			LArr[i] = arr[count++];
		for(int i = 0; i < RArr.length; i++)
			RArr[i] = arr[count++];
		
		mergeSort(LArr); mergeSort(RArr);
		
		int i = 0;
		int j = 0;
		int index = 0;
		
		while(i < LArr.length && j < RArr.length) {
			if(LArr[i] <= RArr[j]) 
				arr[index++] = LArr[i++];
			else
				arr[index++] = RArr[j++];
		}
		
		while(i < LArr.length)
			arr[index++] = LArr[i++];
		
		while(j < RArr.length)
			arr[index++] = RArr[j++];
	}
}
