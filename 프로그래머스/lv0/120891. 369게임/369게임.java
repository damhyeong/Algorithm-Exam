

class Solution {
    public int solution(int order) {
        int answer = 0;
        
        String strNum = Integer.toString(order);
        for(int i = 0; i < strNum.length(); i++){
            char ch = strNum.charAt(i);
            if(Character.getNumericValue(ch) % 3 == 0 && ch != '0')
                answer++;
        }
        
        return answer;
    }
}