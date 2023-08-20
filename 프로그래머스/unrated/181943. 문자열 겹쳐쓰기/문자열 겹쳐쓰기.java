class Solution {
    public String solution(String my_string, String overwrite_string, int s) {
        
        char[] chStr = my_string.toCharArray();
        
        for(int i = 0; i < overwrite_string.length(); i++){
            chStr[s + i] = overwrite_string.charAt(i);
        }
        String answer = new String(chStr);
        return answer;
    }
}