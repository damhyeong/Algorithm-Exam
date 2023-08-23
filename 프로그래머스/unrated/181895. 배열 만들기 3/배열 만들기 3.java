import java.util.*;

class Solution {
    public Integer[] solution(int[] arr, int[][] intervals) {
        Integer[] answer = {};
        List<Integer> list = new ArrayList<Integer>();
        
        for(int i = 0; i < 2; i++){
            int fIndex = intervals[i][0];
            int lIndex = intervals[i][1];
            for(int j = fIndex; j <= lIndex; j++){
                list.add(arr[j]);
            }
        }
        
        answer = list.toArray(new Integer[list.size()]);
        
        return answer;
    }
}