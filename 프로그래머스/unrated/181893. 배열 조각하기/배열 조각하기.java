import java.util.*;

class Solution {
    public int[] solution(int[] arr, int[] query) {
        int[] answer = arr;
        
        int fIndex = -1;
        int lIndex = -1;
        
        List<Integer> list;
        
        for(int i = 0; i < query.length; i++){
            list = new ArrayList<Integer>();
            if(i % 2 == 0){
                lIndex = query[i];
                for(int j = 0; j <= lIndex; j++)
                    list.add(answer[j]);
            } else {
                fIndex = query[i];
                for(int j = fIndex; j < answer.length; j++)
                    list.add(answer[j]);
            }
            answer = new int[list.size()];
            for(int j = 0; j < answer.length; j++){
                answer[j] = list.get(j);
            }
        }
        return answer;
    }
}