class Solution {
    public int solution(String A, String B) {
        int answer = -1;
        
        for(int i = 0; i < A.length(); i++){
            if(A.equals(B)){
                answer = i;
                break;
            }
            String subString1 = A.substring(0, A.length() - 1);
            String subString2 = A.substring(A.length() - 1, A.length());
            A = subString2 + subString1;
        }
        
        return answer;
    }
}