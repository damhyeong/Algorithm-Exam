class Solution {
    public int solution(int num) {
        int answer = -1;
        
        long lNum = num;
        
        if(num == 1)
            return 0;
        
        int cnt = 0;
        while(lNum != 1){
            if(cnt >= 500)
                break;
            if(lNum % 2 == 0)
                lNum /= 2;
            else
                lNum = lNum * 3 + 1;
            cnt++;
        }
        if(cnt >= 500)
            answer = -1;
        else
            answer = cnt;
        
        return answer;
    }
}