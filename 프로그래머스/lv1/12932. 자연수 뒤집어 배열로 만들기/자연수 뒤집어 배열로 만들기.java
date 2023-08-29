class Solution {
    public int[] solution(long n) {
        int[] answer = {};
        
        String strNum = Long.toString(n);
        
        answer = new int[strNum.length()];
        
        for(int i = strNum.length() - 1, j = 0; i >= 0; i--, j++)
            answer[j] = Character.getNumericValue(strNum.charAt(i));
        
        return answer;
    }
}