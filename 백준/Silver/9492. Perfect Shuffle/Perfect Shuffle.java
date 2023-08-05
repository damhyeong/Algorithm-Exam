import java.util.*;
import java.io.*;

/**
Tricknology
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	1024 MB	186	87	70	59.829%
문제
다음 쿼리를 수행하는 프로그램을 작성하시오.

 
$L\ R$: 
$L \leq x < y \leq R$을 만족하는 정수 
$x$, 
$y$에 대하여, 
$x \leq k \leq y$를 만족하는 모든 자연수 
$k$의 합이 소수가 되게 하는 모든 정수 쌍 
$(x, \:y)$의 개수를 출력한다.
입력
첫째 줄에 쿼리의 개수 
$Q$가 주어진다. 
$(1 \leq Q \leq 500\ 000)$ 

다음 
$Q$개의 줄에는 각각의 쿼리를 나타내는 양의 정수 
$L$, 
$R$이 주어진다. 
$(2 \leq L < R \leq 500 \ 000)$ 

출력
각각의 쿼리마다 한 줄에 하나씩 정답을 출력한다.

예제 입력 1 
4
2 4
3 8
7 12
9 21
예제 출력 1 
2
3
3
6
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		String s = "";
		while(!(s = br.readLine()).equals("0")) {
			int T = Integer.parseInt(s);
			String[] cards = new String[T];
			for(int i = 0; i < T; i++) {
				cards[i] = br.readLine();
			}
			String[] newCards = new String[T];
			int halfNum = 0;
			if(T % 2 == 0)
				halfNum = T / 2;
			else
				halfNum = T / 2 + 1;
			int index = 0;
			for(int i = 0; i < T; i++) {
				if(i % 2 == 0)
					newCards[i] = cards[index++];
				else
					newCards[i] = cards[halfNum++];
			}
			for(int i = 0; i < newCards.length; i++) {
				bw.write(newCards[i] + "\n");
			}
		}
		
		bw.flush();
		bw.close();
		br.close();
	}
	
}
