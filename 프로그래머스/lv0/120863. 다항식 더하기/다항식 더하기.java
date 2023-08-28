import java.util.*;

class Solution {
    public String solution(String polynomial) {
        String answer = "";
        
        long xNum = 0;
        long num = 0;
        
        StringTokenizer st = new StringTokenizer(polynomial);
        String newNum = st.nextToken();
        
        if(newNum.contains("x")){
            if(newNum.length() != 1){
                long intNum = Long.parseLong(newNum.substring(0, newNum.length() - 1));
                xNum += intNum;
            } else {
                xNum++;
            }
        } else {
            long intNum = Long.parseLong(newNum);
            num += intNum;
        }
        
        while(st.hasMoreTokens()){
            st.nextToken();
            newNum = st.nextToken();
        
            if(newNum.contains("x")){
                if(newNum.length() != 1){
                    long intNum = Long.parseLong(newNum.substring(0, newNum.length() - 1));
                    xNum += intNum;
                } else {
                    xNum++;
                }
            } else {
                long intNum = Long.parseLong(newNum);
                num += intNum;
            }
        }
        if(xNum > 0 && num > 0){
            if(xNum != 1)
                answer = Long.toString(xNum) + "x + " + Long.toString(num);
            else
                answer = "x + " + Long.toString(num);
        } else if(xNum > 0){
            if(xNum != 1)
                answer = Long.toString(xNum) + "x";
            else
                answer = "x";
        }else if(num > 0)
            answer = Long.toString(num);
        
        return answer;
    }
}