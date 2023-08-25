import java.util.*;

class Solution {
    public Integer[] solution(int[] arr) {
        Integer[] answer = {};
        
        int fIndex = -1;
        for(int i = 0; i < arr.length; i++){
            if(arr[i] == 2){
                fIndex = i;
                break;
            }
        }
        
        int lIndex = -1;
        for(int i = arr.length - 1; i >= 0; i--){
            if(arr[i] == 2){
                lIndex = i;
                break;
            }
        }
        if(fIndex == -1){
            answer = new Integer[1];
            answer[0] = -1;
        } else {
            List<Integer> list = new ArrayList<Integer>();
            for(int i = fIndex; i <= lIndex; i++)
                list.add(arr[i]);
            answer = list.toArray(new Integer[list.size()]);
        }
        
        return answer;
    }
}