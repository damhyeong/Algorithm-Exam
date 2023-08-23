import java.util.*;

class Solution {
    public String[] solution(String[] strArr) {
        String[] answer = {};
        List<String> list = new ArrayList<String>();
        
        for(int i = 0; i < strArr.length; i++){
            if(strArr[i].contains("ad"))
                continue;
            list.add(strArr[i]);
        }
        
        answer = list.toArray(new String[list.size()]);
        
        return answer;
    }
}