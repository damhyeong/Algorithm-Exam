import java.util.*;

class Solution {
    public int solution(String my_string) {
        int answer = 0;
        
        StringTokenizer st = new StringTokenizer(my_string);
        answer = Integer.parseInt(st.nextToken());
        
        while(st.hasMoreTokens()){
            String calculate = st.nextToken();
            int calNum = Integer.parseInt(st.nextToken());
            if(calculate.contains("+"))
                answer += calNum;
            else if(calculate.contains("-"))
                answer -= calNum;
        }
        
        return answer;
    }
}