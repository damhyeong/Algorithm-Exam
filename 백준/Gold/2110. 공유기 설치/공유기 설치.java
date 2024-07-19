import java.util.*;
import java.io.*;

/**
공유기 설치 다국어

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	77310	27636	19162	36.444%

문제
---
도현이의 집 N개가 수직선 위에 있다. 각각의 집의 좌표는 x1, ..., xN이고, 
집 여러개가 같은 좌표를 가지는 일은 없다.

도현이는 언제 어디서나 와이파이를 즐기기 위해서 집에 공유기 C개를 설치하려고 한다. 

최대한 많은 곳에서 와이파이를 사용하려고 하기 때문에, 
한 집에는 공유기를 하나만 설치할 수 있고, 
가장 인접한 두 공유기 사이의 거리를 가능한 크게 하여 설치하려고 한다.

C개의 공유기를 N개의 집에 적당히 설치해서, 
가장 인접한 두 공유기 사이의 거리를 최대로 하는 프로그램을 작성하시오.


입력
---
첫째 줄에 집의 개수 N (2 ≤ N ≤ 200,000)과 공유기의 개수 C (2 ≤ C ≤ N)이 하나 이상의 빈 칸을 사이에 두고 주어진다. 

둘째 줄부터 N개의 줄에는 집의 좌표를 나타내는 x_i (0 ≤ x_i ≤ 1,000,000,000)가 한 줄에 하나씩 주어진다.


출력
---
첫째 줄에 가장 인접한 두 공유기 사이의 최대 거리를 출력한다.


예제 입력 1 
5 3
1
2
8
4
9
예제 출력 1 
3

힌트
---
공유기를 1, 4, 8 또는 1, 4, 9에 설치하면 가장 인접한 두 공유기 사이의 거리는 3이고, 이 거리보다 크게 공유기를 3개 설치할 수 없다.
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken()); int C = Integer.parseInt(st.nextToken());
		
		long[] points = new long[N];
		
		for(int i = 0; i < N; i++)
			points[i] = Long.parseLong(br.readLine());
		
		// SortHelper.quickSort(points, 0, points.length - 1);
		
		// SortHelper.mergeSort(points);
		
		SortHelper.heapSort(points);
		
		// SortHelper.dualPivotQuickSort(points, 0, points.length - 1);
		
		long[] widths = new long[points.length];
		
		widths[0] = 0;
		
		for(int i = 1; i < widths.length; i++) 
			widths[i] = points[i] - points[i - 1];
		
		long result = getMaxWidth(widths, C);
		
		System.out.println(result);
	}
	public static long getMaxWidth(long[] widths, int C) {
		return getWidth(widths, C, 0, Integer.MAX_VALUE);
	}
	public static long getWidth(long[] widths, int C, long sNum, long eNum) {
		if(sNum > eNum)
			return -1;
		
		long midWidth = (sNum + eNum) / 2;
		
		boolean isAbleWidth = isAbleWidth(widths, C, midWidth);
		
		if(isAbleWidth) {
			long width = getWidth(widths, C, midWidth + 1, eNum);
			
			if(width == -1)
				return midWidth;
			else
				return width;
		} else {
			return getWidth(widths, C, sNum, midWidth - 1);
		}
		
	}
	public static boolean isAbleWidth(long[] widths, int C, long width) {
		// 첫 번째 집에 곧바로 설치한다고 가정.
		int cnt = C - 1;
		
		long currWidth = 0;
		for(int i = 1; i < widths.length; i++) {
			if(cnt == 0)
				break;
			
			currWidth += widths[i];
			
			if(width <= currWidth) {
				currWidth = 0;
				cnt--;
			}
		}
		
		return cnt == 0 ? true : false;
	}
}

class SortHelper{
	public static void quickSort(long[] arr, int start, int end) {
		if(start >= end)
			return;
		
		int pivot = start;
		int left = start;
		int right = end;
		
		while(left < right) {
			while(arr[pivot] < arr[right])
				right--;
			while(left < right && arr[pivot] >= arr[left])
				left++;
			swap(arr, left, right);
		}
		
		swap(arr, pivot, left);
		
		quickSort(arr, start, left - 1);
		quickSort(arr, left + 1, end);
	}
	
	public static void mergeSort(long[] arr) {
		if(arr.length <= 1)
			return;
		
		int middle = arr.length / 2;
		
		long[] LArr = new long[middle];
		long[] RArr = new long[arr.length - middle];
		
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
	
	public static void heapSort(long[] arr) {
		int len = arr.length;
		
		for(int i = len / 2 - 1; i >= 0; i--)
			heapify(arr, len, i);
		
		for(int i = len - 1; i > 0; i--) {
			swap(arr, 0, i);
			heapify(arr, i, 0);
		}
	}
	private static void heapify(long[] arr, int end, int index) {
		int parent = index;
		int left = parent * 2 + 1;
		int right = parent * 2 + 2;
		
		if(left < end && arr[parent] < arr[left])
			parent = left;
		if(right < end && arr[parent] < arr[right])
			parent = right;
		
		if(parent != index) {
			swap(arr, parent, index);
			heapify(arr, end, parent);
		}
	}
	
	public static void dualPivotQuickSort(long[] arr, int low, int high) {
		if(low >= high)
			return;
		
		if(arr[low] > arr[high])
			swap(arr, low, high);
		
		int leftPivot = low + 1;
		int rightPivot = high - 1;
		int iter = leftPivot;
		
		while(iter <= rightPivot) {
			if(arr[iter] < arr[low])
				swap(arr, leftPivot++, iter++);
			else if(arr[iter] > arr[high])
				swap(arr, rightPivot--, iter);
			else
				iter++;
		}
		
		swap(arr, low, --leftPivot);
		swap(arr, high, ++rightPivot);
		
		dualPivotQuickSort(arr, low, leftPivot - 1);
		dualPivotQuickSort(arr, leftPivot + 1, rightPivot - 1);
		dualPivotQuickSort(arr, rightPivot + 1, high);
	}
	
	private static void swap(long[] arr, int i, int j) {
		long temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}
