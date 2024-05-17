import java.util.*;
import java.io.*;

/**
덱 2

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	1024 MB	11461	5620	5016	50.321%

문제
----
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
----
첫째 줄에 명령의 수 N이 주어진다. (1 ≤ N ≤ 1,000,000)

둘째 줄부터 N개 줄에 명령이 하나씩 주어진다.

출력을 요구하는 명령은 하나 이상 주어진다.

출력
----
출력을 요구하는 명령이 주어질 때마다 명령의 결과를 한 줄에 하나씩 출력한다.

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
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int loop = Integer.parseInt(br.readLine());
		
		Deck9 deck = new Deck9();
		
		StringBuilder sb = new StringBuilder();
		while(loop-- > 0) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int order = Integer.parseInt(st.nextToken());
			
			if(order == 1) {
				int inputNum = Integer.parseInt(st.nextToken());
				deck.addTop(inputNum);
			} else if(order == 2) {
				int inputNum = Integer.parseInt(st.nextToken());
				deck.addBottom(inputNum);
			} else if(order == 3) {
				sb.append(deck.popTop()).append("\n");
			} else if(order == 4) {
				sb.append(deck.popBottom()).append("\n");
			} else if(order == 5) {
				sb.append(deck.size()).append("\n");
			} else if(order == 6) {
				sb.append(deck.isEmpty() ? 1 : 0).append("\n");
			} else if(order == 7) {
				sb.append(deck.peekTop()).append("\n");
			} else if(order == 8) {
				sb.append(deck.peekBottom()).append("\n");
			}
		}
		System.out.println(sb.toString());
	}

}

class Deck9{
	Node9 topNode;
	Node9 bottomNode;
	int size;
	
	public Deck9() {
		this.size = 0;
		this.topNode = null;
		this.bottomNode = null;
	}
	
	// 정수를 덱의 맨 위에 넣는다.
	public boolean addTop(int newNum) {
		Node9 newNode = new Node9(newNum);
		if(isEmpty()) {
			this.topNode = newNode;
			this.bottomNode = newNode;
			this.size++;
			return true;
		} else {
			this.topNode.setUpperNode(newNode);
			newNode.setLowerNode(this.topNode);
			this.topNode = newNode;
			this.size++;
			return true;
		}
	}
	// 정수를 덱의 맨 밑에 넣는다.
	public boolean addBottom(int newNum) {
		Node9 newNode = new Node9(newNum);
		if(isEmpty()) {
			this.topNode = newNode;
			this.bottomNode = newNode;
			this.size++;
			return true;
		}
		this.bottomNode.setLowerNode(newNode);
		newNode.setUpperNode(this.bottomNode);
		this.bottomNode = newNode;
		this.size++;
		return true;
	}
	
	// 덱에 정수가 있다면 맨 위의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
	public int popTop() {
		if(isEmpty()) {
			return -1;
		}
		int returnValue = this.topNode.getValue();
		
		this.topNode = this.topNode.getLowerNode();
		
		size--;
		
		if(size == 0) {
			this.topNode = null;
			this.bottomNode = null;
		}
		return returnValue;
	}
	// 덱에 정수가 있다면 맨 밑의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
	public int popBottom() {
		if(isEmpty()) {
			return -1;
		}
		int returnValue = this.bottomNode.getValue();
		
		this.bottomNode = this.bottomNode.getUpperNode();
		
		size--;
		
		if(size == 0) {
			this.topNode = null;
			this.bottomNode = null;
		}
		return returnValue;
	}
	
	// 덱에 정수가 있다면 맨 위의 정수를 출력한다. 없다면 -1을 대신 출력한다. 
	public int peekTop() {
		if(isEmpty()) {
			return -1;
		} else {
			return this.topNode.getValue();
		}
	}
	// 덱에 정수가 있다면 맨 밑의 정수를 출력한다. 없다면 -1을 대신 출력한다.
	public int peekBottom() {
		if(isEmpty()) {
			return -1;
		} else {
			return this.bottomNode.getValue();
		}
	}
	
	public boolean isEmpty() {
		return this.size == 0 ? true : false;
	}
	
	public int size() {
		return this.size;
	}
}

class Node9{
	Integer value;
	Node9 upperNode;
	Node9 lowerNode;
	
	public Node9() {
		
	}
	public Node9(Integer value) {
		this.value = value;
	}
	
	public Integer getValue() {
		return this.value;
	}
	public boolean setValue(Integer value) {
		this.value = value;
		return true;
	}
	
	public Node9 getUpperNode() {
		return this.upperNode;
	}
	public boolean setUpperNode(Node9 upperNode) {
		this.upperNode = upperNode;
		return true;
	}
	
	public Node9 getLowerNode() {
		return this.lowerNode;
	}
	public boolean setLowerNode(Node9 lowerNode) {
		this.lowerNode = lowerNode;
		return true;
	}
}