class Solution {
    public int[] solution(String[] wallpaper) {
        int[] answer = new int[4];
        
        boolean[][] filePlace = new boolean[wallpaper.length][wallpaper[0].length()];
        
        int minX = 51;
        int maxX = -1;
        int minY = 51;
        int maxY = -1;
        
        for(int i = 0; i < wallpaper.length; i++){
            for(int j = 0; j < wallpaper[0].length(); j++){
                filePlace[i][j] = wallpaper[i].charAt(j) == '.' ? false : true;
            }
        }
        
        for(int i = 0; i < filePlace.length; i++){
            for(int j = 0; j < filePlace[0].length; j++){
                if(filePlace[i][j] == true){
                    if(minX >= j)
                        minX = j;
                    if(minY >= i)
                        minY = i;
                    if(maxX <= j)
                        maxX = j;
                    if(maxY <= i)
                        maxY = i;
                }
            }
        }
        
        answer[0] = minY; answer[1] = minX; answer[2] = maxY + 1; answer[3] = maxX + 1;
        
        return answer;
    }
}