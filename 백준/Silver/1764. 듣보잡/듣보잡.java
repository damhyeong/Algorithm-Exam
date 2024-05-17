import java.util.*;
import java.io.*;

/**
듣보잡
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	256 MB	109516	47186	36744	41.313%
문제
김진영이 듣도 못한 사람의 명단과, 
보도 못한 사람의 명단이 주어질 때, 

듣도 보도 못한 사람의 명단을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 듣도 못한 사람의 수 N, 보도 못한 사람의 수 M이 주어진다. 

이어서 둘째 줄부터 N개의 줄에 걸쳐 듣도 못한 사람의 이름과, N+2째 줄부터 보도 못한 사람의 이름이 순서대로 주어진다. 

이름은 띄어쓰기 없이 알파벳 소문자로만 이루어지며, 그 길이는 20 이하이다. 

N, M은 500,000 이하의 자연수이다.

듣도 못한 사람의 명단에는 중복되는 이름이 없으며, 보도 못한 사람의 명단도 마찬가지이다.

출력
듣보잡의 수와 그 명단을 사전순으로 출력한다.

예제 입력 1 
3 4
ohhenrie
charlie
baesangwook
obama
baesangwook
ohhenrie
clinton
예제 출력 1 
2
baesangwook
ohhenrie
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken()); int M = Integer.parseInt(st.nextToken());
		
		Set<String> inputSet = new HashSet<>();
		Set<String> resultSet = new HashSet<>();
		
		for(int i = 0; i < N; i++)
			inputSet.add(br.readLine().trim());
		
		int count = 0;
		for(int i = 0; i < M; i++) {
			String findSomeone = br.readLine().trim();
			
			if(inputSet.contains(findSomeone)) {
				resultSet.add(findSomeone);
				count++;
			}
		}
		
		String[] strArr = resultSet.toArray(new String[0]);
		
		StringBuilder sb = new StringBuilder();
		
		Arrays.sort(strArr);
		
		sb.append(count); sb.append("\n");
		
		for(int i = 0; i < strArr.length; i++)
			sb.append(strArr[i] + "\n");
		
		System.out.println(sb.toString());
	}

}