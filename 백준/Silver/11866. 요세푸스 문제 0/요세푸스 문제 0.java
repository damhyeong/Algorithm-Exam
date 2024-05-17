import java.util.*;
import java.io.*;

/**
요세푸스 문제 0

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	512 MB	79954	45401	38017	56.517%

문제
요세푸스 문제는 다음과 같다.

1번부터 N번까지 N명의 사람이 원을 이루면서 앉아있고, 양의 정수 K(≤ N)가 주어진다. 

이제 순서대로 K번째 사람을 제거한다. 

한 사람이 제거되면 남은 사람들로 이루어진 원을 따라 이 과정을 계속해 나간다. 

이 과정은 N명의 사람이 모두 제거될 때까지 계속된다. 

원에서 사람들이 제거되는 순서를 (N, K)-요세푸스 순열이라고 한다. 

예를 들어 (7, 3)-요세푸스 순열은 <3, 6, 2, 7, 5, 1, 4>이다.

N과 K가 주어지면 (N, K)-요세푸스 순열을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 빈 칸을 사이에 두고 순서대로 주어진다. (1 ≤ K ≤ N ≤ 1,000)

출력
예제와 같이 요세푸스 순열을 출력한다.

예제 입력 1 
7 3
예제 출력 1 
<3, 6, 2, 7, 5, 1, 4>
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken()); int K = Integer.parseInt(st.nextToken());
		
		CircleQueue circleQueue = new CircleQueue(K);
		
		circleQueue.addAll(N);
		
		int[] tempArr = new int[N];
		int index = 0;
		while(circleQueue.size() != 0) {
			tempArr[index++] = circleQueue.pop();
		}
		
		StringBuilder sb = new StringBuilder();
		sb.append('<');
		for(int i = 0; i < N; i++) {
			if(i != N - 1) {
				sb.append(tempArr[i]).append(", ");
			} else {
				sb.append(tempArr[i]);
			}
		}
		sb.append('>');
		
		System.out.println(sb.toString());
	}

}

class CircleQueue{
	Node8 currNode;
	Integer width;
	int size;
	
	public CircleQueue(int width){
		this.width = width;
		this.size = 0;
	}
	
	public boolean addAll(int number) {
		currNode = new Node8(1);
		Node8 startNode = currNode;
		
		for(int i = 2; i <= number; i++) {
			Node8 newNode = new Node8(i);
			currNode.setNextNode(newNode);
			newNode.setPreNode(currNode);
			currNode = newNode;
		}
		
		currNode.setNextNode(startNode);
		startNode.setPreNode(currNode);
		
		this.size = number;
		return true;
	}
	public int pop() {
		for(int i = 0; i < width; i++) {
			currNode = currNode.getNextNode();
		}
		
		int result = currNode.getValue();
		
		Node8 preNode = currNode.getPreNode();
		Node8 nextNode = currNode.getNextNode();
		preNode.setNextNode(nextNode);
		nextNode.setPreNode(preNode);
		currNode = preNode;
		
		size--;
		return result;
	}
	
	public boolean setWidth(int width) {
		this.width = width;
		return true;
	}
	public Integer getWidth() {
		return this.width;
	}
	
	public int size() {
		return this.size;
	}
	
	public void clear() {
		this.currNode = null;
		this.width = null;
		this.size = 0;
	}
}

class Node8{
	Integer value;
	Node8 preNode;
	Node8 nextNode;
	
	public Node8(){
		
	}
	public Node8(Integer value) {
		this.value = value;
	}
	
	public Integer getValue() {
		return this.value;
	}
	public boolean setValue(Integer value) {
		if(value == null)
			return false;
		else {
			this.value = value;
			return true;
		}
	}
	
	public Node8 getPreNode() {
		return this.preNode;
	}
	public boolean setPreNode(Node8 preNode) {
		if(preNode == null)
			return false;
		this.preNode = preNode;
		return true;
	}
	
	public Node8 getNextNode() {
		return this.nextNode;
	}
	public boolean setNextNode(Node8 nextNode) {
		if(nextNode == null)
			return false;
		
		this.nextNode = nextNode;
		return true;
	}
}
