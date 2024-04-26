import java.util.*;
import java.io.*;

/**
커트라인

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	1024 MB	35804	23407	21409	66.210%

문제
2022 연세대학교 미래캠퍼스 슬기로운 코딩생활에 N 명의 학생들이 응시했다.

이들 중 점수가 가장 높은 k 명은 상을 받을 것이다. 

이 때, 상을 받는 커트라인이 몇 점인지 구하라.

커트라인이란 상을 받는 사람들 중 점수가 가장 가장 낮은 사람의 점수를 말한다.

입력
첫째 줄에는 응시자의 수 
N과 상을 받는 사람의 수 
k가 공백을 사이에 두고 주어진다.

둘째 줄에는 각 학생의 점수 
x가 공백을 사이에 두고 주어진다.

출력
상을 받는 커트라인을 출력하라.

제한

* 1 <= N <= 1_000
* 1 <= k <= N
* 0 <= x <= 10_000 


예제 입력 1 
5 2
100 76 85 93 98
예제 출력 1 
98

힌트
---
시험 응시자들 가운데 1등은 100점, 2등은 98점, 3등은 93점이다. 2등까지 상을 받으므로 커트라인은 98점이다.
 */

public class Main {
	public static int[] arr;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int len = Integer.parseInt(st.nextToken()); // 사람의 수 
		int cut = Integer.parseInt(st.nextToken()); // 커트라인 - 상 받는 사람 수 
		
		arr = new int[len];
		
		st = new StringTokenizer(br.readLine());
		
		for(int i = 0; i < arr.length; i++)
			arr[i] = Integer.parseInt(st.nextToken());
		
		// quickSort(0, arr.length - 1);
		// mergeSort(arr);
		heapSort();
		
		
		StringBuilder sb = new StringBuilder();
		
		int count = 0;
		for(int i = arr.length - 1; i >= 0; i--) {
			count++;
			if(count == cut) {
				sb.append(arr[i]);
				break;
			}
		}
		System.out.println(sb.toString());
	}
	
	public static void quickSort(int start, int end) {
		if(end - start <= 0)
			return;
		
		int pivot = start;
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
		
		int temp = arr[i];
		arr[i] = arr[pivot];
		arr[pivot] = temp;
		
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
		
		while(i < LArr.length) {
			arr[index++] = LArr[i++];
		}
		
		while(j < RArr.length) {
			arr[index++] = RArr[j++];
		}
	}
	
	public static void heapSort() {
		int len = arr.length; 
		
		for(int i = len / 2 - 1; i >= 0; i--) {
			heapify(len, i);
		}
		
		for(int i = len - 1; i > 0; i--) {
			int temp = arr[0];
			arr[0] = arr[i];
			arr[i] = temp;
			
			heapify(i, 0);
		}
	}
	public static void heapify(int end, int i) {
		int parent = i;
		int left = i * 2 + 1;
		int right = i * 2 + 2;
		
		if(left < end && arr[parent] < arr[left])
			parent = left;
		if(right < end && arr[parent] < arr[right])
			parent = right;
		
		if(parent != i) {
			int temp = arr[parent];
			arr[parent] = arr[i];
			arr[i] = temp;
			
			heapify(end, parent);
		}
			
		
	}
}
