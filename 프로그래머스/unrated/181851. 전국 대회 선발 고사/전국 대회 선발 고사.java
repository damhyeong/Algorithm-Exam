import java.util.*;

class Solution {
    public int solution(int[] rank, boolean[] attendance) {
        int answer = 0;
        
        List<Integer> list = new ArrayList<Integer>();
        
        
        int minIndex = -1;
        int minValue = Integer.MAX_VALUE;
        for(int i = 0; i < rank.length; i++){
            if(attendance[i] && rank[i] <= minValue){
                minIndex = i;
                minValue = rank[i];
            }
        }
        int a = minIndex;
        
        minIndex = -1;
        minValue = Integer.MAX_VALUE;
        for(int i = 0; i < rank.length; i++){
            if(i == a)
                continue;
            
            if(attendance[i] && rank[i] <= minValue){
                minIndex = i;
                minValue = rank[i];
            }
        }
        int b = minIndex;
        
        minIndex = -1;
        minValue = Integer.MAX_VALUE;
        for(int i = 0; i < rank.length; i++){
            if(i == a || i == b)
                continue;
            if(attendance[i] && rank[i] <= minValue){
                minIndex = i;
                minValue = rank[i];
            }
        }
        int c = minIndex;
        
        answer = (10000 * a) + (100 * b) + c;
        
        return answer;
    }
}