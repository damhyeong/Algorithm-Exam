import java.util.*;

class Solution {
    public String[] solution(String myString) {
        String[] answer = {};
        
        List<String> list = new ArrayList<String>();
        int index = 0;
        for(int i = 0; i < myString.length(); i++){
            char ch = myString.charAt(i);
            if(ch == 'x'){
                if(index == i){
                    index = i + 1;
                    continue;
                }
                list.add(myString.substring(index, i));
                index = i + 1;
            }
        }
        
        if(index != myString.length())
            list.add(myString.substring(index, myString.length()));
        
        answer = list.toArray(new String[list.size()]);
        
        Arrays.sort(answer);
        
        return answer;
    }
}