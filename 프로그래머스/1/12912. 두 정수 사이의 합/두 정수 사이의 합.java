class Solution {
    public long solution(int a, int b) {
        long sum = 0;
        long start = a > b ? b : a;
        long end = a > b ? a : b;
        
        for(long i = start; i <= end; i++) {
            sum += i;
        }
        return sum;
    }
}