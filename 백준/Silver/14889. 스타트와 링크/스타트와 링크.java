
import java.util.*;
import java.io.*;

public class Main {
	public static int N;
	public static boolean[] isSelected;
	public static int diffMin;
	public static boolean isFirst = true;
	public static int[][] ability;
	public static int[] sTeam;
	public static int[] lTeam;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		N = Integer.parseInt(br.readLine());
		isSelected = new boolean[N];
		
		ability = new int[N][N];
		sTeam = new int[N / 2];
		lTeam = new int[N / 2];
		
		for(int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for(int j = 0; j < N; j++) {
				ability[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		divTeam(0, 0);
		
		bw.write(Integer.toString(diffMin));
		bw.flush();
		bw.close();
		br.close();
	}
	
	public static void divTeam(int index, int deep) {
		if(deep == N / 2) {
			getDiff();
			return;
		}
		
		for(int i = index; i < N; i++) {
			if(isSelected[i])
				continue;
			else {
				isSelected[i] = true;
				
				divTeam(i + 1, deep + 1);
				isSelected[i] = false;
			}
		}
	}
	
	public static void getDiff() {
		int sTeamAbil = 0;
		int lTeamAbil = 0;
		int sIndex = 0;
		int lIndex = 0;
		
		for(int i = 0; i < isSelected.length; i++) {
			if(isSelected[i]) {
				sTeam[sIndex] = i;
				sIndex++;
			} else {
				lTeam[lIndex] = i;
				lIndex++;
			}
		}
		
		
		for(int i = 0; i < (N / 2) - 1; i++) {
			for(int j = i + 1; j < N / 2 ; j++) {
				sTeamAbil += ability[sTeam[i]][sTeam[j]] + ability[sTeam[j]][sTeam[i]];
				lTeamAbil += ability[lTeam[i]][lTeam[j]] + ability[lTeam[j]][lTeam[i]];
			}
		}
		
		int diff = Math.abs(sTeamAbil - lTeamAbil);
		
		if(isFirst) {
			diffMin = diff;
			isFirst = false;
		} else {
			diffMin = (diffMin >= diff) ? diff : diffMin;
		}
		if(diffMin == 0) {
			System.out.println("0");
			System.exit(0);
		}
	}
}
