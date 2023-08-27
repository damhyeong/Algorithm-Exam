class Solution {
    public int solution(int n) {
        int answer = 1;
        
        int index = 1;
        
        while(index != n){
            if(answer % 3 == 0){
                answer++;
                continue;
            }
            if(Integer.toString(answer).contains("3")){
                answer++;
                continue;
            }
            answer++;
            index++;
        }
        
        while((answer % 3 == 0) || (Integer.toString(answer).contains("3")))
            answer++;
        
        return answer;
    }
}