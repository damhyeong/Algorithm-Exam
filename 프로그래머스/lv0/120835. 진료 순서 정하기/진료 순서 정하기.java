class Solution {
    public int[] solution(int[] emergency) {
        int[] answer = new int[emergency.length];
        
        boolean[] isVisited = new boolean[emergency.length];
        int cnt = 1;
        for(int i = 0; i < emergency.length; i++){
            int max = -1;
            
            for(int j = 0; j < emergency.length; j++){
                if(isVisited[j])
                    continue;
                if(emergency[j] > max)
                    max = emergency[j];
            }
            for(int j = 0; j < emergency.length; j++){
                if(max == emergency[j]){
                    isVisited[j] = true;
                    answer[j] = cnt;
                    cnt++;
                    break;
                }
            }
        }
        
        return answer;
    }
}