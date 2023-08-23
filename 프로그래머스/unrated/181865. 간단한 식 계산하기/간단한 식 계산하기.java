import java.util.*;

class Solution {
    public int solution(String binomial) {
        int answer = 0;
        
        StringTokenizer st = new StringTokenizer(binomial);
        answer = Integer.parseInt(st.nextToken());
        while(st.hasMoreTokens()){
            String ch = st.nextToken();
            int num = Integer.parseInt(st.nextToken());
            
            if(ch.equals("+"))
                answer += num;
            else if(ch.equals("-"))
                answer -= num;
            else if(ch.equals("*"))
                answer *= num;
        }
        
        return answer;
    }
}