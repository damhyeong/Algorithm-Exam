
import java.util.*;
import java.io.*;

public class Main {
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken()); 
		int K = Integer.parseInt(st.nextToken());
		MGClass mg = new MGClass(N, K);
		
		mg.read(N, br, st);
		mg.merge_sort(0, N - 1);
		if(mg.getCnt() < K) {
			bw.write("-1\n");
			bw.flush();
		}
		br.close();
		bw.close();
	}
	
}

class MGClass{
	public int cnt = 0;
	public int K;
	public int[] A;
	public int[] tmp;
	public MGClass(int N, int K){
		this.K = K;
		A = new int[N];
		tmp = new int[N];
	}
	public int getCnt() {
		return this.cnt;
	}
	
	public void read(int N, BufferedReader br, StringTokenizer st) throws IOException {
		int i = 0;
		st = new StringTokenizer(br.readLine());
		while(st.hasMoreTokens()) {
			// 총 N번 받게 되는데, NoSuchElement 오류가 나서 st.hasMoreToken형식의 while 사용 
			this.A[i++] = Integer.parseInt(st.nextToken());
		}
	}
	
	public void merge_sort(int f, int l) {
		if(f < l) {
			int middle = (f + l) / 2;
			this.merge_sort(f, middle);
			this.merge_sort(middle + 1, l);
			this.merge(f, middle, l);
		} 
	}
	public void merge(int p, int q, int r) {
		int i = p; int j = q + 1; int t = 0;
		while(i <= q && j <= r) {
			if(this.A[i] <= this.A[j]) {
				this.tmp[t++] = this.A[i++]; // tmp[t] = A[i]; t++; i++;
			}
			else {
				this.tmp[t++] = this.A[j++]; // tmp[t] = A[i]; t++; i++;
			}
		}
		while(i <= q) // 왼쪽 배열 부분이 남은 경우 
		{
			this.tmp[t++] = this.A[i++];
		}
		while(j <= r) // 오른쪽 배열 부분이 남은 경우 
		{
			this.tmp[t++] = this.A[j++];
		}
		i = p; t = 0;
		while(i <= r) {
			this.A[i++] = this.tmp[t++];
			this.cnt++;
			if(this.cnt == this.K) {
				System.out.println(this.A[i - 1]);
				break;
			}
		}
	}
}
