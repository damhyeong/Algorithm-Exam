class Solution {
    public String solution(String my_string, int[][] queries) {
        String answer = my_string;
        
        
        for(int i = 0; i < queries.length; i++){
            int s = queries[i][0];
            int e = queries[i][1];
            
            String frontStr = "";
            String lastStr = "";
            String reverseStr = "";
            
            if(s != 0)
                frontStr += answer.substring(0, s);
            if(e != answer.length() - 1)
                lastStr += answer.substring(e + 1, answer.length());
            
            for(int j = e; j >= s; j--)
                reverseStr += answer.charAt(j);
            
            answer = frontStr + reverseStr + lastStr;
        }
        answer = answer.trim();
        return answer;
    }
}