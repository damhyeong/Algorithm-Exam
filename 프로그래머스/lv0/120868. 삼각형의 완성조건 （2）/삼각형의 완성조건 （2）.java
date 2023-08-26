class Solution {
    public int solution(int[] sides) {
        int answer = 0;
        int max = 0, min = 0;
        if(sides[0] >= sides[1]){
            max = sides[0];
            min = sides[1];
        } else {
            max = sides[1];
            min = sides[0];
        }
        
        for(int i = (max - min) + 1; i < max + min; i++){
            answer++;
        }
        
        return answer;
    }
}