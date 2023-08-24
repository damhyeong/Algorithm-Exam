class Solution {
    public int solution(String before, String after) {
        int answer = 1;
        
        int[] bAlphabet = new int['z' - 'a' + 1];
        for(int i = 0; i < before.length(); i++){
            char ch = before.charAt(i);
            bAlphabet[ch - 'a']++;
        }
        
        int[] aAlphabet = new int['z' - 'a' + 1];
        for(int i = 0; i < after.length(); i++){
            char ch = after.charAt(i);
            aAlphabet[ch - 'a']++;
        }
        
        for(int i = 0; i < bAlphabet.length; i++){
            if(bAlphabet[i] != aAlphabet[i]){
                answer = 0;
                break;
            }
        }
        
        return answer;
    }
}