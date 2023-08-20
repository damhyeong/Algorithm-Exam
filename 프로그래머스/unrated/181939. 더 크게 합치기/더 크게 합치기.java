class Solution {
    public int solution(int a, int b) {
        int answer = 0;
        
        int num1 = Integer.parseInt(Integer.toString(a) + Integer.toString(b));
        int num2 = Integer.parseInt(Integer.toString(b) + Integer.toString(a));
        
        answer = num1 >= num2 ? num1 : num2;
        
        return answer;
    }
}