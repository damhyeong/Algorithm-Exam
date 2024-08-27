import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int n = Integer.parseInt(br.readLine());
        
        // n 만큼의 int 배열 메모리 생성 
        int[] arr = new int[n];
        
        // " " 델림을 사용하여 각 단어별 토큰 분리해주는 클래스
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        for(int i = 0; i < arr.length; i++)
            arr[i] = Integer.parseInt(st.nextToken());
        
        int v = Integer.parseInt(br.readLine());
        
        // 개수를 셀 result 변수 선언 
        int result = 0;
        
        for(int i = 0; i < arr.length; i++)
            result = (arr[i] == v) ? result + 1 : result;
        
        System.out.println(result);
    }
}
