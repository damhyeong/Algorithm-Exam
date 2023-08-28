import java.math.*;

class Solution {
    public int solution(int[][] board) {
        int answer = 0;
        
        boolean[][] isNotSafe = new boolean[board.length][board[0].length];
        
        for(int i = 0; i < board.length; i++){
            for(int j = 0; j < board[0].length; j++){
                if(board[i][j] == 1){
                    int iF = Math.max(i - 1, 0);
                    int iL = Math.min(i + 1, board.length - 1);
                    int jF = Math.max(j - 1, 0);
                    int jL = Math.min(j + 1, board[0].length - 1);
                    for(int x = iF; x <= iL; x++){
                        for(int y = jF; y <= jL; y++){
                            isNotSafe[x][y] = true;
                        }
                    }
                }
            }
        }
        
        for(int i = 0; i < isNotSafe.length; i++){
            for(int j = 0; j < isNotSafe[0].length; j++)
                if(!isNotSafe[i][j])
                    answer++;
        }
        
        return answer;
    }
}