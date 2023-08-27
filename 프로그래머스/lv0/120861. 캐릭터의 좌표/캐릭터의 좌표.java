class Solution {
    public int[] solution(String[] keyinput, int[] board) {
        int[] answer = new int[2];
        answer[0] = 0; answer[1] = 0;
        
        int distanceX = board[0] / 2;
        int distanceY = board[1] / 2;
        
        for(int i = 0; i < keyinput.length; i++){
            String command = keyinput[i];
            int[] save = new int[2];
            save[0] = answer[0]; save[1] = answer[1];
            
            if(command.equals("up"))
                answer[1]++;
            else if(command.equals("down"))
                answer[1]--;
            else if(command.equals("left"))
                answer[0]--;
            else if(command.equals("right"))
                answer[0]++;
            
            int newDisX = Math.abs(answer[0]);
            int newDisY = Math.abs(answer[1]);
            
            if(newDisX > distanceX || newDisY > distanceY)
                answer = save;
        }
        
        return answer;
    }
}