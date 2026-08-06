class Solution {
    public int solution(int[] absolutes, boolean[] signs) {
        int result = 0;
        
        for(int i = 0; i < signs.length; i++) {
            result += signs[i] ? absolutes[i] : -1 * absolutes[i];
        }
        
        return result;
    }
}