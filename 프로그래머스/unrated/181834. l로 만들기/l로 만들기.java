class Solution {
    public String solution(String myString) {
        String answer = "";
        
        for(int i = 0; i < myString.length(); i++){
            char ch = myString.charAt(i);
            ch = (ch < 'l') ? 'l' : ch;
            answer += ch;
        }
        
        return answer;
    }
}