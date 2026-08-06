class Solution {
    boolean solution(String s) {
        boolean answer = true;

        int pNm = 0;
        int yNm = 0;
        for(int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            int tmpResult = charFunc(ch);
            if(tmpResult == 1)
                pNm++;
            else if(tmpResult == 2)
                yNm++;
        }
        
        answer = pNm == yNm ? true : false;

        return answer;
    }
    public int charFunc(char ch) {
        if(ch == 'p' || ch == 'P')
            return 1;
        else if(ch == 'y' || ch == 'Y') {
            return 2;
        } else {
            return 3;
        }
    }
}