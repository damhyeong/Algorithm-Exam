import java.util.*;
import java.io.*;

class Solution {
    public String solution(String s) throws IOException {
        String answer = "";
        
        List<Integer> list = new ArrayList<>();
        StringTokenizer st = new StringTokenizer(s);
        while(st.hasMoreTokens())
            list.add(Integer.parseInt(st.nextToken()));
        
        Collections.sort(list);
        answer = Integer.toString(list.get(0)) + 
            " " + Integer.toString(list.get(list.size() - 1));
        
        return answer;
    }
}