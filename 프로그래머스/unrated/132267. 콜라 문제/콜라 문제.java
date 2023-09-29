class Solution {
    public int solution(int a, int b, int n) {
        int answer = 0;
        
        while(n / a != 0){
            int num = n / a; // 몇 번의 a개를 만들 수 있는지
            int full = num * b; // 만들어진 개수만큼 b를 곱한다. 3병을 주면 2병을 줄 수도 있으므로.
            n %= a;
            answer += full;
            n += full;
        }
        
        return answer;
    }
}