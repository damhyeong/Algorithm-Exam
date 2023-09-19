import java.util.*;

class Solution {
    public String solution(String s) {
        String answer = "";
        
        List<Character> smallList = new ArrayList<>();
        List<Character> bigList = new ArrayList<>();
        
        for(int i = 0; i < s.length(); i++){
            char ch = s.charAt(i);
            if(ch >= 'a' && ch <= 'z')
                smallList.add(ch);
            else if(ch >= 'A' && ch <= 'Z')
                bigList.add(ch);
        }
        Collections.sort(smallList);
        Collections.sort(bigList);
        
        for(int i = smallList.size() - 1; i >= 0; i--)
            answer += smallList.get(i);
        for(int i = bigList.size() - 1; i >= 0; i--)
            answer += bigList.get(i);
        
        return answer;
    }
}