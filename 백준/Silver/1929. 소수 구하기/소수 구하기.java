import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int M = Integer.parseInt(st.nextToken()); int N = Integer.parseInt(st.nextToken());
		
		StringBuilder sb = new StringBuilder();
		for(int i = M; i <= N; i++) {
			boolean isPrime = checkPrime(i);
			
			if(isPrime)
				sb.append(i).append("\n");
		}
		
		System.out.println(sb.toString());
	}
	
	public static boolean checkPrime(int num) {
		if(num == 1)
			return false;
		if(num == 2 || num == 3)
			return true;
		
		boolean isPrime = true;
		for(int i = 2; i * i <= num; i++) {
			if(num % i == 0) {
				isPrime = false;
				break;
			}
		}
		
		return isPrime;
	}
}
