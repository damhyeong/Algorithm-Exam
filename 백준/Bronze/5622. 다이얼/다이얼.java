import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        // 할머니가 외운 알파벳을 입력받는다. 
        String strNumber = br.readLine();
        
        int totalTime = 0;
        
        for(int i = 0; i < strNumber.length(); i++) {
            char ch = strNumber.charAt(i);
            totalTime += chToTime(ch);
        }
        System.out.println(totalTime);
        
    }
    
    public static int chToTime(char ch){
        switch (ch) {
            case 'A': case 'B': case 'C':
                return 3;
            case 'D': case 'E': case 'F':
                return 4;
            case 'G': case 'H': case 'I':
                return 5;
            case 'J': case 'K': case 'L':
                return 6;
            case 'M': case 'N': case 'O':
                return 7;
            case 'P': case 'Q': case 'R': case 'S':
                return 8;
            case 'T': case 'U': case 'V':
                return 9;
            case 'W': case 'X': case 'Y': case 'Z':
                return 10;
            default:
                return -1;
        }
    }
}