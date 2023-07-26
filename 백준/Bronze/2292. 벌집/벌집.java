
import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		
		int line = 1; 
		int lastNum = 1;
		
		
		while(n > lastNum) {
			lastNum += line * 6;
			line++;
		}
		
		System.out.println(line);
	}

}
