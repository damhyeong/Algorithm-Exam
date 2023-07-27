
import java.util.*;
import java.io.*;

/**
문제
오늘도 서준이는 알고리즘의 수행시간 수업 조교를 하고 있다. 아빠가 수업한 내용을 학생들이 잘 이해했는지 문제를 통해서 확인해보자.

입력의 크기 n이 주어지면 MenOfPassion 알고리즘 수행 시간을 예제 출력과 같은 방식으로 출력해보자.

MenOfPassion 알고리즘은 다음과 같다.

MenOfPassion(A[], n) {
    sum <- 0;
    for i <- 1 to n - 1
        for j <- i + 1 to n
            sum <- sum + A[i] × A[j]; # 코드1
    return sum;
}
입력
첫째 줄에 입력의 크기 n(1 ≤ n ≤ 500,000)이 주어진다.

출력
첫째 줄에 코드1 의 수행 횟수를 출력한다.

둘째 줄에 코드1의 수행 횟수를 다항식으로 나타내었을 때, 최고차항의 차수를 출력한다. 단, 다항식으로 나타낼 수 없거나 최고차항의 차수가 3보다 크면 4를 출력한다.

예제 입력 1 
7
예제 출력 1 
21
2

개인적 해석 : 
	* i의 반복 회수는 들어온 n - 1이다.
	* j의 반복 회수는 처음 n - 1부터 시작해 1까지 내려간다.
	* 즉, 입력 값이 7일 때, 6 + 5 + 4 + 3 + 2 + 1이 답이 된다.
	* 하지만, 이중 중첩 반복문이기에 최고 차수는 2가 된다.
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		long n = Integer.parseInt(br.readLine());
		
		Long sum = (long)0;
		for(int i = 1; i <= n - 1; i++) {
			sum += i;
		}
		StringBuilder sb = new StringBuilder();
		sb.append(sum.toString() + "\n" + 2);
		System.out.println(sb);
	}

}
