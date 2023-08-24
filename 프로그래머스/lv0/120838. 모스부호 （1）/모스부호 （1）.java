import java.util.*;
import java.io.*;

class Solution {
    public String solution(String letter) {
        String answer = "";
        
        String[] morse = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", 
                         "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                         ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
        
        StringTokenizer st = new StringTokenizer(letter);
        while(st.hasMoreTokens()){
            String m = st.nextToken();
            for(int i = 0; i < morse.length; i++){
                if(m.equals(morse[i])){
                    answer += (char)('a' + i);
                }
            }
        }
        
        return answer;
    }
}