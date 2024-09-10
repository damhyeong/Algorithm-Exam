import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
       BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
       // 문자들의 첫 번째 수를 담을 배열 생성 
       int[] arr = new int['z' - 'a' + 1];
       
       // 반복문 말고도 이러한 방식을 사용 할 수 있다.
       // 단순 배열에 대한 편의성 객체를 이용하여 내부의 값을 채움.
       Arrays.fill(arr, -1);
       
       String str = br.readLine();
       
       for(int i = 0; i < str.length(); i++) {
          char ch = str.charAt(i);
          
          /**
           만약 현재 문자 순서가 삽입되었다면, 값을 변경하지 않으며,
           현재 문자의 순서가 -1 로 삽입 된 적이 없다면, 현재의 인덱스로 변경한다.
           */
          arr[ch - 'a'] = arr[ch - 'a'] == -1 ? i : arr[ch - 'a'];
       }
       
       // System.out.print() 사용해도 되지만, StringBuilder 로 더 깔끔하게 만들 수 있다.
       StringBuilder sb = new StringBuilder();
       for(int i = 0; i < arr.length; i++)
          sb.append(arr[i]).append(" ");
       
       System.out.println(sb.toString());
    }
}