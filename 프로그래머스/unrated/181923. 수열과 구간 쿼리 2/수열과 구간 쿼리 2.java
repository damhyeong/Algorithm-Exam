import java.util.*;

class Solution {
    public Integer[] solution(int[] arr, int[][] queries) {
        Integer[] answer = {};
        List<Integer> list = new ArrayList<Integer>();
        
        for(int i = 0; i < queries.length; i++){
            
            int s = queries[i][0];
            int e = queries[i][1];
            int k = queries[i][2];
            
            int min = Integer.MAX_VALUE;
            for(int j = s; j <= e; j++){
                if(arr[j] > k)
                    if(arr[j] <= min)
                        min = arr[j];
            }
            if(min == Integer.MAX_VALUE)
                list.add(-1);
            else
                list.add(min);
        }
        
        answer = list.toArray(new Integer[list.size()]);
        
        return answer;
    }
}