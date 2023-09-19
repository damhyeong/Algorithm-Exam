import java.util.*;

class Solution {
    public Integer[] solution(int[] arr, int divisor) {
        Integer[] answer = new Integer[1];
        answer[0] = -1;
        
        List<Integer> list = new ArrayList<>();
        for(int i = 0; i < arr.length; i++)
            if(arr[i] % divisor == 0)
                list.add(arr[i]);
        
        Collections.sort(list);
        
        if(!list.isEmpty()){
            answer = list.toArray(new Integer[list.size()]);
        }
        
        return answer;
    }
}