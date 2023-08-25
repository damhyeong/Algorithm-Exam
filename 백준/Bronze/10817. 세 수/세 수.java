import java.util.*;
import java.io.*;


public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        int[] number = new int[3];
        for(int i = 0; i < 3; i++){
            number[i] = Integer.parseInt(st.nextToken());
        }
        
        boolean[] largest = new boolean[3];
        int maxIndex = 0;
        for(int i = maxIndex; i < 3; i++){
            if(number[maxIndex] <= number[i])
                maxIndex = i;
        }
        
        int max = -1;
        for(int i = 0; i < 3; i++){
            if(i == maxIndex)
                continue;
            if(number[i] >= max)
                max = number[i];
        }
        for(int i = 0; i < 3; i++){
            if(number[i] == max){
                bw.write(Integer.toString(number[i]));
                break;
            }
        }
        bw.flush();
        bw.close();
        br.close();
	}
	
}