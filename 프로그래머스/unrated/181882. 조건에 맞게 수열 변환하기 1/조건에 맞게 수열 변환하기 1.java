class Solution {
    public int[] solution(int[] arr) {
        int[] answer = new int[arr.length];
        
        for(int i = 0; i < arr.length; i++){
            int num = arr[i];
            if(num >= 50 && num % 2 == 0){
                answer[i] = arr[i] / 2;
                continue;
            } else if(num < 50 && num % 2 == 1){
                answer[i] = arr[i] * 2;
            } else
                answer[i] = arr[i];
        }
        
        return answer;
    }
}