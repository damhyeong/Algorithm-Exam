
import java.util.*;
import java.io.*;

/**
주어진 숫자부터 0까지 순서대로 찍어보세요

아래는 입력된 숫자가 N일 때 거꾸로 출력하는 예시입니다

입력
8
SampleInput.txt

출력
8 7 6 5 4 3 2 1 0
SampleOutput.txt
 */

public class Solution {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		int N = Integer.parseInt(br.readLine().trim());
		for(int i = N; i >= 0; i--)
			bw.write(Integer.toString(i) + " ");
		bw.flush();
		br.close();
		bw.close();
	}

}
