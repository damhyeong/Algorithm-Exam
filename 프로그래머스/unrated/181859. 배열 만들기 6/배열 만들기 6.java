import java.util.*;

class Solution {
    public Integer[] solution(int[] arr) {
        Integer[] answer = {};
        
        List<Integer> list = new ArrayList<Integer>();
        
        int i = 0;
        while(i < arr.length){
            if(list.isEmpty())
                list.add(arr[i++]);
            else {
                if(list.get(list.size() - 1) == arr[i]){
                    list.remove(list.size() - 1);
                    i++;
                } else
                    list.add(arr[i++]);
            }
        }
        if(list.isEmpty()){
            answer = new Integer[1];
            answer[0] = -1;
        } else 
            answer = list.toArray(new Integer[list.size()]);
        
        return answer;
    }
}