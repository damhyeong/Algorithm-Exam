class Solution {
    public String solution(String s) {
        String answer = "";
        
        int middle = s.length() / 2;
        
        if(s.length() % 2 == 0){
            answer += s.substring(middle - 1, middle + 1);
        } else {
            answer += s.charAt(middle);
        }
        
        return answer;
    }
}