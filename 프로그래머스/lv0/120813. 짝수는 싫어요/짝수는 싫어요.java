class Solution {
    public int[] solution(int n) {
        int[] answer;
        
        int cnt = 0;
        for(int i = 1; i <= n; i += 2){
            cnt++;
        }
        
        answer = new int[cnt];
        
        for(int i = 0, j = 1; i < cnt; i++, j += 2){
            answer[i] = j;
        }
        
        return answer;
    }
}