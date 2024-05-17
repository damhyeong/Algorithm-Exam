import java.util.*;
import java.io.*;

/**
큐 2

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초 (하단 참고)	512 MB	100404	32410	26256	32.522%

문제
----
정수를 저장하는 큐를 구현한 다음,
입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 여섯 가지이다.

push X: 정수 X를 큐에 넣는 연산이다.
pop: 큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
size: 큐에 들어있는 정수의 개수를 출력한다.
empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
front: 큐의 가장 앞에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
back: 큐의 가장 뒤에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.


입력
----
첫째 줄에 주어지는 명령의 수 N (1 ≤ N ≤ 2,000,000)이 주어진다. 

둘째 줄부터 N개의 줄에는 명령이 하나씩 주어진다. 

주어지는 정수는 1보다 크거나 같고, 100,000보다 작거나 같다. 

문제에 나와있지 않은 명령이 주어지는 경우는 없다.

출력
----
출력해야하는 명령이 주어질 때마다, 한 줄에 하나씩 출력한다.

예제 입력 1 
15
push 1
push 2
front
back
size
empty
pop
pop
pop
size
empty
pop
push 3
empty
front
예제 출력 1 
1
2
2
0
1
2
-1
0
1
-1
0
3
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int loop = Integer.parseInt(br.readLine());
		
		Queue6 queue = new Queue6();
		
		StringBuilder sb = new StringBuilder();
		while(loop-- > 0) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			
			String order = st.nextToken();
			
			if(order.equals("push")) {
				int pushNum = Integer.parseInt(st.nextToken());
				queue.push(pushNum);
			} else if(order.equals("pop")) {
				if(queue.isEmpty()) {
					sb.append("-1").append("\n");
				} else {
					sb.append(queue.poll()).append("\n");
				}
			} else if(order.equals("size")) {
				sb.append(queue.size()).append("\n");
			} else if(order.equals("empty")) {
				if(queue.isEmpty()) 
					sb.append("1").append("\n");
				else
					sb.append("0").append("\n");
			} else if(order.equals("front")) {
				if(queue.isEmpty())
					sb.append("-1").append("\n");
				else {
					sb.append(queue.peek()).append("\n");
				}
			} else if(order.equals("back")) {
				if(queue.isEmpty())
					sb.append("-1").append("\n");
				else
					sb.append(queue.front()).append("\n");
			}
		}
		
		System.out.println(sb.toString());
	}

}

class Queue6{
	Node6 lastNode;
	Node6 headNode;
	int size;
	
	public Queue6() {
		this.lastNode = null;
		this.size = 0;
	}
	public boolean push(int value) {
		return add(value);
	}
	
	public boolean add(int value) {
		if(headNode == null) {
			headNode = new Node6(value);
			lastNode = headNode;
			size++;
			return true;
		} else {
			Node6 newNode = new Node6(value);
			lastNode.setpreviousNode(newNode);
			lastNode = newNode;
			size++;
			return true;
		}
	}
	
	public int poll() {
		if(headNode == null)
			return -1;
		
		Integer returnValue = headNode.getValue();
		
		headNode = headNode.getpreviousNode();
		
		if(headNode == null)
			lastNode = null;
		
		size--;
		return returnValue;
	}
	
	public int peek() {
		return headNode.getValue();
	}
	public int front() {
		return lastNode.getValue();
	}
	
	public boolean isEmpty() {
		return size == 0 ? true : false;
	}
	
	public int size() {
		return this.size;
	}
}

class Node6{
	Integer value;
	Node6 previousNode;
	
	public Node6 () {
		this.value = null;
		this.previousNode = null;
	}
	public Node6(Integer value) {
		this.value = value;
	}
	
	public Integer getValue() {
		return this.value;
	}
	public boolean setValue(Integer value) {
		if(value == null)
			return false;
		
		this.value = value;
		return true;
	}
	
	public Node6 getpreviousNode() {
		return this.previousNode;
	}
	public boolean setpreviousNode(Node6 previousNode) {
		if(previousNode == null)
			return false;
		
		this.previousNode = previousNode;
		return true;
	}
}
