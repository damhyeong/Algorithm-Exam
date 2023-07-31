
import java.util.*;
import java.io.*;

/**
문제
두 자연수 A와 B에 대해서, A의 배수이면서 B의 배수인 자연수를 A와 B의 공배수라고 한다. 
이런 공배수 중에서 가장 작은 수를 최소공배수라고 한다. 
예를 들어, 6과 15의 공배수는 30, 60, 90등이 있으며, 최소 공배수는 30이다.

두 자연수 A와 B가 주어졌을 때, A와 B의 최소공배수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 테스트 케이스의 개수 T(1 ≤ T ≤ 1,000)가 주어진다. 
둘째 줄부터 T개의 줄에 걸쳐서 A와 B가 주어진다. (1 ≤ A, B ≤ 45,000)

출력
첫째 줄부터 T개의 줄에 A와 B의 최소공배수를 입력받은 순서대로 한 줄에 하나씩 출력한다.

예제 입력 1 
3
1 45000
6 10
13 17
예제 출력 1 
45000
30
221
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int T = Integer.parseInt(br.readLine());
		
		StringTokenizer st;
		
		while(T --> 0) {
			st = new StringTokenizer(br.readLine());
			int A = Integer.parseInt(st.nextToken());
			int B = Integer.parseInt(st.nextToken());
			
			// 최대 공약수를 구하기 위한 수이다.
			int shareMax = -1;
			
			int smallerNum = A >= B ? B : A;
			
			// 두 수 중 하나가 1이라면 큰 수를 출력. 어짜피 큰 수가 최소 공배수이므로. 
			if(smallerNum == 1) {
				bw.write(Integer.toString(A >= B ? A : B) + "\n");
				continue;
			} else if ((A - B) == 1 || (B - A) == 1) {
				bw.write(Integer.toString(A * B) + "\n");
				continue;
			}
			
			// 두 수의 최대 공약수를 구한다. 
			for(int i = smallerNum; i >= 2; i--) {
				if(A % i == 0 && B % i == 0) {
					shareMax = i;
					break;
				}
			}
			
			// 최대 공약수가 구해지지 않았다면, 두 수를 곱한 수가 최소 공배수가 된다. ex - 13, 17 
			if(shareMax == -1) {
				bw.write(Integer.toString(A * B) + "\n");
				continue;
			}
			
			// 최소 공배수를 구할 때 까지, 최대 공약수를 더한다. 
			int multiMin = B / shareMax * A;
			bw.write(Integer.toString(multiMin) + "\n");
		}
		bw.flush();
		
		bw.close();
		br.close();
	}

}
