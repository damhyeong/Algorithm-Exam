import java.util.*;

class Solution {
    public Integer[] solution(String my_string) {
        Integer[] answer = {};
        
        int[] upperCases = new int['Z' - 'A' + 1];
        int[] lowerCases = new int['z' - 'a' + 1];
        
        for(int i = 0; i < my_string.length(); i++){
            char ch = my_string.charAt(i);
            if('A' <= ch && ch <= 'Z')
                upperCases[ch - 'A']++;
            else if('a' <= ch && ch <= 'z')
                lowerCases[ch - 'a']++;
        }
        
        List<Integer> list = new ArrayList<Integer>();
        
        for(int i = 0; i < upperCases.length; i++)
            list.add(upperCases[i]);
        
        for(int i = 0; i < lowerCases.length; i++)
            list.add(lowerCases[i]);
        
        answer = list.toArray(new Integer[list.size()]);
        
        return answer;
    }
}