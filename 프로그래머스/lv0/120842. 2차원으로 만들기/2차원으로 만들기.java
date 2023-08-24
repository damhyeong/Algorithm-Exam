class Solution {
    public int[][] solution(int[] num_list, int n) {
        int[][] answer = {};
        
        int iLen = num_list.length / n;
        
        answer = new int[iLen][n];
        
        int index = 0;
        for(int i = 0; i < iLen; i++){
            for(int j = 0; j < n; j++){
                answer[i][j] = num_list[index++];
            }
        }
        
        return answer;
    }
}