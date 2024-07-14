import java.util.*;
import java.io.*;

/**
수 찾기

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	274082	85921	56856	30.217%

문제
---
N개의 정수 A[1], A[2], …, A[N]이 주어져 있을 때, 
이 안에 X라는 정수가 존재하는지 알아내는 프로그램을 작성하시오.

입력
---
첫째 줄에 자연수 N(1 ≤ N ≤ 100,000)이 주어진다. 

다음 줄에는 N개의 정수 A[1], A[2], …, A[N]이 주어진다. 

다음 줄에는 M(1 ≤ M ≤ 100,000)이 주어진다. 

다음 줄에는 M개의 수들이 주어지는데, 이 수들이 A안에 존재하는지 알아내면 된다. 

모든 정수의 범위는 -2^31 보다 크거나 같고 2^31보다 작다.


출력
---
M개의 줄에 답을 출력한다. 존재하면 1을, 존재하지 않으면 0을 출력한다.


예제 입력 1 
5
4 1 5 2 3
5
1 3 7 9 5
예제 출력 1 
1
1
0
0
1
 */

/*
 * 1. 정렬 후 이분탐색
 * 2. 해시맵 제작 후 찾기
 * 
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		int[] arr = new int[N];
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		for(int i = 0; i < N; i++) 
			arr[i] = Integer.parseInt(st.nextToken());
		
		// ------------------------------------------------------------------------------------------------------------
		// QuickSort - 2932ms, 46820KB
		// quickSort(arr, 0, arr.length - 1);
		
		
		
		// ------------------------------------------------------------------------------------------------------------
		// mergeSort - 728ms, 58736KB
		// mergeSort(arr);
		
		
		// ------------------------------------------------------------------------------------------------------------
		// heapSort
		heapSort(arr);
		
		
		// ------------------------------------------------------------------------------------------------------------
		// dualPivotQuickSort
		// dualPivotQuickSort(arr, 0, arr.length - 1);
		
		
		
		int M = Integer.parseInt(br.readLine());
		
		StringBuilder sb = new StringBuilder();
		
		st = new StringTokenizer(br.readLine());
		for(int i = 0; i < M; i++) {
			if(binarySearch(arr, 0, arr.length - 1, Integer.parseInt(st.nextToken()))) {
				sb.append("1").append("\n");
			} else {
				sb.append("0").append("\n");
			}
		}
		
		System.out.println(sb.toString());
	}
	
	public static void quickSort(int[] arr, int start, int end) {
		if(start >= end)
			return;
		
		int pivot = start;
		int left = start;
		int right = end;
		
		while(left < right) {
			while( arr[pivot] < arr[right] )
				right--;
			while((left < right) && (arr[pivot] >= arr[left]) )
				left++;
			
			swap(arr, left, right);
		}
		swap(arr, pivot, left);
		
		quickSort(arr, start, left - 1);
		quickSort(arr, left + 1, end);
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
	public static void heapSort(int[] arr) {
		int len = arr.length;
		
		for(int i = len / 2 - 1; i >= 0; i--)
			heapify(arr, len, i);
		
		for(int i = arr.length - 1; i > 0; i--) {
			swap(arr, 0, i);
			heapify(arr, i, 0);
		}
	}
	public static void heapify(int[] arr, int end, int index) {
		int parent = index;
		int left = index * 2 + 1;
		int right = index * 2 + 2;
		
		if(left < end && arr[parent] < arr[left])
			parent = left;
		if(right < end && arr[parent] < arr[right])
			parent = right;
		
		if(parent != index) {
			swap(arr, parent, index);
			heapify(arr, end, parent);
		}
	}
	public static void dualPivotQuickSort(int[] arr, int low, int high) {
		
	}
	
	public static void swap(int[] arr, int i, int j) {
		int temp = arr[i];
		
		arr[i] = arr[j];
		
		arr[j] = temp;
		
		return;
	}
	
	public static boolean binarySearch(int[] arr, int i, int j, int num) {
		int mIndex = (i + j) / 2;
		
		if(i > j)
			return false;
		
		if(arr[mIndex] == num) {
			return true;
		} else if(arr[mIndex] > num){
			return binarySearch(arr, i, mIndex - 1, num);
		} else {
			return binarySearch(arr, mIndex + 1, j, num);
		}
	}
}

class HashMap1{
	
}
