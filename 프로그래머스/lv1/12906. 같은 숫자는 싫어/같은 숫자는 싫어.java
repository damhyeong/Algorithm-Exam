import java.util.*;

public class Solution {
    public Integer[] solution(int []arr) {
        Integer[] answer = {};
        
        List<Integer> list = new ArrayList<>();
        
        list.add(arr[0]);
        int preNum = arr[0];
        
        for(int i = 1; i < arr.length; i++){
            int newNum = arr[i];
            if(preNum == newNum)
                continue;
            else{
                preNum = newNum;
                list.add(newNum);
            }
        }
        
        answer = list.toArray(new Integer[list.size()]);

        return answer;
    }
}