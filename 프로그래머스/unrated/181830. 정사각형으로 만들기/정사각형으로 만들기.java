class Solution {
    public int[][] solution(int[][] arr) {
        int[][] answer = {};
        
        int height = arr.length;
        int width = arr[0].length;
        
        int max = 0;
        max = (height >= width) ? height : width;
        
        answer = new int[max][max];
        
        for(int i = 0; i < max; i++){
            for(int j = 0; j < max; j++){
                answer[i][j] = (i < height && j < width) ? arr[i][j] : 0;
            }
        }
        
        return answer;
    }
}