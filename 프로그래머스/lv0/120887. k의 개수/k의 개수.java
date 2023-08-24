class Solution {
    public int solution(int i, int j, int k) {
        int answer = 0;
        
        char kCh = Integer.toString(k).charAt(0);
        int cnt = 0;
        for(;i <= j; i++){
            String str = Integer.toString(i);
            for(int x = 0; x < str.length(); x++){
                char ch = str.charAt(x);
                if(ch == kCh)
                    cnt++;
            }
        }
        answer = cnt;
        
        return answer;
    }
}