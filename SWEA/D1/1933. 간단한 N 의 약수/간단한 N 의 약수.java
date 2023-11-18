
import java.util.*;
import java.io.*;

/**
입력으로 1개의 정수 N 이 주어진다.

정수 N 의 약수를 오름차순으로 출력하는 프로그램을 작성하라.
 

[제약사항]

N은 1이상 1,000이하의 정수이다. (1 ≤ N ≤ 1,000)
 

[입력]

입력으로 정수 N 이 주어진다.


[출력]

정수 N 의 모든 약수를 오름차순으로 출력한다.

입력
10
input.txt
출력
1 2 5 10
output.txt
 */

public class Solution {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		int N = Integer.parseInt(br.readLine().trim());
		
		for(int i = 1; i <= N; i++)
			if(N % i == 0)
				bw.write(Integer.toString(i) + " ");
		bw.flush();
	}

}
