import java.util.*;
import java.math.*;


class Solution {
    public String solution(String a, String b) {
        String answer = "";
        
        BigInteger firstInteger = new BigInteger("0");
        BigInteger aInteger = new BigInteger(a);
        BigInteger bInteger = new BigInteger(b);
        
        firstInteger = firstInteger.add(aInteger);
        firstInteger = firstInteger.add(bInteger);
        
        answer = firstInteger.toString();
        
        return answer;
    }
}