class Solution {
    public int solution(String[] spell, String[] dic) {
        int answer = 2;
        
        int[] charSet = new int['z' - 'a' + 1];
        for(int i = 0; i < spell.length; i++){
            char ch = spell[i].charAt(0);
            charSet[ch - 'a']++;
        }
        
        for(int i = 0; i < dic.length; i++){
            String newStr = dic[i];
            int[] numCh = new int['z' - 'a' + 1];
            for(int j = 0; j < newStr.length(); j++){
                char ch = newStr.charAt(j);
                numCh[ch - 'a']++;
            }
            boolean isEqual = true;
            for(int j = 0; j < numCh.length; j++){
                if(charSet[j] != numCh[j]){
                    isEqual = false;
                    break;
                }
            }
            if(isEqual){
                answer = 1;
                break;
            }
        }
        
        return answer;
    }
}