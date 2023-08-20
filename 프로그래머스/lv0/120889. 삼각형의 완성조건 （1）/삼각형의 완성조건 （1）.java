class Solution {
    public int solution(int[] sides) {
        int answer = 0;
        
        int maxIndex = 0;
        for(int i = 1; i < sides.length; i++){
            maxIndex = sides[maxIndex] <= sides[i] ? i : maxIndex;
        }
        int max = sides[maxIndex];
        int sum = 0;
        for(int i = 0; i < sides.length; i++){
            if(maxIndex == i)
                continue;
            else
                sum += sides[i];
        }
        
        if(max >= sum)
            answer = 2;
        else
            answer = 1;
        
        return answer;
    }
}