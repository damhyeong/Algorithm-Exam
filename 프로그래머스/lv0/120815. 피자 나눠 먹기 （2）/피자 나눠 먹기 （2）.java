class Solution {
    public int solution(int n) {
        int answer = 0;
        
        int cnt = 0;
        while(true){
            cnt++;
            if((cnt * 6) % n == 0){
                break;
            }
        }
        answer = cnt;
        
        return answer;
    }
}