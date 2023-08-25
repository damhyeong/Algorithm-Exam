import java.util.*;

class Solution {
    public int solution(String s) {
        int answer = 0;
        
        LinkedList<Integer> list = new LinkedList<Integer>();
        
        StringTokenizer st = new StringTokenizer(s);
        while(st.hasMoreTokens()){
            String str = st.nextToken();
            if(str.equals("Z"))
                list.removeLast();
            else
                list.add(Integer.parseInt(str));
        }
        for(int i = 0; i < list.size(); i++)
            answer += list.get(i);
        
        return answer;
    }
}