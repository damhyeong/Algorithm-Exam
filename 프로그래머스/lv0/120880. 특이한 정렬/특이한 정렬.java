import java.util.*;
import java.math.*;

class Solution {
    public int[] solution(int[] numlist, int n) {
        int[] answer = new int[numlist.length];
        boolean[] visited = new boolean[numlist.length];
        
        for(int i = 0; i < numlist.length; i++){
            int minDiff = Integer.MAX_VALUE;
            int minIndex = -1;
            for(int j = 0; j < numlist.length; j++){
                if(visited[j])
                    continue;
                int absDiff = Math.abs(n - numlist[j]);
                if(minDiff > absDiff){
                    minDiff = absDiff;
                    minIndex = j;
                } else if(minDiff == absDiff){
                    minIndex = (numlist[minIndex] > numlist[j]) ? minIndex : j;
                }
            }
            visited[minIndex] = true;
            answer[i] = numlist[minIndex];
        }
        
        return answer;
    }
}