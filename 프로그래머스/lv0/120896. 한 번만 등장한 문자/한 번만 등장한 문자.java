class Solution {
    public String solution(String s) {
        String answer = "";
        
        int[] chCnt = new int['z' - 'a' + 1];
        
        for(int i = 0; i < s.length(); i++){
            chCnt[s.charAt(i) - 'a']++;
        }
        for(int i = 0; i < chCnt.length; i++){
            if(chCnt[i] == 1)
                answer += (char)(i + 'a');
        }
        
        return answer;
    }
}