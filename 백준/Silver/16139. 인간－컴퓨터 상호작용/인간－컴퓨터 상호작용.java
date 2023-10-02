
import java.util.*;
import java.io.*;

/**
인간-컴퓨터 상호작용 서브태스크
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초 (추가 시간 없음)	256 MB	18468	4952	3965	28.736%

문제
승재는 인간-컴퓨터 상호작용에서 생체공학 설계를 공부하다가 키보드 자판이 실용적인지 궁금해졌다. 
이를 알아보기 위해 승재는 다음과 같은 생각을 했다. 

'문자열에서 특정 알파벳이 몇 번 나타나는지 알아봐서 
자주 나타나는 알파벳이 중지나 검지 위치에 오는 알파벳인지 확인하면 실용적인지 확인할 수 있을 것이다.'

승재를 도와 특정 문자열 
S, 특정 알파벳 
a 와 문자열의 구간 
[l,r]이 주어지면 
S의 l번째 문자부터 r번째 문자 사이에 a 가 몇 번 나타나는지 구하는 프로그램을 작성하여라. 
승재는 문자열의 문자는 0번째부터 세며, l번째와 r번째 문자를 포함해서 생각한다. 
주의할 점은 승재는 호기심이 많기에 (통계적으로 크게 무의미하지만) 같은 문자열을 두고 질문을 q번 할 것이다.

입력
첫 줄에 문자열 S가 주어진다. 
문자열의 길이는 200,000자 이하이며 알파벳 소문자로만 구성되었다. 
두 번째 줄에는 질문의 수 q가 주어지며, 문제의 수는 1 <= q <= 200,000을 만족한다. 
세 번째 줄부터 (q+2)번째 줄에는 질문이 주어진다. 
각 질문은 알파벳 소문자 ai와 0 <= li <= ri < |S|를 만족하는 정수 li, ri가 공백으로 구분되어 주어진다.

출력
각 질문마다 줄을 구분해 순서대로 답변한다. 
i번째 줄에 S의 li번째 문자부터 ri번째 문자 사이에 ai가 나타나는 횟수를 출력한다.

서브태스크 1 (50점)
문자열의 길이는 
2,000자 이하, 질문의 수는 
2,000개 이하이다.

서브태스크 2 (50점)
추가 제한 조건이 없다.

예제 입력 1 
seungjaehwang
4
a 0 5
a 0 6
a 6 10
a 7 10
예제 출력 1 
0
1
2
1
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		String word = br.readLine();
		
		int[][] alphaCount = new int['z' - 'a' + 1][word.length()];
		
		for(int i = 0; i < alphaCount.length; i++) {
			char ch = (char)(i + 'a');
			int count = 0;
			for(int j = 0; j < word.length(); j++) {
				char newCh = word.charAt(j);
				if(newCh == ch)
					count++;
				alphaCount[i][j] = count;
			}
		}
		
		int q = Integer.parseInt(br.readLine());
		for(int i = 0; i < q; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			char ch = st.nextToken().charAt(0);
			int index1 = Integer.parseInt(st.nextToken());
			int index2 = Integer.parseInt(st.nextToken());
			
			
			int num = -1;
			if(index1 == 0) {
				num = alphaCount[ch - 'a'][index2];
			}else
				num = alphaCount[ch - 'a'][index2] - alphaCount[ch - 'a'][index1 - 1];
			bw.write(Integer.toString(num) + "\n");
			
		}
		bw.flush();
		bw.close();
		br.close();
	}

}
