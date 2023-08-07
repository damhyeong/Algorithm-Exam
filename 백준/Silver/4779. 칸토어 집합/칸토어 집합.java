
import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		String s = "";
		while((s = br.readLine()) != null) {
			int N = Integer.parseInt(s);
			char[] str;
			if(N == 0) {
				str = new char[1];
				str[0] = '-';
			}
			else {
				int n = 1;
				for(int i = 0; i < N; i++) {
					n *= 3;
				}
				str = new char[n];
				for(int i = 0; i < n; i++) {
					str[i] = '-';
				}
			}
			//String newStr = kanto(str);
			bw.write(kanto(new String(str)) + "\n");
			bw.flush();
		}
		bw.close();
		br.close();
	}
	public static String kanto(String str) {
		char[] chStr = str.toCharArray();
		if(str.length() == 1)
			return "-";
		else {
			int fIndex = str.length() / 3;
			int lIndex = str.length() / 3 * 2;
			for(int i = fIndex; i < lIndex; i++) {
				chStr[i] = ' ';
			}
			str = new String(chStr);
			
			return kanto(str.substring(0, fIndex)) 
					+ str.substring(fIndex, lIndex)
					+ kanto(str.substring(lIndex, str.length()));
		}
	}
}
