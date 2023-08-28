
import java.util.*;
import java.io.*;

/**
집합 언어 제한
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1.5 초	4 MB (하단 참고)	87854	26372	19265	29.255%

예제 입력 1 
26
add 1
add 2
check 1
check 2
check 3
remove 2
check 1
check 2
toggle 3
check 1
check 2
check 3
check 4
all
check 10
check 20
toggle 10
remove 20
check 10
check 20
empty
check 1
toggle 1
check 1
toggle 1
check 1
예제 출력 1 
1
1
0
1
0
1
0
1
0
1
1
0
0
0
1
0

문제
비어있는 공집합 S가 주어졌을 때, 아래 연산을 수행하는 프로그램을 작성하시오.

add x: S에 x를 추가한다. (1 ≤ x ≤ 20) S에 x가 이미 있는 경우에는 연산을 무시한다.
remove x: S에서 x를 제거한다. (1 ≤ x ≤ 20) S에 x가 없는 경우에는 연산을 무시한다.
check x: S에 x가 있으면 1을, 없으면 0을 출력한다. (1 ≤ x ≤ 20)
toggle x: S에 x가 있으면 x를 제거하고, 없으면 x를 추가한다. (1 ≤ x ≤ 20)
all: S를 {1, 2, ..., 20} 으로 바꾼다.
empty: S를 공집합으로 바꾼다.
입력
첫째 줄에 수행해야 하는 연산의 수 M (1 ≤ M ≤ 3,000,000)이 주어진다.

둘째 줄부터 M개의 줄에 수행해야 하는 연산이 한 줄에 하나씩 주어진다.

출력
check 연산이 주어질때마다, 결과를 출력한다.

 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int M = Integer.parseInt(br.readLine());
		
		// 1 <= x <= 20
		boolean[] set = new boolean[21];
		StringTokenizer st;
		while(M --> 0) {
			st = new StringTokenizer(br.readLine());
			String command = st.nextToken();
			
			if(command.equals("add")) {
				int num = Integer.parseInt(st.nextToken());
				set[num] = true;
			} else if (command.equals("remove")) {
				int num = Integer.parseInt(st.nextToken());
				set[num] = false;
			} else if (command.equals("check")) {
				int num = Integer.parseInt(st.nextToken());
				if(set[num])
					bw.write("1\n");
				else
					bw.write("0\n");
			} else if (command.equals("toggle")) {
				int num = Integer.parseInt(st.nextToken());
				set[num] = !set[num];
			} else if (command.equals("all")) {
				for(int i = 1; i <= 20; i++)
					set[i] = true;
			} else if (command.equals("empty")) {
				set = new boolean[21];
			}
		}
		bw.flush();
		bw.close();
		br.close();
	}

}
