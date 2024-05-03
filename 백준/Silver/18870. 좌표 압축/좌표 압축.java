import java.util.*;
import java.io.*;

/**
좌표 압축
-------
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	512 MB	94658	39901	29973	39.511%

문제
----
수직선 위에 N개의 좌표 X1, X2, ..., XN이 있다. 이 좌표에 좌표 압축을 적용하려고 한다.

Xi를 좌표 압축한 결과 X'i의 값은 Xi > Xj를 만족하는 서로 다른 좌표 Xj의 개수와 같아야 한다.

X1, X2, ..., XN에 좌표 압축을 적용한 결과 X'1, X'2, ..., X'N를 출력해보자.

입력
-----
첫째 줄에 N이 주어진다.

둘째 줄에는 공백 한 칸으로 구분된 X1, X2, ..., XN이 주어진다.

출력
-----
첫째 줄에 X'1, X'2, ..., X'N을 공백 한 칸으로 구분해서 출력한다.

제한
-----
1 ≤ N ≤ 1,000,000
-109 ≤ Xi ≤ 109
예제 입력 1 
5
2 4 -10 4 -9
예제 출력 1 
2 3 0 3 1
예제 입력 2 
6
1000 999 1000 999 1000 999
예제 출력 2 
1 0 1 0 1 0
 */

public class Main {
	public static int[] arr;
	public static int[] noDuplicitNum;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		
		int[] orgArr = new int[N]; // 원본을 저장 해 둘 곳.
		arr = new int[N]; // 정렬 될 수 - 정렬 후, 중복은 없앤다.
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		for(int i = 0; i < N; i++) {
			int num = Integer.parseInt(st.nextToken());
			orgArr[i] = num;
			arr[i] = num;
		}
		
		// ---------------------------------------------------------------------
		
		// quickSort
		// quickSort(0, arr.length - 1);
		
		// mergeSort
		// mergeSort(arr);
		
		// heapSort
		heapSort();
		
		// 정렬 완료. - 중복값 남은 상태.
		
		int initialNum = arr[0];
		int count = 1;
		for(int i = 1; i < arr.length; i++) {
			int num = arr[i];
			
			// 이전과 중복된 값일 경우, 폐기.
			if(initialNum == num) {
				continue;
			}
			
			// 저장해야 할 수 증가.
			arr[count++] = num;
			
			initialNum = num;
		}
		
		noDuplicitNum = new int[count];
		
		for(int i = 0; i < count; i++)
			noDuplicitNum[i] = arr[i];
		
		// noDuplicitNum에서 이분 탐색을 통해 인덱스 값을 구하자.
		
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < orgArr.length; i++) {
			int index = searchBinaryIndex(orgArr[i], 0, noDuplicitNum.length - 1);
			sb.append(index); sb.append(" ");
		}
		System.out.println(sb.toString());
		
	}
	
	public static int searchBinaryIndex(int value, int start, int end) {
		int mIdx = (start + end) / 2;
		int mValue = noDuplicitNum[mIdx];
		
		if(value > mValue) {
			return searchBinaryIndex(value, mIdx + 1, end);
		} else if(value < mValue){
			return searchBinaryIndex(value, start, mIdx - 1);
		} else { // value == noDuplicitNum[mIdx] 
			return mIdx;
		}
	}
	
	public static void quickSort(int start, int end) {
		if(end - start <= 0)
			return;
		
		int pivot = start;
		int i = start;
		int j = end;
		
		while(i < j) {
			while(arr[pivot] < arr[j])
				j--;
			while(i < j && arr[pivot] >= arr[i])
				i++;
			
			swapIndex(i, j);
		}
		swapIndex(i, pivot);
		
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
			swapIndex(0, i);
			
			heapify(i, 0);
		}
	}
	public static void heapify(int end, int index) {
		int parent = index;
		int left = parent * 2 + 1;
		int right = parent * 2 + 2;
		
		if(left < end && arr[parent] < arr[left])
			parent = left;
		if(right < end && arr[parent] < arr[right])
			parent = right;
		
		if(parent != index) {
			swapIndex(parent, index);
			heapify(end, parent);
		}
	}
	
	public static void swapIndex(int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
	public static int charToInt(char ch) {
		switch(ch) {
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		default:
			return -1;	
		}
	}
	
	public static char intToChar(int num) {
		switch(num) {
		case 0:
			return '0';
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
		default:
			return '-';
		}
	}
}
