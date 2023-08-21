class Solution {
    public int[] solution(int[] num_list) {
        int[] answer = new int[num_list.length + 1];
        
        for(int i = 0; i < num_list.length; i++)
            answer[i] = num_list[i];
        
        int lastNum = num_list[num_list.length - 1];
        int preNum = num_list[num_list.length - 2];
        
        if(lastNum > preNum)
            answer[num_list.length] = lastNum - preNum;
        else
            answer[num_list.length] = lastNum * 2;
        
        return answer;
    }
}