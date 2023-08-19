import java.util.*;
import java.io.*;

class Solution {
    public int[] solution(int n, String[] words) {
        int[] answer = new int[2];

        int cnt = 0;
        
        String str = words[0];
        
        boolean isBreak = false;
        
        for(int i = 1; i < words.length; i++){
            for(int j = 0; j < i; j++){
                if(words[i].equals(words[j])){
                    isBreak = true;
                }
            }
            if(!(str.charAt(str.length() - 1) == words[i].charAt(0)) || isBreak){
                isBreak = true;
                cnt++;
                break;
            }
            str = words[i];
            cnt++;
        }
        if(isBreak){
            answer[0] = (cnt % n) + 1;
            answer[1] = (cnt / n) + 1;
        } else {
            answer[0] = 0;
            answer[1] = 0;
        }
        return answer;
    }
}