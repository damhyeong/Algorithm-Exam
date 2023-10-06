class Solution {
    public int solution(int n, int m, int[] section) {
        int answer = 0;
        
        int pIndex = -1;
        for(int i = 0; i < section.length; i++){
            int noPainted = section[i];
            if(pIndex < noPainted){
                pIndex = noPainted + m - 1;
                answer++;
            }
        }
        
        return answer;
    }
}