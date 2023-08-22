class Solution {
    public String solution(String myString) {
        String answer = "";
        
        for(int i = 0; i < myString.length(); i++){
            char ch = myString.charAt(i);
            if(ch == 'a')
                answer += 'A';
            else if(ch >= 'B' &&  ch <= 'Z')
                answer += (char)(ch - 'A' + 'a');
            else
                answer += ch;
        }
        
        return answer;
    }
}