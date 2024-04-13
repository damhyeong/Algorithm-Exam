import java.io.*;
import java.util.Arrays;

/**
단어 공부

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	287782	114899	90612	39.725%

문제
알파벳 대소문자로 된 단어가 주어지면, 이 단어에서 가장 많이 사용된 알파벳이 무엇인지 알아내는 프로그램을 작성하시오. 
단, 대문자와 소문자를 구분하지 않는다.

입력
첫째 줄에 알파벳 대소문자로 이루어진 단어가 주어진다. 
주어지는 단어의 길이는 1,000,000을 넘지 않는다.

출력
첫째 줄에 이 단어에서 가장 많이 사용된 알파벳을 대문자로 출력한다. 
단, 가장 많이 사용된 알파벳이 여러 개 존재하는 경우에는 ?를 출력한다.

예제 입력 1 
Mississipi
예제 출력 1 
?
예제 입력 2 
zZa
예제 출력 2 
Z
예제 입력 3 
z
예제 출력 3 
Z
예제 입력 4 
baaa
예제 출력 4 
A
 */

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String str = br.readLine().trim();
		
		int[] alphabet = new int['Z' - 'A' + 1]; // List<ArrayList<Integer>> list = new ArrayList<>(); 로도 가능하다.
		
		Arrays.fill(alphabet, 0); // alphabet 배열은 냅둬도 0으로 초기화 되어있다. - 연습삼아 한 것.
		
		for(int i = 0; i < str.length(); i++) {
			char ch = str.charAt(i);
			
			if('A' <= ch && ch <= 'Z') { // 대문자일 경우 
				alphabet[ch - 'A']++;
			} else if('a' <= ch && ch <= 'z') { // 소문자일 경우 
				alphabet[ch - 'a']++;
			}
		}
		
		// 가장 많이 나온 단어 구하기
		int max = -1;
		int maxIndex = -1; // maxIndex + 'A' 가 가장 많이 나온 단어. 
		for(int i = 0; i < alphabet.length; i++) {
			if(max <= alphabet[i]) {
				max = alphabet[i];
				maxIndex = i;
			} 
		}
		
		int count = 0;
		for(int i = 0; i < alphabet.length; i++) {
			if(alphabet[i] == max)
				count++;
		}
		
		StringBuilder sb = new StringBuilder();
		if(count > 1) { // 가장 많이 나온 단어가 1개 이상이다. - 다중이다.
			sb.append("?");
		} else {
			char answer = (char)(maxIndex + 'A');
			sb.append(answer);
		}
		
		System.out.println(sb.toString());
	}

}
