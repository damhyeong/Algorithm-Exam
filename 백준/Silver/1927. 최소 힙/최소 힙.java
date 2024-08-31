import java.util.*;
import java.io.*;

/**
최소 힙

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초 (추가 시간 없음) (하단 참고)	128 MB	90671	43305	34269	49.104%

문제
---
널리 잘 알려진 자료구조 중 최소 힙이 있다. 

최소 힙을 이용하여 다음과 같은 연산을 지원하는 프로그램을 작성하시오.

배열에 자연수 x를 넣는다.

배열에서 가장 작은 값을 출력하고, 그 값을 배열에서 제거한다.

프로그램은 처음에 비어있는 배열에서 시작하게 된다.


입력
---
첫째 줄에 연산의 개수 N(1 ≤ N ≤ 100,000)이 주어진다. 

다음 N개의 줄에는 연산에 대한 정보를 나타내는 정수 x가 주어진다. 

만약 x가 자연수라면 배열에 x라는 값을 넣는(추가하는) 연산이고, 
x가 0이라면 배열에서 가장 작은 값을 출력하고 그 값을 배열에서 제거하는 경우이다. 

x는 2^31보다 작은 자연수 또는 0이고, 음의 정수는 입력으로 주어지지 않는다.


출력
---
입력에서 0이 주어진 횟수만큼 답을 출력한다. 

만약 배열이 비어 있는 경우인데 가장 작은 값을 출력하라고 한 경우에는 0을 출력하면 된다.

예제 입력 1 
9
0
12345678
1
2
0
0
0
0
32
예제 출력 1 
0
1
2
12345678
0
 */

public class Main {
	public static int size = 0;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		int[] arr = new int[100_000];
		
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < N; i++) {
			int num = Integer.parseInt(br.readLine());
			
			if(num == 0) {
				
				int minNum = getMinValue(arr);
				sb.append(minNum).append("\n");
			} else {
				insertValue(arr, num);
			}
		}
		
		System.out.println(sb.toString());
	}
	
	public static void insertValue(int[] arr, int num) {
		size++;
		
		arr[size - 1] = num;
		
		int index = size - 1;
		while(index != 0) {
			int parentIdx = (index - 1) / 2;
			
			if(arr[parentIdx] > arr[index]) {
				swap(arr, parentIdx, index);
				index = parentIdx;
			} else 
				break;
		}
		
		heapify(arr, size, index);
	}
	
	public static int getMinValue(int[] arr) {
		if(size == 0) {
			return 0;
		}
		
		int minNum = arr[0];
		
		arr[0] = arr[size - 1];
		
		arr[size - 1] = 0;
		
		heapify(arr, size - 1, 0);
		
		size--;
		
		return minNum;
	}
	// 위로 갈 수록 작아지는 트리 형태의 힙 
	public static void heapify(int[] arr, int len, int index) {
		int parent = index;
		int left = parent * 2 + 1;
		int right = parent * 2 + 2;
		
		if(left < len && arr[parent] > arr[left])
			parent = left;
		if(right < len && arr[parent] > arr[right])
			parent = right;
		
		if(parent != index){
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
