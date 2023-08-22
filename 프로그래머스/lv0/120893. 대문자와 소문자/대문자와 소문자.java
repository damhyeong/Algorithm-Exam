class Solution {
    public String solution(String my_string) {
        String answer = "";
        
        for(int i = 0; i < my_string.length(); i++){
            char ch = my_string.charAt(i);
            if('a' <= ch && 'z' >= ch)
                ch = (char)(ch - 'a' + 'A');
            else if('A' <= ch && 'Z' >= ch)
                ch = (char)(ch - 'A' + 'a');
            
            answer += ch;
        }
        
        return answer;
    }
}