import java.util.*;

class Solution {
    public Integer[] solution(int n) {
        Integer[] answer = {};
        
        List<Integer> list = new ArrayList<Integer>();
        list.add(n);
        while(n != 1){
            if(n % 2 == 0){
                n /= 2;
                list.add(n);
            } else {
                n = 3 * n + 1;
                list.add(n);
            }
        }
        answer = list.toArray(new Integer[list.size()]);
        
        return answer;
    }
}