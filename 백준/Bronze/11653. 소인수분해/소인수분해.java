import java.util.*;
import java.io.*;

/**
소인수분해

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	112169	61479	47681	53.386%

문제
정수 N이 주어졌을 때, 소인수분해하는 프로그램을 작성하시오.

입력
첫째 줄에 정수 N (1 ≤ N ≤ 10,000,000)이 주어진다.

출력
N의 소인수분해 결과를 한 줄에 하나씩 오름차순으로 출력한다. 
N이 1인 경우 아무것도 출력하지 않는다.

예제 입력 1 
72
예제 출력 1 
2
2
2
3
3
예제 입력 2 
3
예제 출력 2 
3
예제 입력 3 
6
예제 출력 3 
2
3
예제 입력 4 
2
예제 출력 4 
2
예제 입력 5 
9991
예제 출력 5 
97
103
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int originNum = Integer.parseInt(br.readLine());
		
		
		if(originNum == 1) { // 소인수분해 하는 수가 1일 경우, 아무것도 출력하지 않는다.
			
		} else {
			StringBuilder sb = new StringBuilder();
			while(originNum != 1) { 
				
				int index = 2;
				while(index <= originNum) {
					if(originNum % index == 0) { // 낮은 수로 소인수분해가 된다면,
						sb.append(index); sb.append("\n");
						originNum /= index;
						break;
					}
					index++;
				}
			}
			
			System.out.println(sb.toString());
		}
	}

}
