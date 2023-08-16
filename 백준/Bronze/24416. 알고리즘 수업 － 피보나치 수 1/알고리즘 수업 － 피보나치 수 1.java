
import java.util.*;
import java.io.*;

/**
알고리즘 수업 - 피보나치 수 1
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	512 MB	14783	8568	7597	59.217%
문제
오늘도 서준이는 동적 프로그래밍 수업 조교를 하고 있다. 아빠가 수업한 내용을 학생들이 잘 이해했는지 문제를 통해서 확인해보자.

오늘은 n의 피보나치 수를 재귀호출과 동적 프로그래밍으로 구하는 알고리즘을 배웠다. 재귀호출에 비해 동적 프로그래밍이 얼마나 빠른지 확인해 보자. 아래 의사 코드를 이용하여 n의 피보나치 수를 구할 경우 코드1 코드2 실행 횟수를 출력하자.

피보나치 수 재귀호출 의사 코드는 다음과 같다.

fib(n) {
    if (n = 1 or n = 2)
    then return 1;  # 코드1
    else return (fib(n - 1) + fib(n - 2));
}
피보나치 수 동적 프로그래밍 의사 코드는 다음과 같다.

fibonacci(n) {
    f[1] <- f[2] <- 1;
    for i <- 3 to n
        f[i] <- f[i - 1] + f[i - 2];  # 코드2
    return f[n];
}
입력
첫째 줄에 n(5 ≤ n ≤ 40)이 주어진다.

출력
코드1 코드2 실행 횟수를 한 줄에 출력한다.

예제 입력 1 
5
예제 출력 1 
5 3
예제 입력 2 
30
예제 출력 2 
832040 28
 */

public class Main {
	public static int n;
	public static int callRecursive = 0;
	public static int callDanamic = 0;
	public static int[] fibonachi;
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		n = Integer.parseInt(br.readLine());
		fibonachi = new int[n];
		
		int recurFibo = recursive(n);
		danamic(n);
		bw.write(Integer.toString(callRecursive) + " " + Integer.toString(callDanamic));
		bw.flush();
		bw.close();
		br.close();
	}
	public static int recursive(int deep) {
		if(deep == 1 || deep == 2) {
			callRecursive++;
			return 1;
		} else {
			return recursive(deep - 1) + recursive(deep - 2);
		}
	}
	public static void danamic(int n) {
		fibonachi[0] = 1;
		fibonachi[1] = 1;
		for(int i = 2; i < n; i++) {
			callDanamic++;
			fibonachi[i] = fibonachi[i - 1] + fibonachi[i - 2];
		}
	}
}
