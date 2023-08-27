class Solution {
    public int solution(int M, int N) {
        int answer = 0;
        
        int mCnt = 0;
        while(M != 1){
            M -= 1;
            mCnt++;
        }
        
        int nCnt = 0;
        while(N != 1){
            N -= 1;
            nCnt += (mCnt + 1);
        }
        answer = mCnt + nCnt;
        
        return answer;
    }
}