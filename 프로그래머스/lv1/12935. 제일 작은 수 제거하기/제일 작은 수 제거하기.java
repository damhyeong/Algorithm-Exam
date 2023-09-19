import java.util.*;

class Solution {
    public Integer[] solution(int[] arr) {
        Integer[] answer = new Integer[1];
        answer[0] = -1;
        
        List<Integer> list = new ArrayList<>();
        
        int minIndex = 0;
        for(int i = 1; i < arr.length; i++){
            minIndex = arr[i] > arr[minIndex] ? minIndex : i;
        }
        
        for(int i = 0; i < arr.length; i++){
            if(i == minIndex)
                continue;
            list.add(arr[i]);
        }
        
        if(arr.length != 1)
            answer = list.toArray(new Integer[list.size()]);
        
        return answer;
    }
}