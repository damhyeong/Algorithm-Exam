class Solution {
    public int solution(String s) {
        int answer = 0;
        
        char ch = s.charAt(0);
        if(ch == '+'){
            answer = Integer.parseInt(s.substring(1, s.length()));
        } else if(ch == '-'){
            answer = Integer.parseInt(s);
        } else {
            answer = Integer.parseInt(s);
        }
        
        return answer;
    }
}