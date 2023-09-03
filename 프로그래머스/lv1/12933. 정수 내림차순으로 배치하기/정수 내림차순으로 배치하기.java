import java.util.*;

class Solution {
    public long solution(long n) {
        long answer = 0;
        
        String nString = Long.toString(n);
        int[] arr = new int[nString.length()];
        
        for(int i = 0; i < nString.length(); i++)
            arr[i] = Character.getNumericValue(nString.charAt(i));
        
        Arrays.sort(arr);
        
        String answerStr = "";
        
        for(int i = arr.length - 1; i >= 0; i--)
            answerStr += Integer.toString(arr[i]);
        
        answer = Long.parseLong(answerStr);
        
        return answer;
    }
}