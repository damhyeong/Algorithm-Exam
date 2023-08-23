import java.util.*;

class Solution {
    public Integer[] solution(int n) {
        Integer[] answer = {};
        
        List<Integer> list = new ArrayList<Integer>();
        
        for(int i = 1; i <= n; i++){
            if(n % i == 0)
                list.add(i);
        }
        answer = list.toArray(new Integer[list.size()]);
        
        return answer;
    }
}