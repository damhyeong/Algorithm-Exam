class Solution {
    public int[] solution(int[] arr) {
        int[] answer = {};
        
        int len = arr.length;
        
        int mul = 1;
        while(mul < len){
            mul *= 2;
        }
        
        answer = new int[mul];
        
        for(int i = 0; i < answer.length; i++){
            if(i < arr.length)
                answer[i] = arr[i];
            else
                answer[i] = 0;
        }
        
        return answer;
    }
}