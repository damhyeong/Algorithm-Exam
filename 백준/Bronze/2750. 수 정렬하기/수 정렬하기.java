import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        // N 번 만큼의 수가 주어진다.
        int N = Integer.parseInt(br.readLine());
        
        // N 번의 수를 담을 배열을 생성.
        int[] arr = new int[N];
        
        // while(N-- > 0) 을 사용해도 상관은 없음. - 인덱스가 중요하지 않은 부분.
        for(int i = 0; i < N; i++) 
            arr[i] = Integer.parseInt(br.readLine());
        
        // Arrays 유틸 메서드를 통한 
        Arrays.sort(arr);
        
        // 결과값을 저장하기 위한 빌더 - 사실 String 객체에서 유틸성이 굉장히 올라가는 클래스
        StringBuilder sb = new StringBuilder();
        
        for(int i = 0; i < arr.length; i++)
            sb.append(arr[i]).append("\n");
        
        System.out.println(sb.toString());
    }
}