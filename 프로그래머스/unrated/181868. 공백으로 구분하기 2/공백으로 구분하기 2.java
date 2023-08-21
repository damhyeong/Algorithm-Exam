import java.util.*;
import java.io.*;

class Solution {
    public String[] solution(String my_string) throws IOException {
        String[] answer = {};
        
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(my_string);
        
        ArrayList<String> list = new ArrayList<>();
        
        while(st.hasMoreTokens()){
            list.add(st.nextToken());
        }
        
        answer = list.toArray(new String[list.size()]);
        
        return answer;
    }
}