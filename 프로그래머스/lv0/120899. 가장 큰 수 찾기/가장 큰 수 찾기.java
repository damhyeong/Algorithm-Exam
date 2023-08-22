class Solution {
    public int[] solution(int[] array) {
        int[] answer = new int[2];
        
        int maxIndex = 0;
        
        for(int i = 0; i < array.length; i++)
            maxIndex = array[i] >= array[maxIndex] ? i : maxIndex;
        
        answer[0] = array[maxIndex]; answer[1] = maxIndex;
        
        return answer;
    }
}