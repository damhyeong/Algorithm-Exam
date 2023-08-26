class Solution {
    public long solution(String numbers) {
        long answer = 0;
        String strAnswer = "";
        
        int index = 0;
        for(int i = 1; i <= numbers.length(); i++){
            String newStr = numbers.substring(index, i);
            
            
            if(newStr.equals("zero")){
                strAnswer += "0";
                index = i;
            } else if(newStr.equals("one")){
                strAnswer += "1";
                index = i;
            } else if (newStr.equals("two")){
                strAnswer += "2";
                index = i;
            } else if (newStr.equals("three")){
                strAnswer += "3";
                index = i;
            } else if (newStr.equals("four")){
                strAnswer += "4";
                index = i;
            } else if (newStr.equals("five")){
                strAnswer += "5";
                index = i;
            } else if (newStr.equals("six")){
                strAnswer += "6";
                index = i;
            } else if (newStr.equals("seven")){
                strAnswer += "7";
                index = i;
            } else if (newStr.equals("eight")){
                strAnswer += "8";
                index = i;
            } else if (newStr.equals("nine")){
                strAnswer += "9";
                index = i;
            }
        }
        
        answer = Long.parseLong(strAnswer);
        
        return answer;
    }
}