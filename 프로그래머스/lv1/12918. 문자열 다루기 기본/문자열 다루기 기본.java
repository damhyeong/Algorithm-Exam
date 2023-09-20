class Solution {
    public boolean solution(String s) {
        boolean answer = true;
        
        int len = s.length();
        if(len == 4 || len == 6)
            answer = true;
        else
            answer = false;
        
        for(int i = 0; i < s.length(); i++){
            char ch = s.charAt(i);
            if(ch >= '0' && ch <= '9')
                continue;
            else{
                answer = false;
                break;
            }
        }
        
        return answer;
    }
}