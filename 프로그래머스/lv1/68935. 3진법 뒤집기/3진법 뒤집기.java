class Solution {
    public int solution(int n) {
        int answer = 0;
        
        String threeStr = "";
        while(n != 0){
            int num = n % 3;
            threeStr = Integer.toString(num) + threeStr;
            n /= 3;
        }
        
        String reverseThreeStr = "";
        for(int i = threeStr.length() - 1; i >= 0; i --)
            reverseThreeStr += threeStr.charAt(i);
        
        int len = reverseThreeStr.length();
        
        for(int i = 0; i < len; i++){
            int mul = 1;
            for(int j = len - i - 1; j >= 1; j--){
                mul *= 3;
            }
            answer += mul * Character.getNumericValue(reverseThreeStr.charAt(i));
        }
        
        return answer;
    }
}