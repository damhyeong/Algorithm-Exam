import java.util.*;

class Solution {
    public Integer[] solution(int[] array, int[][] commands) {
        Integer[] answer = {};
        List<Integer> list = new ArrayList<>();
        
        for(int x = 0; x < commands.length; x++){
            List<Integer> newList = new ArrayList<>();
            int i = commands[x][0];
            int j = commands[x][1];
            int k = commands[x][2];
            
            for(int y = i - 1; y <= j - 1; y++)
                newList.add(array[y]);
            
            Collections.sort(newList);
            
            list.add(newList.get(k - 1));
        }
        
        answer = list.toArray(new Integer[list.size()]);
        
        return answer;
    }
}