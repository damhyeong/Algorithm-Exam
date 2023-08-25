class Solution {
    public int solution(int[] array) {
        int answer = 0;
        
        int cnt = 0;
        for(int i = 0; i < array.length; i++){
            String str = Integer.toString(array[i]);
            for(int j = 0; j < str.length(); j++){
                char ch = str.charAt(j);
                if(ch == '7')
                    cnt++;
            }
        }
        answer = cnt;
        
        return answer;
    }
}