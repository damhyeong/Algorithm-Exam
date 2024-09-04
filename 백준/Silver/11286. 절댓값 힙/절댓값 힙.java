import java.util.*;
import java.io.*;

/**
절댓값 힙

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초 (추가 시간 없음) (하단 참고)	256 MB	61119	34587	27268	56.744%

문제
---
절댓값 힙은 다음과 같은 연산을 지원하는 자료구조이다.

배열에 정수 x (x ≠ 0)를 넣는다.

배열에서 절댓값이 가장 작은 값을 출력하고, 그 값을 배열에서 제거한다. 

절댓값이 가장 작은 값이 여러개일 때는, 가장 작은 수를 출력하고, 그 값을 배열에서 제거한다.

프로그램은 처음에 비어있는 배열에서 시작하게 된다.


입력
---
첫째 줄에 연산의 개수 N(1≤N≤100,000)이 주어진다. 

다음 N개의 줄에는 연산에 대한 정보를 나타내는 정수 x가 주어진다. 

만약 x가 0이 아니라면 배열에 x라는 값을 넣는(추가하는) 연산이고, 
x가 0이라면 배열에서 절댓값이 가장 작은 값을 출력하고 그 값을 배열에서 제거하는 경우이다. 

입력되는 정수는 -2^31보다 크고, 2^31보다 작다.

출력
---
입력에서 0이 주어진 회수만큼 답을 출력한다. 

만약 배열이 비어 있는 경우인데 절댓값이 가장 작은 값을 출력하라고 한 경우에는 0을 출력하면 된다.


예제 입력 1 
18
1
-1
0
0
0
1
1
-1
-1
2
-2
0
0
0
0
0
0
0
예제 출력 1 
-1
1
0
-1
-1
1
1
-2
2
0
 */

public class Main {
	public static int size = 0;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		int[] arr = new int[N];
		
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < N; i++) {
			int num = Integer.parseInt(br.readLine());
			
			if(num == 0) {
				sb.append(getMinAbsNum(arr)).append("\n");
			} else {
				insertAbsNum(arr, num);
			}
		}
		
		System.out.println(sb.toString());
	}
	
	public static int getMinAbsNum(int[] arr) {
		if(size == 0)
			return 0;
		
		int minAbsNum = arr[0];
		
		arr[0] = arr[size - 1];
		
		arr[size - 1] = 0;
		
		
		heapify(arr, size - 1, 0);
		
		size--;
		
		return minAbsNum;
	}
	
	public static void insertAbsNum(int[] arr, int num) {
		size++;
		
		arr[size - 1] = num;
		
		int index = size - 1;
		while(index != 0) {
			int parentIndex = (index - 1) / 2;
			
			int absParent = Math.abs(arr[parentIndex]);
			int absIndex = Math.abs(arr[index]);
			
			
			if(( Math.abs(arr[parentIndex]) > Math.abs(arr[index])) || ( absParent == absIndex && arr[parentIndex] > arr[index]) ) {
				swap(arr, index, parentIndex);
				index = parentIndex;
			} else
				break;
		}
		
		heapify(arr, size, index);
	}
	
	public static void heapify(int[] arr, int len, int index) {
		int parent = index;
		int left = parent * 2 + 1;
		int right = parent * 2 + 2;
		
		
		// 바로 밑에서 절대값이 같을 경우, parent, left 인덱스 비교하여 옮긴다. 
		
		if(left < len && Math.abs(arr[parent]) > Math.abs(arr[left]))
			parent = left;
		if(right < len && Math.abs(arr[parent]) > Math.abs(arr[right]))
			parent = right;
		if(left < len && (Math.abs(arr[parent]) == Math.abs(arr[left]) && arr[parent] > arr[left]) )
			parent = left;
		if(right < len && (Math.abs(arr[parent]) == Math.abs(arr[right]) && arr[parent] > arr[right]) )
			parent = right;
		
		if(parent != index) {
			swap(arr, parent, index);
			heapify(arr, len, parent);
		}
	}
	
	public static void swap(int[] arr, int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
}
