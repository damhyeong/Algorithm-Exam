
import java.util.*;
import java.io.*;

/**
예제 입력 1 
11
6
1 3
1 8
7
8
3
2 5
1 2
5
4
4
예제 출력 1 
1
8
3
8
3
5
3

덱 2
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	1024 MB	300	189	159	65.975%
문제
정수를 저장하는 덱을 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 여덟 가지이다.

1 X: 정수 X를 덱의 앞에 넣는다. (1 ≤ X ≤ 100,000)
2 X: 정수 X를 덱의 뒤에 넣는다. (1 ≤ X ≤ 100,000)
3: 덱에 정수가 있다면 맨 앞의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
4: 덱에 정수가 있다면 맨 뒤의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
5: 덱에 들어있는 정수의 개수를 출력한다.
6: 덱이 비어있으면 1, 아니면 0을 출력한다.
7: 덱에 정수가 있다면 맨 앞의 정수를 출력한다. 없다면 -1을 대신 출력한다.
8: 덱에 정수가 있다면 맨 뒤의 정수를 출력한다. 없다면 -1을 대신 출력한다.
입력
첫째 줄에 명령의 수 N이 주어진다. (1 ≤ N ≤ 1,000,000)

둘째 줄부터 N개 줄에 명령이 하나씩 주어진다.

출력을 요구하는 명령은 하나 이상 주어진다.

출력
출력을 요구하는 명령이 주어질 때마다 명령의 결과를 한 줄에 하나씩 출력한다.

 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		
		LinkedList<Integer> list = new LinkedList<>();
		
		StringTokenizer st;
		
		while(N --> 0) {
			st = new StringTokenizer(br.readLine());
			int commandNum = Integer.parseInt(st.nextToken());
			
			if(st.hasMoreTokens()) {
				int newNum = Integer.parseInt(st.nextToken());
				
				if(commandNum == 1) 
					list.addFirst(newNum);
				else if(commandNum == 2) 
					list.addLast(newNum);
				continue;
			}
			
			switch(commandNum) {
			//3: 덱에 정수가 있다면 맨 앞의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
			case 3:
				if(!list.isEmpty()) 
					bw.write(Integer.toString(list.removeFirst()) + "\n");
				else 
					bw.write("-1\n");
				
				break;
			//4: 덱에 정수가 있다면 맨 뒤의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
			case 4:
				if(!list.isEmpty()) 
					bw.write(Integer.toString(list.removeLast()) + "\n");
				else 
					bw.write("-1\n");
				
				break;
			//5: 덱에 들어있는 정수의 개수를 출력한다.
			case 5:
				bw.write(Integer.toString(list.size()) + "\n");
				break;
			//6: 덱이 비어있으면 1, 아니면 0을 출력한다.
			case 6:
				bw.write((list.isEmpty() ? "1" : "0") + "\n");
				break;
			//7: 덱에 정수가 있다면 맨 앞의 정수를 출력한다. 없다면 -1을 대신 출력한다.
			case 7:
				if(!list.isEmpty()) 
					bw.write(list.peekFirst() + "\n");
				 else
					bw.write("-1\n");
				break;
			//8: 덱에 정수가 있다면 맨 뒤의 정수를 출력한다. 없다면 -1을 대신 출력한다.
			case 8:
				if(!list.isEmpty())
					bw.write(list.peekLast() + "\n");
				else
					bw.write("-1\n");
				break;
			}
		}
		bw.flush();
		bw.close();
		br.close();
	}

}
