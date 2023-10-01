class Solution {
    public String solution(String[] cards1, String[] cards2, String[] goal) {
        String answer = "";
        
        int index1 = 0; // cards1 index
        int index2 = 0; // cards2 index
        int index = 0; // goal index
        while(!(index1 == cards1.length && index2 == cards2.length)){
            
            if(index == goal.length)
                break;
            
            if(index1 != cards1.length && cards1[index1].equals(goal[index])){
                index1++;
                index++;
            }else if(index2 != cards2.length && cards2[index2].equals(goal[index])){
                index2++;
                index++;
            }else
                break;
        }
        
        answer = index == goal.length ? "Yes" : "No";
        
        return answer;
    }
}