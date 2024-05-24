import java.util.*;
import java.io.*;

/**
통계학

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	256 MB	167193	41024	32837	26.532%

문제
---
수를 처리하는 것은 통계학에서 상당히 중요한 일이다. 

통계학에서 N개의 수를 대표하는 기본 통계값에는 다음과 같은 것들이 있다. 

단, N은 홀수라고 가정하자.

-----
산술평균 : N개의 수들의 합을 N으로 나눈 값
중앙값 : N개의 수들을 증가하는 순서로 나열했을 경우 그 중앙에 위치하는 값
최빈값 : N개의 수들 중 가장 많이 나타나는 값
범위 : N개의 수들 중 최댓값과 최솟값의 차이
N개의 수가 주어졌을 때, 네 가지 기본 통계값을 구하는 프로그램을 작성하시오.
-------


입력
---
첫째 줄에 수의 개수 N(1 ≤ N ≤ 500,000)이 주어진다. 

단, N은 홀수이다. 

그 다음 N개의 줄에는 정수들이 주어진다. 

입력되는 정수의 절댓값은 4,000을 넘지 않는다.

출력
---
첫째 줄에는 산술평균을 출력한다. 소수점 이하 첫째 자리에서 반올림한 값을 출력한다.

둘째 줄에는 중앙값을 출력한다.

셋째 줄에는 최빈값을 출력한다. 여러 개 있을 때에는 최빈값 중 두 번째로 작은 값을 출력한다.

넷째 줄에는 범위를 출력한다.

예제 입력 1 
5
1
3
8
-2
2
예제 출력 1 
2
2
1
10
예제 입력 2 
1
4000
예제 출력 2 
4000
4000
4000
0
예제 입력 3 
5
-1
-2
-3
-1
-2
예제 출력 3 
-2
-2
-1
2
예제 입력 4 
3
0
0
-1
예제 출력 4 
0
0
0
1
(0 + 0 + (-1)) / 3 = -0.333333... 이고 이를 첫째 자리에서 반올림하면 0이다. -0으로 출력하면 안된다.
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		int[] arr = new int[N];
		double sum = 0;
		int min = Integer.MAX_VALUE;
		int max = Integer.MIN_VALUE;
		for(int i = 0; i < N; i++) {
			int newNum = Integer.parseInt(br.readLine());
			arr[i] = newNum;
			sum += arr[i];
			min = min > newNum ? newNum : min;
			max = max < newNum ? newNum : max;
		}
		
		int result1 = (int)Math.round((double)(sum / (double)N));
		
		// quickSort
		// quickSort(arr, 0, arr.length - 1);
		
		// mergeSort
		// mergeSort(arr);
		
		// heapSort
		heapSort(arr);
		
		// dualPivotQuickSort
		// dualPivotQuickSort(arr, 0, arr.length - 1);
		
		int result2 = arr[N / 2];
		
		
		List<Node4> list = new ArrayList<>();
		
		Node4 tempNode = new Node4(arr[0]);
		list.add(tempNode);
		
		int maxCnt = -1;
		for(int i = 1; i < arr.length; i++) {
			if(tempNode.val == arr[i])
				tempNode.increase();
			else {
				int newCnt = tempNode.getCount();
				maxCnt = maxCnt < newCnt ? newCnt : maxCnt;
				
				tempNode = new Node4(arr[i]);
				list.add(tempNode);
			}
		}
		int newCnt = tempNode.getCount();
		maxCnt = maxCnt < newCnt ? newCnt : maxCnt;
		
		List<Node4> maxList = new ArrayList<>();
		
		for(int i = 0; i < list.size(); i++) {
			Node4 node = list.get(i);
			if(node.getCount() == maxCnt)
				maxList.add(node);
		}
		
		Collections.sort(maxList);
		
		int result3 = 0;
		
		if(maxList.size() >= 2)
			result3 = maxList.get(1).val;
		else
			result3 = maxList.get(0).val;
		
		
		int result4 = max - min;
		
		StringBuilder sb = new StringBuilder();
		sb.append(result1).append("\n");
		sb.append(result2).append("\n");
		sb.append(result3).append("\n");
		sb.append(result4).append("\n");
		
		System.out.println(sb.toString());
	}
	
	public static void dualPivotQuickSort(int[] arr, int low, int high) {
		if(low >= high)
			return;
		
		if(arr[low] > arr[high])
			swap(arr, low, high);
		
		int leftPivotIdx = low + 1;
		int rightPivotIdx = high - 1;
		
		int iter = leftPivotIdx;
		
		while(iter <= rightPivotIdx) {
			if(arr[iter] < arr[low])
				swap(arr, iter++, leftPivotIdx++);
			else if(arr[iter] > arr[high])
				swap(arr, iter, rightPivotIdx--);
			else
				iter++;
		}
		
		swap(arr, low, --leftPivotIdx);
		swap(arr, high, ++rightPivotIdx);
		
		dualPivotQuickSort(arr, low, leftPivotIdx - 1);
		dualPivotQuickSort(arr, leftPivotIdx + 1, rightPivotIdx - 1);
		dualPivotQuickSort(arr, rightPivotIdx + 1, high);
	}
	
	public static void heapSort(int[] arr) {
		int len = arr.length;
		
		for(int i = len * 2 - 1; i >= 0; i--)
			heapify(arr, len, i);
		
		for(int i = len - 1; i > 0; i--) {
			swap(arr, 0, i);
			heapify(arr, i, 0);
		}
	}
	private static void heapify(int[] arr, int end, int i) {
		int parent = i;
		int left = i * 2 + 1;
		int right = i * 2 + 2;
		
		if(left < end && arr[parent] < arr[left])
			parent = left;
		
		if(right < end && arr[parent] < arr[right])
			parent = right;
		
		if(parent != i) {
			swap(arr, parent, i);
			heapify(arr, end, parent);
		}
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
	
	public static void quickSort(int[] arr, int start, int end) {
		if(start >= end)
			return;
		
		int pivot = start;
		int i = start;
		int j = end;
		
		while(i < j) {
			while(arr[pivot] < arr[j])
				j--;
			while(i < j && arr[pivot] >= arr[i])
				i++;
			
			swap(arr, i, j);
		}
		
		swap(arr, pivot, i);
		
		quickSort(arr, start, i - 1);
		quickSort(arr, i + 1, end);
	}
	
	public static void swap(int[] arr, int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
}

class Node4 implements Comparable<Node4>{
	int val;
	int count;
	
	public Node4() {
		
	}
	public Node4(int val) {
		this.val = val;
		this.count = 1;
	}
	public void increase() {
		this.count++;
	}
	
	public int getCount() {
		return this.count;
	}
	
	
	
	@Override
	public int compareTo(Node4 o) {
		// TODO Auto-generated method stub
		Node4 node = (Node4) o;
		return this.val - node.val;
	}
}
