class Solution {
    public int solution(int n) {
        int answer = 0;
        
        int sum = 1;
        int mul = 0;
        while(true){
            mul++;
            sum *= mul;
            if(sum > n)
                break;
        }
        
        answer = mul - 1;
        
        return answer;
    }
}