class Solution {
    public long solution(long n) {
        long answer = 0;
        
        Long rimit = 50000000000000l;
        long index = 1;
        
        while(true){
            if(index * index == n)
                break;
            else if(index * index >= n){
                answer = -1;
                break;
            }
            index++;
        }
        if(answer != -1)
            answer = (index + 1) * (index + 1);
        
        return answer;
    }
}