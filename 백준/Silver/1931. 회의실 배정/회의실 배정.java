import java.util.*;
import java.io.*;

/**
회의실 배정

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	219663	72207	50029	30.623%

문제
---
한 개의 회의실이 있는데 이를 사용하고자 하는 N개의 회의에 대하여 회의실 사용표를 만들려고 한다. 

각 회의 I에 대해 시작시간과 끝나는 시간이 주어져 있고, 각 회의가 겹치지 않게 하면서 회의실을 사용할 수 있는 회의의 최대 개수를 찾아보자. 

단, 회의는 한번 시작하면 중간에 중단될 수 없으며 한 회의가 끝나는 것과 동시에 다음 회의가 시작될 수 있다. 

회의의 시작시간과 끝나는 시간이 같을 수도 있다. 

이 경우에는 시작하자마자 끝나는 것으로 생각하면 된다.

입력
---
첫째 줄에 회의의 수 N(1 ≤ N ≤ 100,000)이 주어진다. 

둘째 줄부터 N+1 줄까지 각 회의의 정보가 주어지는데 이것은 공백을 사이에 두고 회의의 시작시간과 끝나는 시간이 주어진다. 

시작 시간과 끝나는 시간은 2^31-1보다 작거나 같은 자연수 또는 0이다.

출력
---
첫째 줄에 최대 사용할 수 있는 회의의 최대 개수를 출력한다.

예제 입력 1 
11
1 4
3 5
0 6
5 7
3 8
5 9
6 10
8 11
8 12
2 13
12 14
예제 출력 1 
4
힌트
(1,4), (5,7), (8,11), (12,14) 를 이용할 수 있다.
 */

public class Main {
	
	public static int maxMeet = Integer.MIN_VALUE;
	
	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int loop = Integer.parseInt(br.readLine());
		
		int[][] meetings = new int[loop][2];
		
		for(int i = 0; i < loop; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			meetings[i][0] = Integer.parseInt(st.nextToken());
			meetings[i][1] = Integer.parseInt(st.nextToken());
		}
		
		
		// --------------------------------------------------------------------------------------------------
		// QuickSort
		/**
		quickSort(meetings, 0, meetings.length - 1, 0);
		
		int currIdx = 0;
		int size = 1;
		int ridNum = meetings[0][0];
		int diffCnt = 1;
		for(int i = 1; i < meetings.length; i++) {
			if(meetings[i][0] == ridNum) {
				size++;
			} else {
				int[][] tempArr = new int[size][2];
				
				for(int j = 0; j < tempArr.length; j++) {
					tempArr[j][0] = meetings[j + currIdx][0];
					tempArr[j][1] = meetings[j + currIdx][1];
				}
				
				quickSort(tempArr, 0, tempArr.length - 1, 1);
				
				for(int j = 0; j < tempArr.length; j++) {
					meetings[j + currIdx][0] = tempArr[j][0];
					meetings[j + currIdx][1] = tempArr[j][1];
				}
				
				currIdx += size;
				size = 1;
				ridNum = meetings[currIdx][0];
				diffCnt++;
			}
		}
		
		if(size > 1) {
			int[][] tempArr = new int[size][2];
			
			for(int j = 0; j < tempArr.length; j++) {
				tempArr[j][0] = meetings[j + currIdx][0];
				tempArr[j][1] = meetings[j + currIdx][1];
			}
			
			quickSort(tempArr, 0, tempArr.length - 1, 1);
			
			for(int j = 0; j < tempArr.length; j++) {
				tempArr[j][0] = meetings[j + currIdx][0];
				tempArr[j][1] = meetings[j + currIdx][1];
			}
		}
		*/
		// --------------------------------------------------------------------------------------------------
		
		//mergeSort
		
		mergeSort(meetings, 1);
		
		int ridNum = meetings[0][1];
		int size = 1; 
		int currIdx = 0;
//		int diffCnt = 1;
		
		for(int i = 1; i < meetings.length; i++) {
			if(meetings[i][1] == ridNum) {
				size++;
			} else {
				int[][] tempArr = new int[size][2];
				
				for(int j = 0; j < tempArr.length; j++) {
					tempArr[j][0] = meetings[j + currIdx][0];
					tempArr[j][1] = meetings[j + currIdx][1];
				}
				
				mergeSort(tempArr, 0);
				
				for(int j = 0; j < tempArr.length; j++) {
					meetings[j + currIdx][0] = tempArr[j][0];
					meetings[j + currIdx][1] = tempArr[j][1];
				}
				ridNum = meetings[i][0];
				size = 1;
				currIdx = i;
//				diffCnt++;
			}
		}
		
		if(size > 1) {
			int[][] tempArr = new int[size][2];
			
			for(int j = 0; j < tempArr.length; j++) {
				tempArr[j][0] = meetings[j + currIdx][0];
				tempArr[j][1] = meetings[j + currIdx][1];
			}
			
			mergeSort(tempArr, 0);
			
			for(int j = 0; j < tempArr.length; j++) {
				meetings[j + currIdx][0] = tempArr[j][0];
				meetings[j + currIdx][1] = tempArr[j][1];
			}
		}
		
		
		
		// --------------------------------------------------------------------------------------------------
		
		
		
		
		
		
		// --------------------------------------------------------------------------------------------------
		
		// 수열을 이용하여 풀기 - 시간초과 실패...
		/**
		int[][] result = new int[diffCnt][2];
		
		result[0][0] = meetings[0][0];
		result[0][1] = meetings[0][1];
		
		System.out.println("[1] : " + result[0][0] + ", [2] : " + result[0][1]);
		
		int idx = 1;
		ridNum = meetings[0][0];
		for(int i = 1; i < meetings.length; i++) {
			if(meetings[i][0] == ridNum) {
				continue;
			} else {
				ridNum = meetings[i][0];
				
				result[idx][0] = meetings[i][0];
				result[idx][1] = meetings[i][1];
				
				System.out.println("[1] : " + result[idx][0] + ", [2] : " + result[idx][1]);
				
				idx++;
			}
		}
		
		getMaxMeet(meetings, -1, 0, 0);
		*/
		
		int count = 0;
		int endTime = 0;
		
		for(int[] meeting : meetings) {
			if(meeting[0] >= endTime) {
				endTime = meeting[1];
				count++;
			}
		}
		
		System.out.println(count);
	}
	
	public static void getMaxMeet(int[][] arr, int startTime, int startIdx, int count) {
		if(startIdx == arr.length) {
			maxMeet = maxMeet < count ? count : maxMeet;
			return;
		}
		
		
		for(int i = startIdx; i < arr.length; i++) {
			// 선택 불가능 시 
			if(arr[startIdx][0] < startTime) {
				getMaxMeet(arr, startTime, startIdx + 1, count);
			} else { // 선택 시 
				getMaxMeet(arr, arr[i][1] + 1, i + 1, count + 1);
			}
		}
	}
	
	public static void mergeSort(int[][] arr, int compareIdx) {
		if(arr.length == 1)
			return;
		
		int middle = arr.length / 2;
		
		int[][] LArr = new int[middle][2];
		int[][] RArr = new int[arr.length - middle][2];
		
		int cnt = 0;
		for(int i = 0; i < LArr.length; i++) {
			LArr[i][0] = arr[cnt][0];
			LArr[i][1] = arr[cnt][1];
			cnt++;
		}
		for(int i = 0; i < RArr.length; i++) {
			RArr[i][0] = arr[cnt][0];
			RArr[i][1] = arr[cnt][1];
			cnt++;
		}
		
		mergeSort(LArr, compareIdx); mergeSort(RArr, compareIdx);
		
		int i = 0, j = 0, index = 0;
		while(i < LArr.length && j < RArr.length) {
			if(LArr[i][compareIdx] <= RArr[j][compareIdx]) {
				arr[index][0] = LArr[i][0];
				arr[index][1] = LArr[i][1];
				index++; i++;
			} else {
				arr[index][0] = RArr[j][0];
				arr[index][1] = RArr[j][1];
				index++; j++;
			}
		}
		
		while(i < LArr.length) {
			arr[index][0] = LArr[i][0];
			arr[index][1] = LArr[i][1];
			index++; i++;
		}
		while(j < RArr.length) {
			arr[index][0] = RArr[j][0];
			arr[index][1] = RArr[j][1];
			index++; j++;
		}
	}
	
	public static void quickSort(int[][] arr, int start, int end, int compareIdx) {
		if(start >= end)
			return;
		
		int pivot = start;
		int i = start;
		int j = end;
		
		while(i < j) {
			while(arr[pivot][compareIdx] < arr[j][compareIdx])
				j--;
			while(i < j && arr[pivot][compareIdx] >= arr[i][compareIdx])
				i++;
			
			swap(arr, i, j);
		}
		
		swap(arr, pivot, i);
		
		quickSort(arr, start, i - 1, compareIdx);
		quickSort(arr, i + 1, end, compareIdx);
	}
	
	public static void swap(int[][] arr, int i, int j) {
		int[] temp = new int[2];
		
		temp[0] = arr[i][0];
		temp[1] = arr[i][1];
		
		arr[i][0] = arr[j][0];
		arr[i][1] = arr[j][1];
		
		arr[j][0] = temp[0];
		arr[j][1] = temp[1];
	}
	
}
