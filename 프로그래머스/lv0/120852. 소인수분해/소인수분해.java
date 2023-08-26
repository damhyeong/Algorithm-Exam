import java.util.*;

class Solution {
    public Integer[] solution(int n) {
        Integer[] answer = {};
        
        int num = n;
        
        List<Integer> list = new ArrayList<Integer>();
        
        while(n != 1){
            for(int i = 2; i <= num; i++){
                if(n % i == 0){
                    n /= i;
                    
                    boolean isContain = false;
                    for(int j = 0; j < list.size(); j++){
                        if(list.get(j) == i){
                            isContain = true;
                            break;
                        }
                    }
                    if(!isContain)
                        list.add(i);
                    
                    break;
                }
            }
        }
        
        answer = list.toArray(new Integer[list.size()]);
        
        return answer;
    }
}