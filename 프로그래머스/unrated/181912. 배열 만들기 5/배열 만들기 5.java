import java.util.*;

class Solution {
    public Integer[] solution(String[] intStrs, int k, int s, int l) {
        Integer[] answer = {};
        
        List<Integer> list = new ArrayList<Integer>();
        
        for(int i = 0; i < intStrs.length; i++){
            int num = Integer.parseInt(intStrs[i].substring(s, s + l));
            
            if(num > k)
                list.add(num);
        }
        
        answer = list.toArray(new Integer[list.size()]);
        
        return answer;
    }
}