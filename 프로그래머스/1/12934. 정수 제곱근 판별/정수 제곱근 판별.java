class Solution {
    public long solution(long n) {
        long answer = -1;
        
        for(long i = 1; i * i <= n; i++) {
            if(i * i == n) {
                long result = i + 1;
                return result * result;
            }
        }
        
        return answer;
    }
}