
import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int N = Integer.parseInt(br.readLine());
		
		boolean[] isStack = new boolean[N];
		StringTokenizer st = new StringTokenizer(br.readLine());
		for(int i = 0; i < N; i++) {
			int n = Integer.parseInt(st.nextToken());
			if(n == 0) {
				isStack[i] = false;
			} else {
				isStack[i] = true;
			}
		}
		
		LinkedList<Integer> isQueList = new LinkedList<>();
		st = new StringTokenizer(br.readLine());
		for(int i = 0; i < N; i++) {
			int sourceNum = Integer.parseInt(st.nextToken());
			if(!isStack[i])
				isQueList.add(sourceNum);

		}
		
		int M = Integer.parseInt(br.readLine());
		st = new StringTokenizer(br.readLine());
		for(int i = 0; i < M; i++) {
			int insertNum = Integer.parseInt(st.nextToken());
			
			if(isQueList.isEmpty()) {
				bw.write(Integer.toString(insertNum) + " ");
				continue;
			}
			
			isQueList.addFirst(insertNum);
			int resultNum = isQueList.removeLast();
			
			bw.write(Integer.toString(resultNum) + " ");
		}
		bw.flush();
		bw.close();
		br.close();
	}

}
