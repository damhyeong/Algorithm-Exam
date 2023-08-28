import java.util.*;
import java.math.*;

class Solution {
    public int solution(int a, int b, int c, int d) {
        int answer = 0;
        int[] numbers = new int[4];
        numbers[0] = a; numbers[1] = b; numbers[2] = c; numbers[3] = d;
        
        Set<Integer> set = new HashSet<Integer>();
        
        set.add(a); set.add(b); set.add(c); set.add(d);
        if(set.size() == 1){ // 네 주사위가 모두 같다면. 
            for(int i = 1; i <= 6; i++){
                if(set.contains(i)){
                    answer = 1111 * i;
                    break;
                }
            }
        } else if(set.size() == 2){ // 세 주사위가 같고, 나머지 하나가 다르다면.
            Iterator iter = set.iterator();
            int p = (int)iter.next();
            int q = (int)iter.next();
            int pCnt = 0;
            int qCnt = 0;
            for(int i = 0; i < numbers.length; i++){
                if(numbers[i] == p)
                    pCnt++;
                else if(numbers[i] == q)
                    qCnt++;
            }
            if(pCnt == 3 || qCnt == 3){
                if(pCnt == 3){
                    answer = (10 * p + q) * (10 * p + q);
                } else {
                    int temp = p;
                    p = q;
                    q = temp;
                    answer = (10 * p + q) * (10 * p + q);
                }
            } else {
                answer = (p + q) * Math.abs(p - q);
            }
        } else if(set.size() == 3){
            Iterator iter = set.iterator();
            int n1 = (int)iter.next();
            int n2 = (int)iter.next();
            int n3 = (int)iter.next();
            
            int n1Cnt = 0; int n2Cnt = 0; int n3Cnt = 0;
            for(int i = 0; i < numbers.length; i++){
                int newNum = numbers[i];
                if(newNum == n1)
                    n1Cnt++;
                else if(newNum == n2)
                    n2Cnt++;
                else if(newNum == n3)
                    n3Cnt++;
                
                if(n1Cnt == 2)
                    answer = n2 * n3;
                else if(n2Cnt == 2)
                    answer = n1 * n3;
                else if(n3Cnt == 2)
                    answer = n1 * n2;
            }
            
        } else if(set.size() == 4){
            int min = 100;
            for(int i = 0; i < numbers.length; i++){
                min = min >= numbers[i] ? numbers[i] : min;
            }
            answer = min;
        }
        
        return answer;
    }
}