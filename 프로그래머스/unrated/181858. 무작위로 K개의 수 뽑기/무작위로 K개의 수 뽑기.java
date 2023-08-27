import java.util.*;

class Solution {
    public int[] solution(int[] arr, int k) {
        int[] answer = new int[k];
        
        Arrays.setAll(answer, num -> -1);
        int index = 0;
        
        for(int i = 0; i < arr.length; i++){
            int newNum = arr[i];
            
            boolean isContain = false;
            for(int j = 0; j < k; j++){
                if(answer[j] == newNum){
                    isContain = true;
                    break;
                } else if(answer[j] == -1){
                    break;
                }
            }
            if(isContain){
                continue;
            } else {
                answer[index++] = newNum;
                if(k == index)
                    break;
            }
        }
        
        return answer;
    }
}