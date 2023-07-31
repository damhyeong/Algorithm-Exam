
import java.util.*;
import java.io.*;

/**
문제
직선으로 되어있는 도로의 한 편에 가로수가 임의의 간격으로 심어져있다. 
KOI 시에서는 가로수들이 모두 같은 간격이 되도록 가로수를 추가로 심는 사업을 추진하고 있다.
KOI 시에서는 예산문제로 가능한 한 가장 적은 수의 나무를 심고 싶다.

편의상 가로수의 위치는 기준점으로 부터 떨어져 있는 거리로 표현되며, 가로수의 위치는 모두 양의 정수이다.

예를 들어, 가로수가 (1, 3, 7, 13)의 위치에 있다면 (5, 9, 11)의 위치에 가로수를 더 심으면 모든 가로수들의 간격이 같게 된다. 
또한, 가로수가 (2, 6, 12, 18)에 있다면 (4, 8, 10, 14, 16)에 가로수를 더 심어야 한다.

심어져 있는 가로수의 위치가 주어질 때, 모든 가로수가 같은 간격이 되도록 새로 심어야 하는 가로수의 최소수를 구하는 프로그램을 작성하라. 
단, 추가되는 나무는 기존의 나무들 사이에만 심을 수 있다.

입력
첫째 줄에는 이미 심어져 있는 가로수의 수를 나타내는 하나의 정수 N이 주어진다(3 ≤ N ≤ 100,000). 
둘째 줄부터 N개의 줄에는 각 줄마다 심어져 있는 가로수의 위치가 양의 정수로 주어지며, 가로수의 위치를 나타내는 정수는 1,000,000,000 이하이다. 
가로수의 위치를 나타내는 정수는 모두 다르다.

출력
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
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		long N = Long.parseLong(br.readLine());
		
		LinkedList<Long> trees = new LinkedList<>();
		
		// 위치를 받는 과정 
		while(N --> 0) {
			trees.add(Long.parseLong(br.readLine()));
		}
		// 테스트 케이스에서 순서대로 나온다는 얘기가 없으므로, 순서대로 정렬해준다. 
		trees.sort(new Comparator<Long>() {
			public int compare(Long l1, Long l2) {
				return l1.compareTo(l2);
			}
		});
		
		// 반복자를 할당. 
		Iterator iter = trees.iterator();
		
		// 최대공약수를 구하기 위해 min이라는 변수를 만든다. 추후, 최대공약수는 가장 큰 수 보다는 작거나 같으므로, 가장 큰 수로 책정한다. 
		long min = trees.getLast();
		
		// 첫 번째 반복자에서 길이 차이를 알기 위해 첫 번째 수를 먼저 할당한다. 
		long iNum = (long)iter.next();
		
		// 첫 번째 반복자에서는 길이 차이 경우의 수가 1개밖에 없으므로 최대공약수를 구할 수 없다. 따라서 0을 할당해 유클리드 공식을 사용하지 않도록 생성.
		int fCnt = 0;
		
		while(iter.hasNext()) {
			long newNum = (long)iter.next();
			long diff = newNum - iNum;
			iNum = newNum;
			if(diff != min) {
				if(fCnt != 0)
					min = shareMax(min, diff);
				else
					min = diff;
			}
			fCnt++;
		}
		
		long cnt = 0;
		
		iter = trees.iterator();
		iNum = (long)iter.next();
		while(iter.hasNext()) {
			long newNum = (long)iter.next();
			long diff = newNum - iNum;
			iNum = newNum;
			cnt = cnt + (diff / min - 1);
		}
		bw.write(Long.toString(cnt));
		bw.flush();
		bw.close();
		br.close();
	}

	
	public static long shareMax(long l1, long l2) {
		long divNum = l1 % l2;
		if(divNum == 0)
			return l2;
		else
			return shareMax(l2, divNum);
	}
}
