import java.util.*;
import java.io.*;

/**
스택 2

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	1024 MB	29136	10584	8830	37.014%

문제
----
정수를 저장하는 스택을 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 다섯 가지이다.

1 X: 정수 X를 스택에 넣는다. (1 ≤ X ≤ 100,000)
2: 스택에 정수가 있다면 맨 위의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
3: 스택에 들어있는 정수의 개수를 출력한다.
4: 스택이 비어있으면 1, 아니면 0을 출력한다.
5: 스택에 정수가 있다면 맨 위의 정수를 출력한다. 없다면 -1을 대신 출력한다.

입력
----
첫째 줄에 명령의 수 N이 주어진다. (1 ≤ N ≤ 1,000,000)

둘째 줄부터 N개 줄에 명령이 하나씩 주어진다.

출력을 요구하는 명령은 하나 이상 주어진다.

출력
----
출력을 요구하는 명령이 주어질 때마다 명령의 결과를 한 줄에 하나씩 출력한다.

예제 입력 1 
9
4
1 3
1 5
3
2
5
2
2
5
예제 출력 1 
1
2
5
3
3
-1
-1
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		
		Stack1 stack = new Stack1();
		
		StringBuilder sb = new StringBuilder();
		while(N-- > 0) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			
			int order = Integer.parseInt(st.nextToken());
			
			if(order == 1) {
				int newNum = Integer.parseInt(st.nextToken());
				stack.push(newNum);
			} else if(order == 2) {
				sb.append(stack.pop()).append("\n");
			} else if(order == 3) {
				sb.append(stack.size()).append("\n");
			} else if(order == 4) {
				sb.append(stack.isEmpty() ? 1 : 0).append("\n");
			} else if(order == 5) {
				sb.append(stack.getTopValue()).append("\n");
			}
		}
		System.out.println(sb.toString());
	}
}

class Stack1{
	int size;
	
	Node1 topNode;
	Node1 bottomNode;
	
	public Stack1() {
		this.size = 0;
	}
	
	public boolean push(Integer value) {
		Node1 newNode = new Node1(value);
		if(isEmpty()) {
			topNode = newNode;
			bottomNode = newNode;
		} else {
			newNode.setNextNode(topNode);
			topNode = newNode;
		}
		size++;
		return true;
	}
	public int pop() {
		if(isEmpty()) {
			return -1;
		}
		
		int newValue = topNode.getValue();
		topNode = topNode.getNextNode();
		
		size--;
		
		if(isEmpty()) {
			topNode = null;
			bottomNode = null;
		}
		
		return newValue;
	}
	
	public int getTopValue() {
		if(topNode == null) {
			return -1;
		} else {
			int returnValue = topNode.getValue();
			return returnValue;
		}
	}
	
	public boolean isEmpty() {
		return this.size == 0 ? true : false;
	}
	public int size() {
		return this.size;
	}
}

class Node1{
	Integer value;
	Node1 preNode;
	Node1 nextNode;
	
	public Node1() {
		
	}
	public Node1(Integer value) {
		this.value = value;
	}
	
	public void setPreNode(Node1 preNode) {
		this.preNode = preNode;
	}
	public Node1 getPreNode() {
		return this.preNode;
	}
	
	public void setNextNode(Node1 nextNode) {
		this.nextNode = nextNode;
	}
	public Node1 getNextNode() {
		return this.nextNode;
	}
	
	public void setValue(Integer value) {
		this.value = value;
	}
	public Integer getValue() {
		return this.value;
	}
}
