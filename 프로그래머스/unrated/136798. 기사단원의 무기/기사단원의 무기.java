class Solution {
    public int solution(int number, int limit, int power) {
        int answer = 0;
        
        int[] countDivide = new int[number + 1];
        
        
        for(int i = 1; i <= number; i++){
            int count = 0; // 약수의 개수
            for(int j = 1; j * j <= i; j++){
                if(j * j == i)
                    count++;
                else if(i % j == 0){
                    count += 2;
                }
            }
            
            if(count > limit) // 약수의 개수 = 파워 가 제한수치를 넘는다면 
                count = power; // 이웃나라와의 협약으로 제한된 파워의 무기를 받는다.
            answer += count; // 파워 == 필요한 철의 개수 
        }
        
        return answer;
    }
}