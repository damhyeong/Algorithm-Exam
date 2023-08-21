import java.util.*;

class Solution {
    public int[] solution(int n, int k) {
        int[] answer;
        
        if(n % k == 0)
            answer = new int[n / k];
        else
            answer = new int[n / k];
        
        for(int i = 1; i * k <= n; i++){
            answer[i - 1] = i * k;
        }
        
        return answer;
    }
}