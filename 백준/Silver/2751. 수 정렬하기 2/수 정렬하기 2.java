import java.util.*;
import java.io.*;

/**
수 정렬하기 2

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	256 MB	318165	96783	67655	31.183%

문제
N개의 수가 주어졌을 때, 이를 오름차순으로 정렬하는 프로그램을 작성하시오.

입력
첫째 줄에 수의 개수 N(1 ≤ N ≤ 1,000,000)이 주어진다. 

둘째 줄부터 N개의 줄에는 수가 주어진다. 

이 수는 절댓값이 1,000,000보다 작거나 같은 정수이다. 

수는 중복되지 않는다.

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
	public static int[] arr;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		
		arr = new int[N];
		
		for(int i = 0; i < N; i++)
			arr[i] = Integer.parseInt(br.readLine());
		
		// 여러 방식으로 정렬하기 
		// quickSort(0, arr.length - 1);
		// mergeSort(arr);
		heapSort();
		
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < arr.length; i++)
			sb.append(arr[i] + "\n");
		
		System.out.println(sb.toString());
	}
	
	public static void quickSort(int start, int end) {
		if(end - start <= 0)
			return;
		
		int pivot  = start;
		int i = start;
		int j = end;
		
		while(i < j) {
			while(arr[pivot] < arr[j]) {
				j--;
			}
			while(i < j && arr[pivot] >= arr[i]) {
				i++;
			}
			
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		
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
		
		int i = 0, j = 0, index = 0;
		
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
	
	public static void heapSort() {
		int len = arr.length;
		
		for(int i = len / 2 - 1; i >= 0; i--) 
			heapify(len, i);
		
		for(int i = len - 1; i > 0; i--) {
			int temp = arr[0];
			arr[0] = arr[i];
			arr[i] = temp;
			
			heapify(i, 0);
		}
		
	}
	public static void heapify(int end, int index) {
		int parent = index;
		int left = index * 2 + 1;
		int right = index * 2 + 2;
		
		if(left < end && arr[parent] < arr[left])
			parent = left;
		
		if(right < end && arr[parent] < arr[right])
			parent = right;
		
		if(parent != index) {
			int temp = arr[parent];
			arr[parent] = arr[index];
			arr[index] = temp;
			
			heapify(end, parent);
		}
	}
}
