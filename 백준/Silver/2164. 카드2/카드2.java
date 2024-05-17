import java.util.*;
import java.io.*;

/**
카드2

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초 (추가 시간 없음)	128 MB	122909	63746	49644	50.840%

문제
----
N장의 카드가 있다. 

각각의 카드는 차례로 1부터 N까지의 번호가 붙어 있으며, 
1번 카드가 제일 위에, 
N번 카드가 제일 아래인 상태로 순서대로 카드가 놓여 있다.

이제 다음과 같은 동작을 카드가 한 장 남을 때까지 반복하게 된다. 

우선, 제일 위에 있는 카드를 바닥에 버린다. 

그 다음, 제일 위에 있는 카드를 제일 아래에 있는 카드 밑으로 옮긴다.

예를 들어 N=4인 경우를 생각해 보자. 

카드는 제일 위에서부터 1234 의 순서로 놓여있다. 

1을 버리면 234가 남는다. 

여기서 2를 제일 아래로 옮기면 342가 된다. 

3을 버리면 42가 되고, 
4를 밑으로 옮기면 24가 된다. 

마지막으로 2를 버리고 나면, 
남는 카드는 4가 된다.

N이 주어졌을 때, 제일 마지막에 남게 되는 카드를 구하는 프로그램을 작성하시오.

입력
----
첫째 줄에 정수 N(1 ≤ N ≤ 500,000)이 주어진다.

출력
----
첫째 줄에 남게 되는 카드의 번호를 출력한다.

예제 입력 1 
6
예제 출력 1 
4
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int number = Integer.parseInt(br.readLine());
		
		Deck7 deck = new Deck7();
		
		for(int i = number; i >= 1; i--)
			deck.push(i);
		
		while(deck.size() != 1) {
			deck.popFront();
			
			int temp = deck.popFront();
			deck.pushBottom(temp);
		}
		
		System.out.println(deck.pop());
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
}

class Deck7{
	Node7 startNode;
	Node7 headNode;
	int size;
	
	public Deck7() {
		this.startNode = null;
		this.headNode = null;
		this.size = 0;
	}
	
	public boolean push(int value) {
		Node7 newNode = new Node7(value);
		if(headNode == null) {
			startNode = newNode;
			headNode = newNode;
		} else {
			startNode.setPreviousNode(newNode);
			newNode.setNextNode(startNode);
			startNode = newNode;
		}
		size++;
		return true;
	}
	public boolean pushBottom(int value) {
		Node7 newNode = new Node7(value);
		if(headNode == null) {
			startNode = newNode;
			headNode = newNode;
		} else {
			headNode.setNextNode(newNode);
			newNode.setPreviousNode(headNode);
			headNode = newNode;
		}
		size++;
		return true;
	}
	
	public int pop() {
		if(isEmpty())
			return -1;
		
		int returnValue = headNode.getValue();
		
		if(startNode == headNode) {
			startNode = null;
			headNode = null;
		} else {
			headNode = headNode.getPreviousNode();
			headNode.setNextNode(null);
		}
		size--;
		return returnValue;
	}
	public int popFront() {
		if(isEmpty())
			return -1;
		
		int returnValue = startNode.getValue();
		
		if(startNode == headNode) {
			startNode = null;
			headNode = null;
		} else {
			startNode = startNode.getNextNode();
			startNode.setPreviousNode(null);
		}
		size--;
		return returnValue;
	}
	
	public int size() {
		return this.size;
	}
	
	public boolean isEmpty() {
		return (this.size == 0) ? true : false;
	}
}

class Node7{
	Integer value;
	Node7 preNode;
	Node7 nextNode;
	
	public Node7() {
		
	}
	public Node7(Integer value) {
		this.value = value;
	}
	
	public Integer getValue() {
		return this.value;
	}
	public void setValue(Integer value) {
		this.value = value;
	}
	
	public Node7 getPreviousNode() {
		return this.preNode;
	}
	public void setPreviousNode(Node7 preNode) {
		this.preNode = preNode;
	}
	
	public Node7 getNextNode() {
		return this.nextNode;
	}
	public void setNextNode(Node7 nextNode) {
		this.nextNode = nextNode;
	}
}
