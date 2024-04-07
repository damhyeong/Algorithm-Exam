
import java.util.*;
import java.io.*;

/**
영수증

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	1024 MB	125983	69658	61859	56.043%

문제

영수증에 적힌,

구매한 각 물건의 가격과 개수
구매한 물건들의 총 금액
을 보고, 구매한 물건의 가격과 개수로 계산한 총 금액이 영수증에 적힌 총 금액과 일치하는지 검사해보자.

입력
첫째 줄에는 영수증에 적힌 총 금액 
$X$가 주어진다.

둘째 줄에는 영수증에 적힌 구매한 물건의 종류의 수 
$N$이 주어진다.

이후 
$N$개의 줄에는 각 물건의 가격 
$a$와 개수 
$b$가 공백을 사이에 두고 주어진다.

출력
구매한 물건의 가격과 개수로 계산한 총 금액이 영수증에 적힌 총 금액과 일치하면 Yes를 출력한다. 일치하지 않는다면 No를 출력한다.

제한
 
$1 ≤ X ≤ 1\,000\,000\,000$ 
 
$1 ≤ N ≤ 100$ 
 
$1 ≤ a ≤ 1\,000\,000$ 
 
$1 ≤ b ≤ 10$ 
예제 입력 1 
260000
4
20000 5
30000 2
10000 6
5000 8
예제 출력 1 
Yes
영수증에 적힌 구매할 물건들의 목록으로 계산한 총 금액은 20000 × 5 + 30000 × 2 + 10000 × 6 + 5000 × 8 = 260000원이다. 이는 영수증에 적힌 총 금액인 260000원과 일치한다. 

예제 입력 2 
250000
4
20000 5
30000 2
10000 6
5000 8
예제 출력 2 
No
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int totalPrice = Integer.parseInt(br.readLine());
		
		int loop = Integer.parseInt(br.readLine());
		
		int newPrice = 0;
		
		while(loop-- > 0) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int price = Integer.parseInt(st.nextToken());
			int n = Integer.parseInt(st.nextToken());
			newPrice += price * n;
		}
		
		if(totalPrice == newPrice)
			System.out.println("Yes");
		else
			System.out.println("No");
	}

}
