class Solution {
    public int solution(String myString, String pat) {
        int answer = 0;
        
        String newString = "";
        for(int i = 0; i < myString.length(); i++){
            char ch = myString.charAt(i);
            if(ch == 'A')
                newString += 'B';
            else if(ch == 'B')
                newString += 'A';
        }
        if(newString.contains(pat))
            answer = 1;
        else
            answer = 0;
        
        return answer;
    }
}