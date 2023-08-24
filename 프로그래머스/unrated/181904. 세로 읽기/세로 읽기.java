class Solution {
    public String solution(String my_string, int m, int c) {
        String answer = "";
        
        int index = 0;
        for(int i = 0; i < my_string.length(); i++){
            if((i + 1) % m == 0){
                String str = my_string.substring(index, i + 1);
                index = i + 1;
                answer += str.charAt(c - 1);
            }
        }
        
        return answer;
    }
}