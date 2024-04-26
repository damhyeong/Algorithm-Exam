import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int[] countNum = new int[10001];
		
		int N = Integer.parseInt(br.readLine());
		
		while(N-- > 0) {
			countNum[Integer.parseInt(br.readLine())]++;
		}
		
		StringBuilder sb = new StringBuilder();
		for(int i = 1; i <= 10_000; i++) {
			if(countNum[i] != 0) {
				int len = countNum[i];
				for(int j = 0; j < len; j++)
					sb.append(i + "\n");
			}
		}
		
		System.out.println(sb.toString());
			
	}

}
