import java.util.*;

class Solution {
    public int[] solution(String myString) {
        int[] answer = {};
        
        List<String> strList = new ArrayList<String>();
        
        int fIndex = 0;
        for(int i = 0; i < myString.length(); i++){
            char ch = myString.charAt(i);
            if(ch == 'x'){
                strList.add(myString.substring(fIndex, i));
                fIndex = i + 1;
            }
        }
        
        
        answer = new int[strList.size() + 1];
        for(int i = 0; i < answer.length - 1; i++){
            answer[i] = strList.get(i).length();
        }
        answer[answer.length - 1] = (fIndex == myString.length()) ? 0 : (myString.length() - fIndex);
        return answer;
    }
}