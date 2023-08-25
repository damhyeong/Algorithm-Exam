class Solution {
    public String solution(String my_string, int[] indices) {
        String answer = "";
        
        boolean[] trueCh = new boolean[my_string.length()];
        
        for(int i = 0; i < indices.length; i++){
            trueCh[indices[i]] = true;
        }
        for(int i = 0; i < my_string.length(); i++){
            if(!trueCh[i])
                answer += my_string.charAt(i);
        }
        
        return answer;
    }
}