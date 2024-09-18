import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
       BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
       
       String str = br.readLine();
       
       boolean isPalindrome = true;
       
       for(int i = 0, j = str.length() - 1; i <= j; i++, j--) {
          char ch1 = str.charAt(i);
          char ch2 = str.charAt(j);
          
          if(ch1 != ch2) {
              isPalindrome = false;
              break;
          }
       }
       
       if(isPalindrome)
          System.out.println(1);
       else 
          System.out.println(0);
    }
}