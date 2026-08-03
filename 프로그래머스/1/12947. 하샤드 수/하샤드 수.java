import java.util.*;

class Solution {
    public boolean solution(int x) {
        List<Integer> list = new ArrayList<>();
        
        int tmp = x;
        while(tmp != 0) {
            list.add(tmp % 10);
            tmp /= 10;
        }
        
        int result = 0;
        for(int i = 0; i < list.size(); i++) {
            result += list.get(i);
        }

        if(x % result == 0)
            return true;
        else
            return false;
    }
}