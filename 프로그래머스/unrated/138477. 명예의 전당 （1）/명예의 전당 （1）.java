import java.util.*;

class Solution {
    public int[] solution(int k, int[] score) {
        int[] answer = new int[score.length];
        
        List<Integer> list = new ArrayList<>();
        
        for(int i = 0; i < score.length; i++){
            int newNum = score[i];
            list.add(newNum);
            
            Collections.sort(list);
            
            int result = -1;
            for(int j = list.size() - 1, x = 0; j >= 0; j--, x++){
                result = list.get(j);
                if(x == k - 1)
                    break;
            }
            answer[i] = result;
        }
        
        return answer;
    }
}