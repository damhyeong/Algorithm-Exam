class Solution {
    public int solution(int[] numbers) {
        int answer = 0;
        
        boolean[] noNum = new boolean[10];
        for(int i = 0; i < numbers.length; i++){
            noNum[numbers[i]] = true;
        }
        
        for(int i = 0; i < noNum.length; i++){
            if(!noNum[i])
                answer += i;
        }
        
        return answer;
    }
}