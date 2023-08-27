import java.util.*;

class Solution {
    public String[] solution(String[] picture, int k) {
        String[] answer = {};
        
        List<String> list = new ArrayList<String>();
        
        for(int i = 0; i < picture.length; i++){
            String newStr = "";
            for(int j = 0; j < picture[i].length(); j++){
                char ch = picture[i].charAt(j);
                for(int n = 0; n < k; n++)
                    newStr += ch;
            }
            for(int n = 0; n < k; n++)
                list.add(newStr);
        }
        
        answer = list.toArray(new String[list.size()]);
        
        return answer;
    }
}