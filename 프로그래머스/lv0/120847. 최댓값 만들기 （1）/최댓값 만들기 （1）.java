class Solution {
    public int solution(int[] numbers) {
        int answer = 0;
        
        int max = -1;
        
        for(int i = 0; i < numbers.length - 1; i++){
            for(int j = i + 1; j < numbers.length; j++){
                int num = numbers[i] * numbers[j];
                if(max <= num)
                    max = num;
            }
        }
        answer = max;
        return answer;
    }
}