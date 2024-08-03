import java.util.*;
import java.io.*;

/**
가장 긴 증가하는 부분 수열 2

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	512 MB	53869	22066	15448	41.324%

문제
---
수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.

예를 들어, 수열 A = {10, 20, 10, 30, 20, 50} 인 경우에,

가장 긴 증가하는 부분 수열은 A = {*10*, *20*, 10, *30*, 20, *50*} 이고, 길이는 4이다.


입력
---
첫째 줄에 수열 A의 크기 N (1 ≤ N ≤ 1,000,000)이 주어진다.

둘째 줄에는 수열 A를 이루고 있는 Ai가 주어진다. 

(1 ≤ Ai ≤ 1,000,000)


출력
----
첫째 줄에 수열 A의 가장 긴 증가하는 부분 수열의 길이를 출력한다.

예제 입력 1 
6
10 20 10 30 20 50
예제 출력 1 
4
 */

/*
이전의 가장 긴 증가하는 부분 수열 문제는 N^2 문제였다.

그런데, 이분 탐색으로 어떻게 이 문제를 풀 수 있을까?

일단, 기존의 방식대로 배열의 현재 인덱스와 이전의 인덱스들을 전부 비교하여,

현재 인덱스에 발생할 수 있는 최대 길이의 부분 수열을 기록하는 것은 불가능하다. (N^2 으로 풀기에는 N 인 백만이 너무 크기 때문) 

이분 탐색으로 풀 수 있는 문제라고 힌트가 주어졌으니, 

이분 탐색의 조건을 찾아야 한다.

1. 이분 탐색을 시작할 숫자와 가장 큰 숫자 정의
2. 위의 숫자를 이분하여 또 다시 재귀할 조건을 정의 (어떨 때 시작 ~ 중간 or 중간 ~ 끝) 
3. 이분하였을 때, 어떤 상황에서 어떠한 수를 비교하는지 정의 


가설 1. 입력을 받으며 이전의 숫자보다 크다면 +1, 이전의 숫자보다 작다면 1 부터 시작 - 일종의 tempDp 역할을 해보자.

10	20	10	30	20	50 - 최적 (10, 20, 30, 50) 4개 
1	2	1	2	1	2 

10 	20	50	20	80	90	10	100	20	30	40	50 - 최적 (10, 20, 50, 80, 90, 100) 6개 
1	2	3	1	2	3	1	2	1	2	3	4

12
10 20 50 20 80 90 10 100 20 30 40 50 

10	100	20	30	40	50	10	20	50	20	80	90 - 최적(10, 20, 30, 40, 50, 80, 90) 7개 
1	2	1	2	3	4	1	2	3	1	2	3

12
10 100 20 30 40 50 10 20 50 20 80 90

 */

public class Main {
	public static int size = 1;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		int[] list = new int[N];
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		list[0] = Integer.parseInt(st.nextToken());
//		int size = 1;
		
		for(int i = 1; i < N; i++) {
			int num = Integer.parseInt(st.nextToken());
			
			// list의 마지막과 동일한 경우는 어떠한 조치도 취하지 않는다.
			if(list[size - 1] > num) {
				binarySearch(list, num, 0, size - 1);
			} else if(list[size - 1] < num){
				list[size++] = num;
			}
		}
		
		System.out.println(size);
		
	}
	
	public static void binarySearch(int[] list, int num, int sIdx, int eIdx) {
		int mIdx = (sIdx + eIdx) / 2;
		
		if(sIdx > eIdx) {
			list[sIdx] = num;
			return;
		}
			
		if(list[mIdx] < num) {
			binarySearch(list, num, mIdx + 1, eIdx);
		} else { // (list[mIdx] <= num)
			binarySearch(list, num, sIdx, mIdx - 1);
		}
	}
}
