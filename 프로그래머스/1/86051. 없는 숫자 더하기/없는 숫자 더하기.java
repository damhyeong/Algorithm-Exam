class Solution {
    public int solution(int[] numbers) {
        int answer = 0;
        
        boolean[] isDisplayed = new boolean[10];
        
        for(int i = 0; i < numbers.length; i++){
            isDisplayed[numbers[i]] = true;
        }
        
        for(int i = 0; i < isDisplayed.length; i++) {
            answer += isDisplayed[i] ? 0 : i;
        }
        
        return answer;
    }
}