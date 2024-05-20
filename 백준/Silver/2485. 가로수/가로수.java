import java.util.*;
import java.io.*;

/**
가로수

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	23816	9684	7952	41.983%

문제
---
직선으로 되어있는 도로의 한 편에 가로수가 임의의 간격으로 심어져있다. 

KOI 시에서는 가로수들이 모두 같은 간격이 되도록 가로수를 추가로 심는 사업을 추진하고 있다. 

KOI 시에서는 예산문제로 가능한 한 가장 적은 수의 나무를 심고 싶다.

편의상 가로수의 위치는 기준점으로 부터 떨어져 있는 거리로 표현되며, 가로수의 위치는 모두 양의 정수이다.

예를 들어, 

가로수가 (1, 3, 7, 13)의 위치에 있다면 (5, 9, 11)의 위치에 가로수를 더 심으면 모든 가로수들의 간격이 같게 된다. 

또한, 가로수가 (2, 6, 12, 18)에 있다면 (4, 8, 10, 14, 16)에 가로수를 더 심어야 한다.

심어져 있는 가로수의 위치가 주어질 때, 모든 가로수가 같은 간격이 되도록 새로 심어야 하는 가로수의 최소수를 구하는 프로그램을 작성하라. 

단, 추가되는 나무는 기존의 나무들 사이에만 심을 수 있다.

입력
---
첫째 줄에는 이미 심어져 있는 가로수의 수를 나타내는 하나의 정수 N이 주어진다(3 ≤ N ≤ 100,000). 

둘째 줄부터 N개의 줄에는 각 줄마다 심어져 있는 가로수의 위치가 양의 정수로 주어지며, 
가로수의 위치를 나타내는 정수는 1,000,000,000 이하이다. 

가로수의 위치를 나타내는 정수는 모두 다르고, 
N개의 가로수는 기준점으로부터 떨어진 거리가 가까운 순서대로 주어진다.

출력
---
모든 가로수가 같은 간격이 되도록 새로 심어야 하는 가로수의 최소수를 첫 번째 줄에 출력한다.

예제 입력 1 
4
1
3
7
13
예제 출력 1 
3
예제 입력 2 
4
2
6
12
18
예제 출력 2 
5
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		int[] trees = new int[T];
		
		for(int i = 0; i < T; i++)
			trees[i] = Integer.parseInt(br.readLine());
		
		// QuickSort
		//quickSort(trees, 0, trees.length - 1);
		
		// DualPivotQuickSort - Arrays.sort의 기본형 
		
		int maxDiffNum = trees[1] - trees[0];
		for(int i = 1; i < T - 1; i++) {
			int newDiffNum = trees[i + 1] - trees[i];
			
			maxDiffNum = getMaxDivNum(maxDiffNum, newDiffNum);
		}
		
		int count = 0;
		for(int i = 0; i < T - 1; i++) {
			int diff = trees[i + 1] - trees[i];
			
			count = count + (diff / maxDiffNum - 1);
		}
		
		System.out.println(count);
	}
	
	public static int getMaxDivNum(int d1, int d2) {
		int limit = d1 <= d2 ? d1 : d2;
		
		int maxDiv = 1;
		
		for(int i = limit; i >= 1; i--) {
			if(d1 % i == 0 && d2 % i == 0){
				maxDiv = i;
				break;
			}
		}
		
		return maxDiv;
	}
	
	public static void dualPivotQuickSort(int[] arr, int low, int high) {
		if(arr[low] > arr[high]) {
			int temp = arr[low];
			arr[low] = arr[high];
			arr[high] = temp;
		}
		
		int leftPivotIdx = low + 1;
		int rightPivotIdx = high - 1;
		
		int iter = leftPivotIdx;
		
		while(iter <= rightPivotIdx) {
			if(arr[iter] < arr[low]) {
				swap(arr, leftPivotIdx++, iter++);
			} else if(arr[iter] > arr[high]) {
				swap(arr, rightPivotIdx--, iter);
			} else
				iter++;
		}
		
		swap(arr, low, --leftPivotIdx);
		swap(arr, high, ++rightPivotIdx);
		
		dualPivotQuickSort(arr, low, leftPivotIdx - 1);
		dualPivotQuickSort(arr, leftPivotIdx + 1, rightPivotIdx - 1);
		dualPivotQuickSort(arr, rightPivotIdx + 1, high);
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
			
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		
		int temp = arr[pivot];
		arr[pivot] = arr[i];
		arr[i] = temp;
		
		quickSort(arr, start, i - 1); quickSort(arr, i + 1, end);
	}
	
	public static void swap(int[] arr, int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}
