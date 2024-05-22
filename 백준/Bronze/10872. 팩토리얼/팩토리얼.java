import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		long N = Integer.parseInt(br.readLine());
		
		long result = 1;
		for(long i = 1; i <= N; i++) {
			result *= i;
		}
		
		System.out.println(result);
	}

}
