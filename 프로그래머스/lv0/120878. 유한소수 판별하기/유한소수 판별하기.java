class Solution {
    public int solution(int a, int b) {
        int answer = 0;
        
        
        int maxShareNum = getMaxShareNum(a, b);
        a /= maxShareNum;
        b /= maxShareNum;
            
        boolean isTrue = true;
        
        while(b != 1){
            for(int i = 2; i <= b; i++){
                if(b % i == 0){
                    if(i == 2 || i == 5){
                        b /= i;
                        break;
                    } else {
                        isTrue = false;
                        b /= i;
                        break;
                    }
                }
            }
        }
        if(isTrue)
            answer = 1;
        else
            answer = 2;
        return answer;
    }
    
    public static int getMaxShareNum(int a, int b){
        int max = 0;
        for(int i = 1; i <= a && i <= b; i++){
            if(a % i == 0 && b % i == 0)
                max = i;
        }
        return max;
    }
}