import java.util.*;

class Solution {
    public String[] solution(String myStr) {
        String[] answer = {};
        
        List<String> list = new ArrayList<String>();
        
        int len = 0;
        for(int i = 0; i < myStr.length(); i++){
            char ch = myStr.charAt(i);
            if(ch == 'a' || ch == 'b' || ch == 'c'){
                if(len == 0)
                    continue;
                else {
                    list.add(myStr.substring(i - len, i));
                    len = 0;
                }
            } else {
                len++;
            }
        }
        if(len > 0)
            list.add(myStr.substring(myStr.length() - len, myStr.length()));
        
        if(list.isEmpty()){
            answer = new String[1];
            answer[0] = "EMPTY";
        } else {
            answer = list.toArray(new String[list.size()]);
        }
        return answer;
    }
}