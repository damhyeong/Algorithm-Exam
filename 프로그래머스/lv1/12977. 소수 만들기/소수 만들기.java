import java.util.*;
import java.io.*;

class Solution {
    public static int cnt = 0;
    public static int[] arr;
    public static int[] selectThree;
    public static boolean[] isSelected;
    public int solution(int[] nums) {
        
        int answer = -1;
        arr = nums;
        selectThree = new int[3];
        
        for(int i = 0; i < arr.length - 2; i++){
            for(int j = i + 1; j < arr.length - 1; j++){
                for(int k = j + 1; k < arr.length; k++){
                    selectThree[0] = arr[i];
                    selectThree[1] = arr[j];
                    selectThree[2] = arr[k];
                    if(isPrime())
                        cnt++;
                }
            }
        }
        
        answer = cnt;
        
        return answer;
    }
    
    public static boolean isPrime(){
        int sum = 0;
        for(int i = 0; i < 3; i++){
            sum += selectThree[i];
        }
        for(int i = 2; i * i <= sum; i++){
            if(sum % i == 0)
                return false;
        }
        return true;
    }
}